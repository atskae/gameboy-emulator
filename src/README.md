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
