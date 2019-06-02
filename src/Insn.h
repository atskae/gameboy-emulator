#ifndef GB_INSN_H
#define GB_INSN_H

#include "Reg.h"

class Insn {
	public:
		// used for debugging
		unsigned char* bytes; // raw bytes 
		int size; // in bytes

		reg_t rd; // target register
		reg_t rs; // source register
		unsigned short imm; // immediate 8-bit or 16-bit data
	
		int num_cycles;
	
		Insn(unsigned char* bytes, int size);
		~Insn();
};

/* Instruction Classes */ 

class NOP : public Insn {

};

// loads
class LD : public Insn {

};

#endif // GB_INSN_H
