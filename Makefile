#export PATH=${PATH}:/Users/jeff/Desktop/z88dk/bin
#export ZCCCFG=/Users/jeff/Desktop/z88dk/lib/config
# see https://github-wiki-see.page/m/z88dk/z88dk/wiki/NewLib--Platform--Embedded

# ~/Downloads/dasmxx-master/src/dasmz80 dasmxx/sega.txt > dasmxx/gamerom.asm
# minipro -p M2716@DIP24 -w /Users/jeff/Downloads/bootrom.bin  --vpp=25

all: gamerom

prereq:
	@mkdir -p build
	@mkdir -p roms

clean:
	$(RM) -rf build
	$(RM) -rf roms

# development is made easier by loading bootrom into 1873.cpu-u25
# then romulator can be quickly loaded to a single large rom on the ROM board

gamerom: prereq bootrom
	@echo "building 32k rom at 0x800 for use with sega-boot-rom in cpu rom socket"
	zcc +z80 --list -vn -SO3 -compiler=sdcc -startup=1 main.c -o $@ -create-app -DEMBEDDED_USB -DENABLE_BOOTROM -Cz"--rombase=0x0800 --romsize=24576"
	@mv $@* build/ 2>/dev/null || true
	@mv *.lis build/ 2>/dev/null || true
	@printf 'code size: ' && stat -f '%z' build/$@_CODE.bin
	@grep -q "/crt_page_zero_z80.inc:" build/$@.lis || (echo "ERROR crt_page_zero missing. please edit z80_crt_o.asm.m4" && exit 1)
	@rm -f build/$@.bin
	cat build/bootrom.bin >> build/$@.bin
	cat build/$@.rom >> build/$@.bin
	truncate -s 26K build/$@.bin
	cat usbrom.bin >> build/$@.bin

bootrom: prereq
	z80asm bootrom.asm -o build/$@.bin
	truncate -s 2K build/$@.bin

roms: prereq gamerom
	@cp build/bootrom.bin roms/1873.cpu-u25
	@split -b 2048 build/gamerom.bin roms/part_
	@i=0; \
	for f in $(wildcard roms/part_* | sort); do \
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
	 ${PROGRAMMER} -mem 27256 -spi y -auto y -start 0 build/gamerom.bin ${UART}

