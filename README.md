# Music Boy
_A high-quality audio playback cartridge for Nintendo® Game Boy® and Game Boy Color®._

![splash](https://user-images.githubusercontent.com/213293/50737951-7f4f8900-119c-11e9-8828-3fdd478bb506.png)

(Note: this project is not approved, condoned, or endorsed by Nintendo®.)

## What is _Music Boy_?

_Music Boy_ is a custom hardware cartridge and accompanying software to play
back **high quality audio** on the Nintendo® Game Boy® and Game Boy Color®
handheld game consoles<sup>1</sup>. Music Boy fits in a standard Game Pak®
cartridge casing and requires no additional modifications - it plays like a
standard game.

_Music Boy_ was originally created as a unique distribution mechanism for [PUSHER](https://twitter.com/itspusher)'s [2016 _New Laces_ EP](https://open.spotify.com/album/1mfsE08YoglXSCHUcvpyCJ). While it can be repurposed to work with other Game Boy games, Music Boy currently only plays music in the background of a modified copy of _Super Mario Land_.

> For a more detailed story of _Music Boy_, see [my 2019 talk from !!con: "_Even more vintage: releasing music on a custom-built Game Boy cartridge!_"](https://www.youtube.com/watch?v=5PHLJ7zppfo):
>
> [![Even more vintage: releasing music on a custom-built Game Boy cartridge!](https://img.youtube.com/vi/5PHLJ7zppfo/0.jpg)](https://www.youtube.com/watch?v=5PHLJ7zppfo)

<sup>1</sup>_Music Boy_ may work on other consoles, like the Super Game Boy®,
but will not work on the Game Boy Pocket®, Game Boy Advance® or Nintendo DS® due to fundamental
hardware differences.

## How does _Music Boy_ Work?

_Music Boy_ is a highly non-standard cartridge - or rather, a cartridge
_emulator_, built upon an [ARM Cortex-M4](https://en.wikipedia.org/wiki/ARM_Cortex-M#Cortex-M4)
(the STMicroelectronics [STM32F446](https://www.st.com/en/microcontrollers/stm32f446ze.html) family)
system-on-chip. This hardware acts as both a flash emulator, providing the
Game Boy with instructions to execute on its own CPU, and a rudimentary co-processor,
providing the Game Boy with additional facilities and control over
a high-quality analog audio output that can output up to 96kHz at 12 bits.

### Hardware specs

 - CPU: [STM32F446ZET6](https://www.st.com/en/microcontrollers/stm32f446ze.html)
   - ARM Cortex-M4 at 180MHz
   - 512kB Flash Storage (may be a bit overkill)
   - 128kB SRAM
   - 2x 8- or 12-bit DAC channels at sample rates well beyond 96kHz
 - Storage: [W25Q128JV](http://www.winbond.com/resource-files/w25q128jv%20revf%2003272018%20plus.pdf)
   - 128MBit / 16MB Quad-SPI Flash
   - Could use Quad-SPI, but currently only connected in single-SPI mode
   - With 8-bit audio depth, this provides up to ~15 minutes of mono audio at ~14kHz.
     (Unlike most audio hardware, we have granular control over sample rate, and choose the
     sample rate based on the amount of audio we want to fit on the cart.)
   - This could reasonably be replaced with a microSD card for greater storage,
     at a slightly increased per-cartridge part cost
 - Interface: Nintendo Game Pak Connector
   - Pin 31 provides a single mono audio input from the cartridge to the Game Boy®'s audio mixer,
     unused by any commercial games
   - The Game Boy® levels are at 5V, while the STM32F4 outputs 3.3V. Luckily, the Game Boy®
     accepts any voltage above ~2.5V as "high" and the STM32F4 pins are 5V-tolerant.
 - Programmable ST-LINK and SPI Flash headers
   - _Music Boy_ can be debugged or re-flashed _while running in a powered-on Game Boy®_,
     which creates a development experience similar to many modern IDEs.
   - Code loading and debugging is possible via the 5-pin ST-LINK header, which
     requires a corresponding ST-LINK board from STMicroelectronics. (Their line of
     Nucleo boards each come with built-in ST-LINK header boards.)
   - Re-flashing of the flash storage can be accomplished via the 6-pin SPI header,
     which, with a standad SPI programmer (or Raspberry Pi), should be flashed with the contents of `flash.bin`.

### Software

_Music Boy_ uses a combination of software written in C, ARM Assembly, Python, and
Game Boy assembly (a variant of Z80 assembly), all working together in sequence:

 - At compile time, a number of Python scripts generate C and RGBDS assembly code
   to share common variable definitions between the Game Boy and the STM32F4. A
   Python script also prepares a `flash.bin` file that contains all of the audio
   data required for playback, and saves metadata about this binary audio data as
   a C header file for use by the STM32F4.
 - At run time, the STM32F4 CPU starts by:
   - configuring its inputs and outputs appropriately
   - initializing its peripherals (DAC for audio output, DMA for reading audio from Flash)
   - configuring an interrupt handler to trigger every time the Game Boy clock's edge rises
   - pulls the Game Pak `/RST` pin low to force the Game Boy to restart
 - The Game Boy's built-in boot ROM (for [Game Boy](https://gist.github.com/drhelius/6063288) or [Game Boy Color](https://gist.github.com/drhelius/6063265)) then starts to read data from the STM32F4
   - The Game Boy compares the Nintendo logo returned by the STM32F4 to the logo programmed into the Game Boy's ROM. If this logo does not match exactly, the Game Boy halts all execution and prevents the "illegitimate" cartridge from playing.
     - This was a simple form of copy protection, as the Nintendo logo is copyrighted and Nintendo had legal grounds to sue any cartridge maker that included it in a cartridge without the appropriate licence.
   - The Game Boy presents the logo from the cartridge on-screen during boot, then starts reading from the cartridge and executing instructions.
     - Depending on the model, the Game Boy and Game Boy Color perform these operations in different orders. The _Music Boy_ accounts for this and can switch the logo being displayed automatically to present a non-Nintendo logo on the splash screen.
 - Using certain timings obtained during the boot process, the STM32F4 can detect which Game Boy model is currently running the cartridge, and will dynamically patch the software it provides to the Game Boy to run different instructions depending on the model.
   - This is necessary due to slight differences in the audio hardware of each Game Boy model:
     - The Game Boy (DMG, or "Dot Matrix Game") supports anywhere from 0 to 4V on its external audio input (V<sub>in</sub>) pin.
     - The Game Boy Color (CGB, or "Color Game Boy") expects a smaller range of voltages, from 1.9V to 2.5V on its V<sub>in</sub> pin.
 - The STM32F4 maps a region of the Game Boy's address space into its own RAM (4kB, from 0xA000 to 0xAFFF) to allow for communication between the code running on the Game Boy's CPU and code running on the STM32F4.
 - The Game Boy software begins to run a game by treating the STM32F4 as a regular cartridge.
 - The software running on the Game Boy (currently _Super Mario Land_) has been modified by replacing certain instructions:
   - The background music loop no longer plays the original game's music
   - Certain button presses send messages through the shared address space to the STM32F4 (pause and unpause, for instance)
   - Changes in game state or current level are communicated to the STM32F4 through the shared address space
   - The audio hardware is initialized to allow audio pass-through from the STM32F4 to the Game Boy's speaker or headphones
   - Other cosmetic changes (artwork or string changes) to fit the desired application

## Software Installation

Assuming you're on macOS, you'll need:

 - [`brew`](https://brew.sh/)
 - a working Python 2.7 installation (sorry, not Python 3 yet!)
 - a working [gcc_arm installation](https://gist.github.com/joegoggins/7763637)

Then:

```bash
brew install rbgds stlink rsync ffmpeg
pip install -r code/requirements.txt
```

Note that if you want to compile the project completely, you'll need:

 - a copy of the Super Mario Land ROM moved to `code/gbrom/baserom.gb`, with the sha1 `418203621b887caa090215d97e3f509b79affd3e`
 - one or more audio files in the `music` folder, of any format accepted by `ffmpeg`, sorted lexicographically. Each successive file will be used as background music for each level. Note that if you provide more than 9 files, any files after the 9th will not be used.

## Hardware Design

The `hardware` directory contains a [KiCad](http://kicad.org/) project and all of its dependencies.

If you plan to print circuit boards, make sure you use 0.8mm thick PCBs. The PCB dimensions should be 61mm*51.4mm, with a notch on one corner.

If you're not comfortable soldering super-fine-pitch surface mount components (like me) then I recommend using a third-party assembly service such as [Seeed Studio](https://www.seeedstudio.com/prototype-pcb-assembly.html).

## Credits

Music Boy was developed between 2016 and 2019 by [Peter Sobot](https://petersobot.com), but leaned heavily on prior art and help by a number of brilliant people:

 - [dhole](http://dhole.github.io/about/)'s posts on building an STM32 cartridge emulator were extremely helpful:
   - [Emulating a GameBoy Cartridge with an STM32F4. Part 1](https://dhole.github.io/post/gameboy_cartridge_emu_1/) (2014)
   - [Emulating a GameBoy Cartridge with an STM32F4. Part 2](https://dhole.github.io/post/gameboy_cartridge_emu_2/) (2014)
   - [Booting the GameBoy with a custom logo](https://dhole.github.io/post/gameboy_custom_logo/) (2014)
   - [stm32f_GBCart](https://github.com/Dhole/stm32f_GBCart) on GitHub
 - [Anders Granlund](http://www.happydaze.se/)'s post on building a custom Wolfenstein 3D game for Game Boy with a co-processor was super inspiring:
   - [Wolf, Gameboy cartridge with co-processor](http://www.happydaze.se/wolf/) (2016)
 - [Kasper Meerts](https://github.com/kaspermeerts)' disassembly of _Super Mario Land_ (1989) was super useful in providing a game to use as payload
   - [_supermarioland_](https://github.com/kaspermeerts/supermarioland) on GitHub
 - [Eric Evenchick](https://www.evenchick.com/) was instrumental in helping review and validate my hardware design before going to production
 - [PUSHER](https://twitter.com/itspusher), the inspiration for starting this project, was an encouraging patron throughout

## Licenses & Legal

This project is a hacked together custom Game Boy cartridge, based on third-party code,
and - for demoing - using a modified version of a commercial Nintendo game from 1989.

All of my original code and hardware designs in this project are licensed under
[the MIT License](https://en.wikipedia.org/wiki/MIT_License). Some STM32 library files
are licensed with the _MCD-ST Liberty SW License Agreement V2_, as they were
open-sourced by STMicroelectronics, and further helper libraries are licensed by their
own various licenses.

If you're trying to build this yourself, you'll need to supply your own copy of
_Super Mario Land_ and your own audio files. I take no responsibility for any derivative
works created from this project.

