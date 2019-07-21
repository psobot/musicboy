.PHONY: all clean check
.SUFFIXES:
.SUFFIXES: .asm .o .gb

# Available from: https://github.com/kaspermeerts/supermarioland
# or forked/cloned to https://github.com/psobot/supermarioland
SUBDIR=supermarioland/

cgbobjects := bank0.cgb.o bank3.cgb.o $(addprefix ${SUBDIR}, bank1.cgb.o bank2.cgb.o music.cgb.o levels/enemy_locations.cgb.o)
dmgobjects := bank0.dmg.o bank3.dmg.o $(addprefix ${SUBDIR}, bank1.dmg.o bank2.dmg.o music.dmg.o levels/enemy_locations.dmg.o)

images := gfx/menuTiles1.2bpp gfx/commonTiles1.2bpp $(addprefix ${SUBDIR}, gfx/backgroundWorld1.2bpp \
	gfx/backgroundWorld2.2bpp \
	gfx/backgroundWorld3.2bpp \
	gfx/backgroundWorld4.2bpp \
	gfx/commonTiles2.2bpp \
	gfx/commonTiles3.2bpp \
	gfx/enemiesWorld1.2bpp \
	gfx/enemiesWorld2.2bpp \
	gfx/enemiesWorld3.2bpp \
	gfx/enemiesWorld4.2bpp \
	gfx/menuTiles2.2bpp)

# Maximum volume for CGB = 0xBB, or 42% of STM32 Voltage
CGBARGS= -D kNR50Value=\$$BB
# Maximum volume for DMG = 0xFF, or 100% of STM32 Voltage
DMGARGS= -D kNR50Value=\$$FF

all: dmg.gb cgb.gb
	@echo "Done compiling: $<"

clean:
	rm -fv dmg.gb cgb.gb $(cgbobjects) $(dmgobjects) gfx/*.2bpp *.map *.sym ${SUBDIR}*.o

gfx/menuTiles1.2bpp: gfx/menuTiles1.png
	@echo "Encoding	$@ from $<"
	@python gb_2bpp_quantize.py $<
	@dazzlie encode -f gb_2bpp -W 16 -i $< -o $@

gfx/commonTiles1.2bpp: gfx/commonTiles1.png
	@echo "Encoding	$@ from $<"
	@python gb_2bpp_quantize.py $<
	@dazzlie encode -f gb_2bpp -W 16 -i $< -o $@

# Export everything for the moment, to make debugging easier
%.cgb.o: %.asm
	@echo "Assembling	$@ from $<"
	@rgbasm -i ./ -i ./gfx/ -i ${SUBDIR} -h -E ${CGBARGS} -h -o $@ $<

%.dmg.o: %.asm
	@echo "Assembling	$@ from $<"
	@rgbasm -i ./ -i ./gfx/ -i ${SUBDIR} -h -E ${DMGARGS} -h -o $@ $<

cgb.gb: $(cgbobjects) $(images)
	@echo "Linking	$@ from ${cgbobjects}"
	@rgblink -d -n $*.sym -m $*.map -o $@ $(cgbobjects)
	@rgbfix -v $@

dmg.gb: $(dmgobjects) $(images)
	@echo "Linking	$@ from ${dmgobjects}"
	@rgblink -d -n $*.sym -m $*.map -o $@ $(dmgobjects)
	@rgbfix -v $@
