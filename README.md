# sega-g80-vector-homebrew


## Follow along as we develop a new game for a SEGA G80 vector display arcade from 1982.

* Does not use emulation or Rasberry Pi or MAME
* Runs as it would have in 1982 on the original Sega G80 boardsets
* Programmed in C rather than period correct assembly
* Runs on a Zilog Z80 at 3.86712 MHz, only 46KB ROM and 2KB RAM
* Assisted by XY vector display hardware and two 8035 CPUs for sound and speech

# Building the ROM yourself
```
export PATH=${PATH}:/Users/jmathews/Desktop/z88dk/bin
export ZCCCFG=/Users/jmathews/Desktop/z88dk/lib/config
make
```
## Dependencies
* https://github.com/z88dk/z88dk/releases
* export PATH=${PATH}:/Users/jmathews/Desktop/z88dk/bin
* export ZCCCFG=/Users/jmathews/Desktop/z88dk/lib/config
* ROM Emulator https://github.com/Kris-Sekula/EPROM-EMU-NG/

[![screenshot](https://img.youtube.com/vi/7MGQQfak8ME/0.jpg)](https://youtube.com/playlist?list=PL5WwuS3ViybqfLWkKmgaT5_N2kVawZYZk)

# Bonus features
## Ever wanted to dump the vector graphics from the factory ROMs ?
```
python3 ./sega-vector-dump.py
```
![screenshot](sega.png)
![screenshot](sega80boardset.jpg)

