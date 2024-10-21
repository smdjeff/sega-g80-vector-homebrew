#export PATH=${PATH}:/Users/jeff/Desktop/z88dk/bin
#export ZCCCFG=/Users/jeff/Desktop/z88dk/lib/config

# see https://github-wiki-see.page/m/z88dk/z88dk/wiki/NewLib--Platform--Embedded



all: gamerom bootrom

prereq:
	@mkdir -p build

clean:
	$(RM) -rf build

# development is made easier by loading bootrom into 1873.cpu-u25
# then romulator can be quickly loaded to a single large rom on the ROM board

gamerom: prereq
	@echo "builing development rom at 0x800 for use with sega-boot-rom in cpu rom socket"
	zcc +z80 -vn -O3 -startup=1 -clib=new main.c -o $@ -create-app -DEMBEDDED_USB -DENABLE_BOOTROM -Cz"--rombase=0x0800 --romsize=30720"
	@mv $@* build/ 2>/dev/null || true
	hexdump build/$@.rom
	truncate -s 2K build/$@.bin
	cat build/$@.rom >> build/$@.bin
	truncate -s 28K build/$@.bin
	cat usbrom.bin >> build/$@.bin

bootrom: prereq
	z80asm bootrom.asm -o build/$@.bin
	truncate -s 2K build/$@.bin


# ROM Emulator https://github.com/Kris-Sekula/EPROM-EMU-NG/
# python3 -m pip install serial
# python3 -m pip install PySimpleGUI
# brew install python-tk

PROGRAMMER = python3 ~/Downloads/EPROM_EMU_NG_2.0rc9.py
UART = /dev/cu.usbserial-B00050RO

flash:
	 ${PROGRAMMER} -mem 27256 -spi n -auto y -start 0 build/gamerom.bin ${UART}

