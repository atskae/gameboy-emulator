#ifndef GB_INSN_H
#define GB_INSN_H

#include "Reg.h"

class Insn {
	public:
		std::string op_str; // name of the instruction (ex. 'LD')
		unsigned char* bytes; // raw bytes 
		int size; // in bytes

		reg_t rd; // target register
		reg_t rs; // source register
		bool rd_mem; // if True, dereference rd
		bool rs_mem; // if True, dereference rs
		unsigned short imm; // immediate 8-bit or 16-bit data
	
		int cycles; // duration

		// flags that this instruction modifies
		bool z_f;
		bool n_f;
		bool h_f;
		bool c_f;

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
