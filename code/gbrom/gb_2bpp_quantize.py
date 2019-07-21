"""
Given the path to a PNG file, quantize its colors to only
those greyscale values that the Game Boy can display.
"""

import sys
from PIL import Image

TWOBPP_VALUES = [0x00, 0x55, 0xA9, 0xFF]


def snap_to_color(pixel):
    avg_pixel_value = sum(pixel[:3]) / 3

    for start, end in zip(TWOBPP_VALUES, TWOBPP_VALUES[1:]):
        midpoint = start + ((end - start) / 2)
        if avg_pixel_value < midpoint:
            return (start, start, start)
    return (end, end, end)


def quantize(filename):
    i = Image.open(filename).convert('RGB')
    pixels = i.load()
    for x in xrange(i.size[0]):
        for y in xrange(i.size[1]):
            pixels[x, y] = snap_to_color(pixels[x, y])
    i.save(filename)

if __name__ == "__main__":
    filename = sys.argv[-1]
    if not filename.endswith('.png'):
        raise ValueError(
            "Usage: %s path_to_png_to_quantize" %
            sys.argv[0])
    quantize(filename)
