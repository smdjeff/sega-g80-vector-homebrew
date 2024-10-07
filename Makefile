#export PATH=${PATH}:/Users/jeff/Desktop/z88dk/bin
#export ZCCCFG=/Users/jeff/Desktop/z88dk/lib/config

# see https://github-wiki-see.page/m/z88dk/z88dk/wiki/NewLib--Platform--Embedded



all: testrom dev bootrom

prereq:
	@mkdir -p build

clean:
	$(RM) -rf build

# development is made easier by loading bootrom into 1873.cpu-u25
# then romulator can be quickly loaded to a single large rom on the ROM board

dev: prereq
	@echo "builing development rom at 0x800 for use with sega-boot-rom in cpu rom socket"
	zcc +z80 -vn -O3 -startup=1 -clib=new main.c -o $@ -create-app -DCUSTOM_DEV -Cz"--rombase=0x0800 --romsize=30720"
	@mv $@* build/ 2>/dev/null || true
	truncate -s 2K build/$@.bin
	cat build/$@.rom >> build/$@.bin
	truncate -s 28K build/$@.bin
	cat usbrom.bin >> build/$@.bin

# test rom controlled by control panel buttons
testrom: prereq
	@echo "building rom to test sounds. requires working ROMs at U10,U11,U12"
	zcc +z80 -vn -O3 -startup=1 -clib=new main.c -o $@ -create-app -Cz"--romsize=3333"
	hexdump $@.rom
	@mv $@* build/ 2>/dev/null || true

bootrom: prereq
	z80asm sega-boot.asm -o build/$@.bin
	truncate -s 2K build/$@.bin


# ROM Emulator https://github.com/Kris-Sekula/EPROM-EMU-NG/
# python3 -m pip install serial
# python3 -m pip install PySimpleGUI
# brew install python-tk

PROGRAMMER = python3 ~/Downloads/EPROM_EMU_NG_2.0rc9.py
UART = /dev/cu.usbserial-14110

flash-dev:
	 ${PROGRAMMER} -mem 27256 -spi n -auto y -start 0 build/dev.bin ${UART}

flash-testrom:
	 ${PROGRAMMER} -mem 2716 -spi y -auto y -start 0 build/testrom.rom ${UART}

flash-fp:
	 ${PROGRAMMER} -mem 2716 -spi n -auto y -start 0 cpu1873_freeplay.bin ${UART}

flash-diag:
	 ${PROGRAMMER} -mem 2716 -spi n -auto y -start 0 david_shuman/sega-xydiag-u25.bin ${UART}

flash-factory:
	 ${PROGRAMMER} -mem 2716 -spi n -auto y -start 0 1873.bin ${UART}
