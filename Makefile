#export PATH=${PATH}:/Users/jeff/Desktop/z88dk/bin
#export ZCCCFG=/Users/jeff/Desktop/z88dk/lib/config

# see https://github-wiki-see.page/m/z88dk/z88dk/wiki/NewLib--Platform--Embedded



all: mamerom bootrom

prereq:
	@mkdir -p build
	@mkdir -p roms

clean:
	$(RM) -rf build
	$(RM) -rf roms

# development is made easier by loading bootrom into 1873.cpu-u25
# then romulator can be quickly loaded to a single large rom on the ROM board

mamerom: prereq
	@echo "building 32kb rom at 0x0000"
	zcc +z80 --list -vn -SO3 -compiler=sdcc -startup=1 main.c -o $@ -create-app -DEMBEDDED_USB -Cz"--rombase=0x0000 --romsize=32768"
	@mv $@* build/ 2>/dev/null || true
	@mv *.lis build/ 2>/dev/null || true
	@printf 'code size: ' && stat -f '%z' build/$@_CODE.bin 
	truncate -s 26K build/$@.rom
	cat usbrom.bin >> build/$@.rom

gamerom: prereq
	@echo "building 32k rom at 0x800 for use with sega-boot-rom in cpu rom socket"
	zcc +z80 --list -vn -SO3 -compiler=sdcc -startup=1 main.c -o $@ -create-app -DEMBEDDED_USB -DENABLE_BOOTROM -Cz"--rombase=0x0800 --romsize=24576"
	@mv $@* build/ 2>/dev/null || true
	@mv *.lis build/ 2>/dev/null || true
	@printf 'code size: ' && stat -f '%z' build/$@_CODE.bin
	@rm -f build/$@.bin
	truncate -s 2K build/$@.bin
	cat build/$@.rom >> build/$@.bin
	truncate -s 26K build/$@.bin
	cat usbrom.bin >> build/$@.bin

bootrom: prereq
	z80asm bootrom.asm -o build/$@.bin
	truncate -s 2K build/$@.bin

roms: prereq
	@cp build/bootrom.bin roms/1873.cpu-u25
	@split -b 2048 build/gamerom.bin roms/part_
	@i=0; \
	for f in $(shell ls roms/part_* | sort); do \
		base=$$((1847 + $$i)); \
		mv "$$f" "roms/$$base.prom-u$$i"; \
		i=$$((i + 1)); \
	done
	@rm roms/1847.prom-u0


# ROM Emulator https://github.com/Kris-Sekula/EPROM-EMU-NG/
# python3 -m pip install serial
# python3 -m pip install PySimpleGUI
# brew install python-tk

PROGRAMMER = python3 ~/Downloads/EPROM_EMU_NG_2.0rc9.py
UART = /dev/cu.usbserial-B00050RO

flash:
	 ${PROGRAMMER} -mem 27256 -spi n -auto y -start 0 build/gamerom.bin ${UART}

