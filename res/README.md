# Resources
A list of GameBoy resources. Some of the files are saved in this directory for offline use.

## Tutorials and Articles
* [Why did I spend 1.5 months creating a Gameboy emulator?](https://blog.rekawek.eu/2017/02/09/coffee-gb/)
* [The Ultimate Game Boy Talk (33c3)](https://www.youtube.com/watch?v=HyzD8pNlpwI)
    * [Presentation slides](https://www.pagetable.com/?p=1099)
    * My own notes on the talk below
* [GameBoy Emulation in Javascript](http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-The-CPU)

## Instruction Set
* [GameBoy CPU Manual](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
	* [Hacker News Discussion](https://news.ycombinator.com/item?id=19663009)
* [Gameboy CPU (LR35902) instruction set](http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html)
* [Decoding Z80 Opcodes](http://www.z80.info/decoding.htm)
* [Decoding GameBoy Z80 Opcodes](https://gb-archive.github.io/salvage/decoding_gbz80_opcodes/Decoding%20Gamboy%20Z80%20Opcodes.html)
	Based on Decoding Z80 Opcodes
* [Pan Docs](http://bgb.bircd.org/pandocs.htm)
    * `"Everything you wanted to know about GAMEBOY * but were afraid to ask"`

## Other
* [Gameboy Bootstrap ROM](http://gbdev.gg8.se/wiki/articles/Gameboy_Bootstrap_ROM)
* [Sound hardware](https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware)
* [Blargg's tests](https://gbdev.gg8.se/files/roms/blargg-gb-tests/)
    * A set of ROMS that test emulated Gameboy hardware (CPU instructions/timing, graphics, sound)
* [Gameboy Color](https://en.wikipedia.org/wiki/Game_Boy_Color)
    * [Pan Docs](http://bgb.bircd.org/pandocs.htm) has specifications on Gameboy color
* [How QEMU disassembles instructions](https://github.com/qemu/qemu/blob/cbf01142b2aef0c0b4e995cecd7e79d342bbc47e/tcg/tci.c)
    * Uses a giant switch statement on the instruction opcode

## Notes on the [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI)

### [Specifications](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=5m55s)
* 1 MHz CPU, 8-bit
* 8KB RAM (CPU)
* 8KB VRAM (video)
* 160x144 resoution 
* 4 simultaneous colors
* 10 sprites/line

### [DMG CPU (System on a Chip)](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=8m57s)
What is included on the board:
* CPU
* Interrupt controller
* Timer
* Memory
* Boot ROM
* Joypad input
* Serial data transfer
* Sound controller
* Pixel Processing Unit (video controller)

### [CPU](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=9m19s)
Sharp LR35902
* Mix between an Intel 8080 and Zilog Z80

[Core Architecture from the 8080](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=10m52s)

Registers
* A - accumulator
    * arithemtic, logic (cannot do with other registers)
* F - flag register (zero and carry)
* B, C, D, E, H, L registers (8-bit)
    * Can combine BC, DE, HL to get 16-bit registers (to get pointers, for example)
* In total, four 16-bit registers, and seven 8-bit registers plus 1 special 8-bit register (value at the memory address stored in the HL register)

[Instructions](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=11m47s)
* Loads, stores
* 16-bit stack
* Arithmetic/logic (only the accumulator register can do this, but increment/decrement instructions can be done by any register)
* Rotate
* Control flow, jump, call, return, conditional
* Misc: clearing carry, nop, halt, disable/enable interrupts, ...

[Interrupt Model](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=12m24s)
* Not a interrupt vector
* Jumps to a fixed locations in RAM, at the beginning of RAM
* Different addresses for different interrupts
* Software interrupts
    * When you first turn on 8080, starts at address 0

Unsupported 8080 Features
* Flags, port IO

Supported Z80 Features
* Shifts, relative jumps, return from interrupts

Unsupported Z80 Features
* Second register set, auto-increment/decrement, other instructions (loop instructions)

[New Features](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=14m03s)
* Post increment/decrement
* Zero page
    * Not actually page 0 in RAM
    * Top-most page in RAM (0xFF00-0xFFFF)
    * Just an optimized way to access this specific page in RAM
* Stack instructions (store stack pointer, swap nibble, power save instruction)

[Opcode Table](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=15m05s)
* CB prefix
    * Hosts an additional 256 instructions (rotate/shift from Z80, for example)

[About the CPU Clock](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=15m40s)
* What does X clocks at 4MHz mean?
* The whole system is memory-bound. The CPU can only go as fast as the memory can provide the data
    * Can say this CPU is clocked at 1MHz at 4 clocks width
* [System Clock](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=16m25s)
    * CPU 4MHz
    * RAM 1MHz
    * PPU 4MHz (how fast the pixels are drawn)
    * VRAM 2MHz
    * But most of the numbers can be expressed as 1MHz
        * 1 machine cycle @ 1MHz

### [Address Space](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=17m06s)
* 8-bit CPU with 16-bit address space due to 16-bit pointers (64KB)

Starting from address `0x0000`
* 32KB of ROM that comes from the game cartridge (simply mapped into the address space)
    * Boot ROM
* Video RAM
* External RAM
    * Can optionally come from the cartridge
* Internal RAM (just RAM)
* Empty space
* (0xFE00 - FEA0) OAM RAM
    * Special-purpose video RAM
* Last page (zero page)
    * I/O (peripherals/registers for sound/video)
    * HRAM (127 bytes)

[Games are not restricted to be 32KB](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=18m05s)
* Some games only need 32KB (Tetris)
* Theoretically no limit
    * Some games go up to 2MB
* Any games larger than 32KB, add additional memory bank controller (MBC) on the cartridge
    * MBC can switch banks
        * 2 banks (each bank is 16KB in the ROM)
* External RAM can also switch banks in a similar manner
    * For saving state in a battery-backed cartridges

[Boot ROM](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=19m16s)
* Address `0x0000`-`0x00FF`
* CPU starts at location `0x0000` in memory
* First screen, logo and chime sound
* Program that is built into GameBoy
    * Initializes RAM, sound, set up logo, scrolls logo, plays the chime
    * Then it decodes logo, compares the logo (checksum)
        * The game has to have a copy of the Nintendo logo inside
        * If the logos do not match, the game does not boot
        * This is so Nintendo could control which games could be released for the platform
    * Next, it checksums the header
    * Finally, it turns off ROM and continues execution into the game cartridge

[ROM header](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=21m17s)

Header starts at address `0x1000` (entry point)
* Contains metadata, checksums, logo, etc.

### [I/O and HRAM](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=21m40s)
* In the top-most page in the address space (zero page)
    * Recall that the zero page can be accessed specifically (instructions for this purpose exist)
* [All of the registers for I/O and HRAM](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=22m00s)
    * For interrupts, joypad controller, sound, timer, PPU

[Joypad Input](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=22m10s)
* The buttons for directions, `A`/`B` buttons, `start`/`select` buttons
* [Uses 6 GPIOs](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=22m21s)
    * Select a column, then row, to see which button was pressed

[Serial Data Transfer](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=22m37s)
* Connecting two GameBoys
* Link cable
    * One wire for data going in one direction
    * Another wire for data in the other direction
    * Third wire for the clock
* The GameBoy needs to decide which of the two GameBoys will be sending the clock and receiving the clock

[Timer](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=23m11s)
* Only 1 timer in the system
* TMA (modular) register (set the start value)
* Select one of four different speeds
* Once the timer is started, it counts up until overflow
    * On overflow, it reloads the modulo value, and can optionally generate an interrupt

[Interrupt Controller](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=23m35s)
* Supports 5 different interrupts
    * V-blank, LCD STAT (deals with the Pixel Processing Unit)
    * Timer
    * Serial (when a new byte has been received)
    * Joypad (when a button has been pressed)
* Interrupt Enable register
* Interrupt Flag register (which interrupt is still pending)
* Depending on the interrupt (timer, serial, etc.) the CPU will automatically jump to the location in memory
    * Don't have to explicitly check what interrupt it was

### [Sound Controller](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=24m09s)
* Many, many registers...
* 4 voices (Pulse A, Pulse B, Wave, Noise), 5 registers each (control, frequency, volumn, length, sweep)
* All voices have
    * Trigger bit (turns on the voice)
    * Length bit and length register (can use this to decide when to turn off the voice after a period of time)
* [Wave register](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=25m06s)
    * Plays any sound wave
    * Has an extra 16 bytes of register (32 entries of 4 bits each)
        * Use these to describe any wave form you like
    * Frequency bits to control the pitch (how fast the wave table is played)
    * 2 bits of volume
        * 100%, 75%, 50%, 0% (muted)
* [2 Pulse registers (voices)](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=26m05s)
    * Both pulses have the same register format
    * Cannot specify a waveform
        * It is fixed, it is always a pulse
        * But can control the ratio of low and high (2 bits of control)
    * New concept of a *volume sweep*
        * Volume can go up/down
    * Only Pulse A has a concept of a *frequency sweep*
        * Up/down effect
* [Noise register (voice)](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=27m27s)
    * Shift register that can generate pseudo-random numbers
    * 15-bit or 7-bit mode
        * It will perform one of two waveforms
* Sound controller also has 3 additional general-purpose registers
    * Volume for left and right channels
    * Cartridges can have their own audio controllers
    * Power bit (to save energy)
* [Little Sound DJ](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=28m28s)
    * Can still compose songs with GameBoy sound effects

### [Pixel Processing Unit](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=29m18s)
* Makes graphics, 12 registers
* Specifications
    * 160x144 pixels
    * 4 shades of gray
    * 8x8 pixel tile-based, 20x18 tiles
    * 40 sprites (10 per line)
    * 8KB VRAM

[Pixel Tiles](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=29m46s)
* 8x8 pixel tiles
* 4 colors
* 16 bytes to describe a single tile
    * Every line of pixel needs 2 bytes
* Can map a color `00` to `11` (choosing a palette)
* 256 tiles in the system (background tile data)

* 20x18 tiles viewport
    * Video RAM (32x32 tiles)
    * Scrolling moves the viewport across the full 32x32 screen
    * Like a camera

* Larger screens? Inifite scrolling? (like Super Mario Land)
    * Draw columns before viewport hits them

* Window layer (no translucency)
    * Used for scoreboards

[Sprites](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=33m57s)

Also called objects
* Don't have to fit in 8x8 tile
* Each sprite has an OAM (object attribute map)
    * x-position, y-position, flip horizontal/vertical, etc.
* 8x8 grid with tranlucency
* 256 tiles possible
* Can only really use 3 colors (since 4th color is transparency)
    * Can select Palette 0 or 1
* Priority (order of view, what gets drawn over pixels "behind")
* 40 sprites in screen
    * 10 sprites per line in screen
* Stored in OAM RAM
    * Each entry is 4 bytes
* Can combine sprites to generate larger sprites
    * Can set sprite height to 16 bits (but this is a global option)
* 3 different layers
    * Can turn off display for some pixels?
    * Turn off LCD

[VRAM Memory Map](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=39m09s)
* 4KB sprite tiles
* 4KB background tiles
* 1KB background map
* 1KB window map
* Only have 8KB of video RAM
    * Can overlap (since everything can't fit)
    * Sprite tiles, background tiles

[Vertial Timing (PPU)](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=40m24s)
* Draws from top to bottom, left to right
    * Like a CRT TV screen
* Draws the picture 60 times a second
* Useful to understand this if different parts of the screen do different things
    * Different scroll effects by setting registers
    * Can see which lines are about to be drawn
    * `SCX` scroll X register stores a line
    * `LYC` register
    * Can control which lines are drawn (can set interrupt for when a certain line is drawn)
    * Scrolling register
* [Applying effects on every line](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=43m00s)
    * Changing `SCX` per line
    * Warp lines
    * Vertical/horizontal scroll

[Horizontal Timing](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=44m41s)
* What happens while a line is being drawn?
    * Pixel transfer mode of the PPU (43 clocks)
    * 144 + 10 lines on the screen
    * After a line is drawn, OAM search and H-Blank occurs before the next line is drawn
* 4 modes in the PPU
    * CPU can read this and trigger interrupts
    * OAM Search mode
        * Determines which sprites are visible in the line
        * Adds to visible sprites array
        * Takes 20 cycles
        * OAM Search CPU Bug
    * CPU connects to RAM
    * PPU connects to Video RAM and OAM RAM
    * CPU goes through PPU to access Video RAM
    * CPU needs to know what mode the PPU is in to access Video RAM
        * CPU can only access OAM during V-Blank/H-Blank mode
    * CPU writes updated sprite information to shadow OAM
        * DMA will do this (160 clocks)

[Pixel Pipeline](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=49m17s)
* Pixel FIFO
    * How the GameBoy draws its picture
    * Stores pixels to be sent to the LCD
    * Fetcher fetches background tiles pixel
* Horizontal scrolling
    * Pixels can be discarded (not placed on the LCD)
* Can clear FIFO if there is a window
    * Fetcher will start getting pixels from the window
* Sprites
    * 10 comparators for sprite positions
    * FIFO always needs at least 8 pixels since titles are overlayed on top
* GameBoy can pause drawing pixels, while a CRT cannot

[Pixel Mixing](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=54m37s)
* Pixel FIFO does not actually store pixel colors
    * Bit combination and source (sprite or background)
    * Applies transparency and draws background tiles when needed

Applying the Palettes
* Apply palette at the end when the pixel is placed onto LCD
* Colorization
    * Similar on GameBoy Color

### [GameBoy Games Development](https://www.youtube.com/watch?v=HyzD8pNlpwI&t=57m11s)
* Rednex GameBoy Development System
* BGB Emulator/Debugger
* Everdrive GB (run on real hardware)
* Game Boy Camera
