#! /usr/bin/python2

from __future__ import print_function
import sys
from PIL import Image

size_x = 96 / 2
size_y = 16 / 2


def usage():
    print("Usage:", sys.argv[0], "boot_logo.png boot_logo.bin")


def binarify(b):
    if b == 0:
        return '1'
    else:
        return '0'


def to_binary(filename, out_file):
    logo = Image.open(filename).convert('L').resize((size_x, size_y)).load()

    logo_s = ['0'] * size_x * size_y

    x = 0
    y = 0
    for i in range(0, 24):
        x = (i * 4) % size_x
        y = ((i * 4) / size_x) * 4
        for j in range(0, 16):
            logo_s[i * 16 + j] = binarify(logo[x + (j % 4), y + (j / 4)])

    with open(out_file, 'wb') as f:
        for i in range(0, len(logo_s) / 8):
            f.write(chr(int(''.join(logo_s[i * 8:i * 8 + 8]), 2)))


if __name__ == "__main__":
    if len(sys.argv) < 3:
        usage()
        sys.exit(1)
    to_binary(sys.argv[1], sys.argv[2])
