# Resources
A list of GameBoy resources. Some of the files are saved in this directory for offline use.

## Tutorials and Articles
* [Why did I spend 1.5 months creating a Gameboy emulator?](https://blog.rekawek.eu/2017/02/09/coffee-gb/)
* [The Ultimate Game Boy Talk (33c3)](https://www.youtube.com/watch?v=HyzD8pNlpwI)
    * [slides](https://www.pagetable.com/?p=1099)
    * My own notes on the talk below
* [GameBoy Emulation in Javascript](http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-The-CPU)

## Instruction Set
* [GameBoy CPU Manual](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
	* [Hacker News Discussion](https://news.ycombinator.com/item?id=19663009)
* [Gameboy CPU (LR35902) instruction set](http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html)
* [Decoding Z80 Opcodes](http://www.z80.info/decoding.htm)
* [Decoding GameBoy Z80 Opcodes](https://gb-archive.github.io/salvage/decoding_gbz80_opcodes/Decoding%20Gamboy%20Z80%20Opcodes.html)
	Based on Decoding Z80 Opcodes

## Other
* [Gameboy Bootstrap ROM](http://gbdev.gg8.se/wiki/articles/Gameboy_Bootstrap_ROM)

## Notes on the [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI)

### Specifications
[timestamp](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=5m55s)
* 1 MHz CPU, 8-bit
* 8KB RAM (CPU)
* 8KB VRAM (video)
* 160x144 resoution 
* 4 simultaneous colors
* 10 sprites/line

### DMG CPU (System on a Chip)
[timestamp](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=8m57s)
What is included on the board:
* CPU
* Interrupt controller
* Timer
* Memory
* Boot ROM
* Joypad Input
* Serial data transfer
* Sound controller
* Pixel Processing Unit

### CPU
Sharp LR35902
* Mix between an Intel 8080 and Zilog Z80

[timestamp: core architecture of the 8080](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=10m52s)
Registers
* A - accumulator
* F - flag register (zero and carry)
* B, C, D, E, H, L registers
    * Can combine BC, DE, HL to get 16-bit registers
* In total, four 16-bit registers, and seven 8-bit registers plus 1 special 8-bit register

Instructions
* Loads, stores
* 16-bit stack
* Arithmetic/logic
* Rotate
* Control flow, jump, call, return
* Misc: clearing carry, nop, halt, disable/enable interrupts, ...

[timestamp: Interrupt Model](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=12m24s)
* Not a interrupt vector
* Jumps to a fixed locations in RAM
* Different addresses for different interrupts
* Software interrupts
    * When you first turn on 8080, starts at address 0

Supported Z80 features
* Shifts, relative jumps, return from interrupts

[timestamp: New Features](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=14m03s)
* Post increment/decrement
* Zero page
    * Top-most page in RAM (0xFF00-0xFFFF)

Opcode Table
* CB prefix

[timestamp: Address space](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=17m06s)
* 8-bit CPU with 16-bit address space (64KB)
* ROM, video RAM, external RAM, internal RAM
* ORAM, I/O, HRAM

ROM
* 32 KB
* Anything larger, add additional memory bank controller
* External RAM for saving state in a battery-backed cartridges

Boot ROM
* Built into GameBoy
* First screen, logo
* Compare logos, checksums

[timestamp: ROM header](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=21m17s)

I/O and HRAM
* Zero page

Serial Data Transfer
* Connecting two GameBoys

Timer

[timestamp: Interrupt Controller](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=23m35s)
* 5 interrupts

[timestamp: Sound Controller](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=24m09s)
* 4 voices, 5 registers each
* Little Sound DJ

[timestamp: Pixel Processing Unit](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=29m18s)
* Graphics, 12 registers
* 8x8 pixel tile-based

Tile
* 8x8 pixels
* 4 colors
* 16 bytes to describe a single tile
* Can map color `00` to `11`
* 20x18 tiles viewport
    * Video RAM (32x32 tiles)
* Larger screens?
    * Draw columns before viewport hits them
* Window layer (no translucency)
    * Used for scoreboards

Sprites
Also called objects
* Don't have to fit in 8x8 tile
* Each sprite has an OAM
    * x-position, y-position, etc.
* 8x8 grid with tranlucency
* Can only really use 3 colors (since 4th color is transparency)
* Stored in OAM RAM
* Can combine sprites to generate larger sprites

[timestamp: VRAM Memory Map](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=39m09s)

Vertial Timing (PPU)
* Draws from top to bottom, left to right
