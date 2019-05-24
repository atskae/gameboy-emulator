#ifndef GB_CPU_H
#define GB_CPU_H

enum reg {
	REG_A,
	REG_B,
	REG_C,
	REG_D,
	REG_E,
	REG_F, // flag register
	REG_H,
	REG_L,
	NUM_REGS
};

class CPU {

	private:
		// registers
		unsigned char regs[NUM_REGS]; // 8-bit registers 
		unsigned short sp; // 16-bit stack pointer 
		unsigned short pc; // 16-bit program counter
	
		char* rom; // gameboy cartridge
		int num_bytes_rom;

	public:
		// constructor
		CPU(char* rom_name);
		
		void decode(unsigned char opcode);

		// destructor
		~CPU();

};

#endif // GB_CPU_H
