"""
Usage: flashprep.py path_to_audio_directory

This script will take the audio files in the passed directory,
sort them lexicographically, pick a sample rate to fit them
into the provided memory space, and then output:
  - flash.bin, containing a header plus the audio streams
  - data/flash_constants.h, containing constants
  - data/flash_constants.c, containing an TrackMetadata array
"""

import os
import sys
import math
import struct
from glob import glob
from tqdm import tqdm
import subprocess


SECRET_HEADER_TEXT = """
Hello world! If you're reading this, you've somehow
disassembled this custom Game Boy cartridge and are
reverse engineering it or something. Cool. My name's
Peter, and I built this in 2017/2018. I'd love to
hear from you - send me an email at:
gameboy@petersobot.com or find me on most social
networks at @psobot.

What follows is a concatenation of multiple audio
files encoded at 8bits and some arbitrary sample rate.
Their bounds are specified in a rudimentary header format:

uint32_t: number of files
uint32_t: start of file 0
uint32_t: start of file 1...

After the newline at the end of the next sentence,
the header will begin. Happy hacking!
"""

SECRET_HEADER_TEXT = SECRET_HEADER_TEXT.lstrip()
DEFAULT_SIZE_IN_MBITS = 128
MAX_NUMBER_OF_HEX_DIGITS = math.log(DEFAULT_SIZE_IN_MBITS, 2) - 1


def generate_file_offsets(files_with_sizes):
    offset = get_header_size(files_with_sizes)
    for file, size in files_with_sizes:
        yield (file, offset)
        offset += size


def generate_header(files_with_sizes):
    return "".join([
        SECRET_HEADER_TEXT,
        struct.pack("<i", len(files_with_sizes)),
    ] + [
        struct.pack("<i", offset)
        for _, offset
        in generate_file_offsets(files_with_sizes)
    ])


def get_header_table_size(files):
    return 4 + (len(files) * 4)


def get_header_table_start():
    return len(SECRET_HEADER_TEXT)


def get_header_size(files):
    return get_header_table_start() + get_header_table_size(files)


def to_raw_audio(file, sample_rate=None):
    if sample_rate:
        sample_rate_args = ['-ar', str(sample_rate)]
    else:
        sample_rate_args = []

    command = [
        'ffmpeg', '-i', file, '-f', 'u8', '-ac', '1'
    ] + sample_rate_args + ['-']

    return subprocess.check_output(
        command,
        stderr=open(os.devnull, 'w')
    )


def normalize_name(fname):
    return (
        fname
        .split('/')[-1]
        .split('.')[0]
        .upper()
        .replace(' ', '_')
        .replace("(", "")
        .replace(")", ""))


def generate_c_defines(offsets, files_with_sizes, sample_rate, buffer_size):
    yield "#ifndef flash_constants"
    yield "#define flash_constants"
    yield "#define BUFFER_SIZE_BYTE {}".format(buffer_size)
    yield "#define AUDIO_TRACK_COUNT {}".format(len(files_with_sizes))

    yield "#define AUDIO_SAMPLE_RATE {}".format(sample_rate)
    for (file, offset), (_, size) in zip(offsets, files_with_sizes):
        yield "#define AUDIO_{}_START {}".format(normalize_name(file), offset)
        yield "#define AUDIO_{}_END {}".format(
            normalize_name(file), offset + size)

    yield "typedef struct {"
    yield "  unsigned int start_offset;"
    yield "  unsigned int end_offset;"
    yield "} TrackMetadataEntry;"

    yield "TrackMetadataEntry TrackMetadata[AUDIO_TRACK_COUNT];"
    yield ("#define TrackMetadataForLevel(level) "
           "(TrackMetadata[level % AUDIO_TRACK_COUNT])")
    yield "#endif"


def generate_c_arrays(offsets, files_with_sizes):
    yield '#include "flash_constants.h"'

    """
    Note: The original Super Mario Land cart uses this music mapping:

    .musicByLevel
        db 7, 7, 3
        db 8, 8, 5
        db 7, 3, 3
        db 6, 6 ,5
    """

    yield "TrackMetadataEntry TrackMetadata[AUDIO_TRACK_COUNT] = {"
    for (file, offset), (_, size) in zip(offsets, files_with_sizes):
        yield "\t{{ AUDIO_{}_START, AUDIO_{}_END }},".format(
            normalize_name(file),
            normalize_name(file))
    yield "};"


def get_total_audio_length(files):
    # assume original files are at 44100
    sample_rate = 44100
    converted_audio_files = [to_raw_audio(f, sample_rate) for f in tqdm(files)]
    return float(sum(len(file) for file in converted_audio_files)) \
        / float(sample_rate)


def as_hex_address(num):
    return ("0x{:0" + str(int(MAX_NUMBER_OF_HEX_DIGITS)) + "X}").format(num)


def flashprep(
    directory,
    outfile='flash.bin',
    maxsize=DEFAULT_SIZE_IN_MBITS * 1024 * 1024 / 8,
    sample_rate=None,
    buffer_size=512,
):
    """
    Given a list of files, generate one binary with all of them concatenated,
    along with C defines specifying their bounds.
    """
    files = sorted(glob(os.path.join(directory, '*')))

    if sample_rate is None:
        quantize = 50
        available_space = maxsize - get_header_size(files)
        audio_length_seconds = get_total_audio_length(files)
        float_sample_rate = (float(available_space) / audio_length_seconds)
        sample_rate = math.floor(float_sample_rate / quantize) * quantize
        print "Using sample rate of {:,} to fit {:,}s into {:,} bytes.".format(
            sample_rate, audio_length_seconds, available_space)

    converted_audio_files = [to_raw_audio(f, sample_rate) for f in tqdm(files)]

    files_with_sizes = [
        (f, len(converted_audio_file))
        for f, converted_audio_file in tqdm(zip(files, converted_audio_files))
    ]
    header = generate_header(files_with_sizes)

    offsets = list(generate_file_offsets(files_with_sizes))
    for (file, offset), (_, size) in zip(offsets, files_with_sizes):
        print (
            "File {} starts at byte {:,} ({}) and "
            "ends at byte {:,} ({})").format(
            file,
            offset,
            as_hex_address(offset + size),
            offset + size,
            as_hex_address(offset + size))

    with open('data/flash_constants.h', 'w') as f:
        for line in generate_c_defines(
            offsets,
            files_with_sizes,
            sample_rate,
            buffer_size
        ):
            f.write(line)
            f.write("\n")

    with open('data/flash_constants.c', 'w') as f:
        for line in generate_c_arrays(offsets, files_with_sizes):
            f.write(line)
            f.write("\n")

    with open(outfile, 'w') as out:
        out.write(header)
        for f in tqdm(converted_audio_files):
            out.write(f)
        size = out.tell()
        # pad with zero bytes until we hit the size of the flash
        out.write("\x00" * (maxsize - size))
    if size > maxsize:
        raise ValueError((
            "Size of requested data ({:,} bytes) is greater "
            "than max flash size ({:,} bytes)!").format(size, maxsize))
    print "Wrote {:,} bytes ({}% of max) to {}.".format(
        size,
        100. * (float(size) / float(maxsize)),
        outfile
    )

if __name__ == "__main__":
    input_folder = sys.argv[-1]
    if not os.path.isdir(input_folder):
        raise ValueError(
            "Usage: %s path_to_directory_with_sorted_audio_files" %
            sys.argv[0])
    flashprep(input_folder)
