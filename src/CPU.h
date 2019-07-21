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
		Insn* cb_insn_table[16][16]; // insn with CB prefix

		// registers (p.61)
		unsigned short regs[NUM_REGS/2]; // 8-bit registers ; use enum reg to index into regs[]
		unsigned short pc; // 16-bit program counter
		unsigned short sp; // 16-bit stack pointer 

		char memory[MEMORY_SIZE];	
		int rom_size; // in bytes

	public:
		// constructor
		CPU(const char* rom_name);
	
		// methods	
		unsigned short read_reg(operand_t reg);
		void write_reg(operand_t reg, unsigned short val);
		void print(short mem_start); // print CPU state and memory specified by parameters
		void print_mem(int start, int end);

		Insn decode(); // decodes 1 instruction at pc
		void execute(Insn insn);

		// destructor
		~CPU();

};

#endif // GB_CPU_H
