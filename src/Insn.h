#ifndef GB_INSN_H
#define GB_INSN_H

enum insn_t {
	LD8, // 8-bit Loads
	LD16, // 16-bit Loads
	NOP,
	INVALID
};

class Insn {
	public:
		// used for debugging
		unsigned char* bytes; // raw bytes 
		int num_bytes; // length of instruction in bytes

		insn_t insn; // type of instruction (ex. 8-bit LD, 16-bit LD, etc... many opcodes can fall under "8-bit LD")
		reg_t rd; // target register
		reg_t rs; // source register
		unsigned short imm; // immediate 8-bit or 16-bit data
	
		int num_cycles;
	
		Insn(unsigned char* bytes, int num_bytes);
		~Insn();
};

#endif // GB_INSN_H
