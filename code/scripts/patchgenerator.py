"""
This script takes in two file names on the command line and
produces two C functions, called patch_to_{filename} for each file,
which - when given a uint8_t array - will convert from one file to
the other.

This is used to store only one copy of the Game Boy ROM on the STM32
but allow us to switch between two different ROMs by only patching
the differences.
"""

import os
import sys


def generate_diff_functions(a_filename, b_filename):
    a_name = os.path.split(a_filename)[-1].split('.')[0]
    b_name = os.path.split(b_filename)[-1].split('.')[0]

    a_file = open(a_filename, 'rb')
    b_file = open(b_filename, 'rb')

    diff_map = {}

    for i, (a_byte, b_byte) in enumerate(zip(a_file.read(), b_file.read())):
        if a_byte != b_byte:
            diff_map[i] = (a_byte, b_byte)

    yield "void patch_to_{}(volatile uint8_t *bin) {{".format(a_name)
    for i, (a, _) in diff_map.iteritems():
        yield "\tbin[0x{:02X}] = 0x{:02X};".format(i, ord(a))
    yield "}"

    yield "void patch_to_{}(volatile uint8_t *bin) {{".format(b_name)
    for i, (_, b) in diff_map.iteritems():
        yield "\tbin[0x{:02X}] = 0x{:02X};".format(i, ord(b))
    yield "}"

if __name__ == "__main__":
    for line in generate_diff_functions(sys.argv[-2], sys.argv[-1]):
        print line
