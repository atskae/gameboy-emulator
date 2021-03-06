# Source Files
This directory contains the source files of the GameBoy emulator.

## Build
To build the GameBoy emulator, run:
```
make
```
This builds an executable called `gameboy`.

To run the GameBoy emulator `gameboy`, run:
```
./gameboy <ROM file>
```
where `<ROM file>` is a GameBoy cartridge binary (ROM). Sample ROMs can be found in the `../roms` directory.

## Source File Descriptions
* `main.cpp`
* `CPU.cpp`
* `opcodes.csv` Contains opcodes extracted from the [Gameboy CPU (LR35902) instruction set](http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html) table using the parsing script `../opcodes/parse.py`
