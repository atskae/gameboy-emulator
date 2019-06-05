#ifndef GB_INSN_H
#define GB_INSN_H

#include <string>

#include "Reg.h"

enum insn_t {
	INSN_NOP,
	INSN_LD,
	INSN_INC,
	INSN_DEC,
	INSN_RLCA,
	INSN_ADD,
	INSN_RRCA,
	INSN_STOP,
	INSN_RLA,
	INSN_JR,
	INSN_RRA,
	INSN_DAA,
	INSN_CPL,
	INSN_SCF,
	INSN_CCF,
	INSN_HALT,
	INSN_ADC,
	INSN_SUB,
	INSN_SBC,
	INSN_AND,
	INSN_XOR,
	INSN_OR,
	INSN_CP,
	INSN_RET,
	INSN_POP,
	INSN_JP,
	INSN_CALL,
	INSN_PUSH,
	INSN_RST,
	INSN_PREFIX,
	INSN_INVALID,
	INSN_RETI,
	INSN_LDH,
	INSN_DI,
	INSN_EI
};

class Insn {
	public:
		//std::string op_str; // name of the instruction (ex. 'LD')
		insn_t insn;
		unsigned char* bytes; // raw bytes 
		int size; // in bytes

		reg_t rd; // target register
		reg_t rs; // source register
		bool rd_mem; // if True, dereference rd
		bool rs_mem; // if True, dereference rs
		unsigned short imm; // immediate 8-bit or 16-bit data
	
		int cycles; // duration

		// flags that this instruction modifies
		flag_op_t z_f;
		flag_op_t n_f;
		flag_op_t h_f;
		flag_op_t c_f;

		Insn(insn_t insn);
		~Insn();
};

/* Instruction Classes */ 

class NOP : public Insn {
	public:
		NOP(insn_t insn);
		~NOP();
};

// loads
class LD : public Insn {
	public:
		LD(insn_t insn);
		~LD();
};

class INC : public Insn {
	public:
		INC(insn_t insn);
		~INC();
};

class DEC : public Insn {
	public:
		DEC(insn_t insn);
		~DEC();
};

// rotate left
class RLCA : public Insn {
	public:
		RLCA(insn_t insn);
		~RLCA();
};

class ADD : public Insn {
	public:
		ADD(insn_t insn);
		~ADD();
};

class RRCA : public Insn {
	public:
		RRCA(insn_t insn);
		~RRCA();
};

class STOP : public Insn {
	public:
		STOP(insn_t insn);
		~STOP();
};

class RLA : public Insn {
	public:
		RLA(insn_t insn);
		~RLA();
};

class JR : public Insn {
	public:
		JR(insn_t insn);
		~JR();
};

class RRA : public Insn {
	public:
		RRA(insn_t insn);
		~RRA();
};

class DAA : public Insn {
	public:
		DAA(insn_t insn);
		~DAA();
};

class CPL : public Insn {
	public:
		CPL(insn_t insn);
		~CPL();
};

class SCF : public Insn {
	public:
		SCF(insn_t insn);
		~SCF();
};

class CCF : public Insn {
	public:
		CCF(insn_t insn);
		~CCF();
};

class HALT : public Insn {
	public:
		HALT(insn_t insn);
		~HALT();
};

class ADC : public Insn {
	public:
		ADC(insn_t insn);
		~ADC();
};

class SUB : public Insn {
	public:
		SUB(insn_t insn);
		~SUB();
};

class SBC : public Insn {
	public:
		SBC(insn_t insn);
		~SBC();
};

class AND : public Insn {
	public:
		AND(insn_t insn);
		~AND();
};

class XOR : public Insn {
	public:
		XOR(insn_t insn);
		~XOR();
};

class OR : public Insn {
	public:
		OR(insn_t insn);
		~OR();
};

class CP : public Insn {
	public:
		CP(insn_t insn);
		~CP();
};

class RET : public Insn {
	public:
		RET(insn_t insn);
		~RET();
};

class POP : public Insn {
	public:
		POP(insn_t insn);
		~POP();
};

class JP : public Insn {
	public:
		JP(insn_t insn);
		~JP();
};

class CALL : public Insn {
	public:
		CALL(insn_t insn);
		~CALL();
};

class PUSH : public Insn {
	public:
		PUSH(insn_t insn);
		~PUSH();
};

class RST : public Insn {
	public:
		RST(insn_t insn);
		~RST();
};

class PREFIX : public Insn {
	public:
		PREFIX(insn_t insn);
		~PREFIX();
};

class INVALID : public Insn {
	public:
		INVALID(insn_t insn);
		~INVALID();
};

class RETI : public Insn {
	public:
		RETI(insn_t insn);
		~RETI();
};

class LDH : public Insn {
	public:
		LDH(insn_t insn);
		~LDH();
};

class DI : public Insn {
	public:
		DI(insn_t insn);
		~DI();
};

class EI : public Insn {
	public:
		EI(insn_t insn);
		~EI();
};

#endif // GB_INSN_H
