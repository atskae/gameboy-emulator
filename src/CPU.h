#ifndef GB_CPU_H
#define GB_CPU_H

#include "Insn.h"

#define NUM_REGS 8 // four 16-bit registers, each can be split in half

#define MEMORY_SIZE 0xFFFF // p,8
#define ROM_START_ADDR 0x0100 // p.10

class CPU {

	private:
		// instruction set table
		Insn* insn_table[16][16];

		// registers (p.61)
		unsigned char regs[NUM_REGS]; // 8-bit registers ; use enum reg to index into regs[]
		unsigned short sp; // 16-bit stack pointer 
		unsigned short pc; // 16-bit program counter

		char memory[MEMORY_SIZE];	
		int rom_size; // in bytes

	public:
		// constructor
		CPU(const char* rom_name);
	
		// methods	
		Insn decode(); // decodes 1 instruction at pc

		// destructor
		~CPU();

};

#endif // GB_CPU_H
