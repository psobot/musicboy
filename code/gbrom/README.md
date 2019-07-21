# gbrom

This directory contains the code that runs on the Game Boy's Z80-based CPU, which is
a modified copy of _Super Mario Land (World) (Rev A)_.

## Instructions

* Ensure you've cloned the `supermarioland` submodule.
* Place a copy of _Super Mario Land (World) (Rev A)_ with SHA1 checksum `418203621b887caa090215d97e3f509b79affd3e` at `baserom.gb`.
* Ensure you have a copy of `rgbds` installed, as well as a working Python installation with `PIL` or `Pillow` installed.

Running `make` should create `cgb.gb` and `dmg.gb`, two different ROMs
built for the Game Boy Color and original Game Boy respectively.
(Usually these are compatible, but as we want to serve different code
based on different Game Boy models, these two ROMs have some crucial differences.)
