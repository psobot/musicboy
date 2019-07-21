# Note: these arguments apparently MUST BE compiled in this order.
# program C files first, then lib, then data.
# Other orderings generate an ELF file that doesn't boot properly on CGB.
LIB_SRCS=lib/*.c lib/*.s
SRCS=*.c $(LIB_SRCS) data/*.c
DUMMY_SRCS=dummy/*.c $(LIB_SRCS)

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=gbcart

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

# Change this IP address to the IP address of a Raspberry Pi on your local network
# This Makefile assumes you'll have flashrom set up on an RPi as so: https://www.flashrom.org/RaspberryPi
PI_IP=192.168.0.112

CFLAGS  = -g -O3 -Wall -Tlib/stm32_flash.ld
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.

OBJS = $(SRCS:.c=.o)

all: $(PROJ_NAME).elf
	@echo "Done compiling: $<"

$(OBJS): Makefile

.PHONY: clean burn burn-dummy debug flash-rpi

gbrom/cgb.gb: gbrom/*.asm gbrom/gfx/* gbrom/audio_constants.asm gbrom/Makefile
	@echo "Compiling $@"
	@$(MAKE) -C gbrom

gbrom/dmg.gb: gbrom/*.asm gbrom/gfx/* gbrom/audio_constants.asm gbrom/Makefile
	@echo "Compiling $@"
	@$(MAKE) -C gbrom

data/rom.h: gbrom/cgb.gb
	@echo "Converting $^ into $@"
	@xxd -i gbrom/cgb.gb | sed s/gbrom_cgb/rom/g | sed s/unsigned\ char/volatile\ unsigned\ char/g > $@

data/boot_logo.bin: scripts/make_logo.py assets/boot_logo2.png
	@echo "Encoding boot logo into $@"
	@python scripts/make_logo.py assets/boot_logo2.png $@

data/boot_logo.h: data/boot_logo.bin
	@echo "Converting $^ into $@"
	@xxd -i data/boot_logo.bin | sed s/data_boot_logo/boot_logo/g > $@

rom_patch.h: scripts/patchgenerator.py gbrom/cgb.gb gbrom/dmg.gb
	@echo "Creating $@ from $^"
	@python scripts/patchgenerator.py gbrom/cgb.gb gbrom/dmg.gb > rom_patch.h

$(SRCS): data/flash_constants.h data/boot_logo.h data/rom.h rom_patch.h audio_constants.h

$(PROJ_NAME).elf: $(SRCS)
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Compiling ${PROJ_NAME}.hex..."
	@$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	@echo "Compiling ${PROJ_NAME}.bin..."
	@$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

$(PROJ_NAME)-dummy.elf: $(DUMMY_SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME)-dummy.elf $(PROJ_NAME)-dummy.hex
	$(OBJCOPY) -O binary $(PROJ_NAME)-dummy.elf $(PROJ_NAME)-dummy.bin

audio_constants.h: scripts/generate_audio_constants.py
	@echo "Generating $@"
	@python scripts/generate_audio_constants.py

gbrom/audio_constants.asm: scripts/generate_audio_constants.py
	@echo "Generating $@"
	@python scripts/generate_audio_constants.py

clean:
	@$(MAKE) -C gbrom clean
	rm -f *.o
	rm -f rom_patch.h
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME)-dummy.elf
	rm -f $(PROJ_NAME)-dummy.hex
	rm -f $(PROJ_NAME)-dummy.bin
	rm -f flash.bin
	rm -f data/*
	rm -f audio_constants.h
	rm -f gbrom/audio_constants.asm

# Flash the STM32F4 with st-flash in preparation for flashing the FLASH ROM.
burn-dummy: $(PROJ_NAME)-dummy.elf
	st-flash write $(PROJ_NAME)-dummy.bin 0x8000000

erase:
	st-flash erase

# Flash the STM32F4 with st-flash
burn: proj
	st-flash write $(PROJ_NAME).bin 0x8000000

debug: # burn
	# Launch st-util for debugging in the background
	st-util &
	arm-none-eabi-gdb ./gbcart.elf

disasm: $(PROJ_NAME).elf
	arm-none-eaby-objdump -S --disassemble $^

data/flash_constants.h: scripts/flashprep.py music/*
	@echo "Preparing $@"
	@python scripts/flashprep.py ./music

data/flash_constants.c: scripts/flashprep.py music/*
	@echo "Preparing $@"
	@python scripts/flashprep.py ./music

flash.bin: scripts/flashprep.py music/*
	@echo "Preparing $@"
	@python scripts/flashprep.py ./music

prep-rpi:
	ssh pi@${PI_IP} "sudo apt-get update && sudo apt-get install -y flashrom"

flash-rpi: flash.bin
	rsync flash.bin pi@${PI_IP}:~
	ssh pi@${PI_IP} "time sudo flashrom -p linux_spi:dev=/dev/spidev0.0,spispeed=30000 --write flash.bin"
