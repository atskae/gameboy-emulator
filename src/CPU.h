#ifndef GB_CPU_H
#define GB_CPU_H

#include "Reg.h"

class CPU {

	private:
		// registers
		unsigned char regs[NUM_REGS]; // 8-bit registers ; use enum reg to index into regs[]
		unsigned short sp; // 16-bit stack pointer 
		unsigned short pc; // 16-bit program counter
	
		char* rom; // gameboy cartridge
		int num_bytes_rom;

	public:
		// constructor
		CPU(char* rom_name);
		
		void decode(unsigned char* bytes, int num_bytes);

		// destructor
		~CPU();

};

#endif // GB_CPU_H
