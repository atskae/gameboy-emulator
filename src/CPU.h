#ifndef GB_CPU_H
#define GB_CPU_H

#include "Insn.h"

struct rom_t {
	char* bytes;
	int size; // in bytes
};

class CPU {

	private:
		// instruction set table
		Insn* insn_table[16][16];

		// registers
		unsigned char regs[NUM_REGS]; // 8-bit registers ; use enum reg to index into regs[]
		unsigned short sp; // 16-bit stack pointer 
		unsigned short pc; // 16-bit program counter
	
		rom_t rom; // gameboy cartridge

	public:
		// constructor
		CPU(char* rom_name);
		
		void decode(unsigned char* bytes, int size); // size in bytes

		// destructor
		~CPU();

};

#endif // GB_CPU_H
