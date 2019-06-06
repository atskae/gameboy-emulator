#ifndef GB_INSN_H
#define GB_INSN_H

#include <string>

#include "Reg.h"

enum op_t {
	OP_NOP,
	OP_LD,
	OP_INC,
	OP_DEC,
	OP_RLCA,
	OP_ADD,
	OP_RRCA,
	OP_STOP,
	OP_RLA,
	OP_JR,
	OP_RRA,
	OP_DAA,
	OP_CPL,
	OP_SCF,
	OP_CCF,
	OP_HALT,
	OP_ADC,
	OP_SUB,
	OP_SBC,
	OP_AND,
	OP_XOR,
	OP_OR,
	OP_CP,
	OP_RET,
	OP_POP,
	OP_JP,
	OP_CALL,
	OP_PUSH,
	OP_RST,
	OP_PREFIX,
	OP_INVALID,
	OP_RETI,
	OP_LDH,
	OP_DI,
	OP_EI
};

class Insn {
	public:
		op_t op;
		std::string op_str;
		std::string insn_str; // full insn, with opcode and operands ; for debugging
		unsigned char* bytes; // raw bytes 
		int size; // in bytes

		reg_t rd; // target register
		reg_t rs; // source register
		bool rd_mem; // if True, dereference rd
		bool rs_mem; // if True, dereference rs
		unsigned short imm; // immediate 8-bit or 16-bit data
	
		int cycles; // duration

		// z, n, h, c
		flag_t flags[4];	

		Insn(op_t op, std::string op_str);
		~Insn();
};

/* Instruction Classes */ 

class NOP : public Insn {
	public:
		NOP(op_t op, std::string op_str);
		~NOP();
};

// loads
class LD : public Insn {
	public:
		LD(op_t op, std::string op_str);
		~LD();
};

class INC : public Insn {
	public:
		INC(op_t op, std::string op_str);
		~INC();
};

class DEC : public Insn {
	public:
		DEC(op_t op, std::string op_str);
		~DEC();
};

// rotate left
class RLCA : public Insn {
	public:
		RLCA(op_t op, std::string op_str);
		~RLCA();
};

class ADD : public Insn {
	public:
		ADD(op_t op, std::string op_str);
		~ADD();
};

class RRCA : public Insn {
	public:
		RRCA(op_t op, std::string op_str);
		~RRCA();
};

class STOP : public Insn {
	public:
		STOP(op_t op, std::string op_str);
		~STOP();
};

class RLA : public Insn {
	public:
		RLA(op_t op, std::string op_str);
		~RLA();
};

class JR : public Insn {
	public:
		JR(op_t op, std::string op_str);
		~JR();
};

class RRA : public Insn {
	public:
		RRA(op_t op, std::string op_str);
		~RRA();
};

class DAA : public Insn {
	public:
		DAA(op_t op, std::string op_str);
		~DAA();
};

class CPL : public Insn {
	public:
		CPL(op_t op, std::string op_str);
		~CPL();
};

class SCF : public Insn {
	public:
		SCF(op_t op, std::string op_str);
		~SCF();
};

class CCF : public Insn {
	public:
		CCF(op_t op, std::string op_str);
		~CCF();
};

class HALT : public Insn {
	public:
		HALT(op_t op, std::string op_str);
		~HALT();
};

class ADC : public Insn {
	public:
		ADC(op_t op, std::string op_str);
		~ADC();
};

class SUB : public Insn {
	public:
		SUB(op_t op, std::string op_str);
		~SUB();
};

class SBC : public Insn {
	public:
		SBC(op_t op, std::string op_str);
		~SBC();
};

class AND : public Insn {
	public:
		AND(op_t op, std::string op_str);
		~AND();
};

class XOR : public Insn {
	public:
		XOR(op_t op, std::string op_str);
		~XOR();
};

class OR : public Insn {
	public:
		OR(op_t op, std::string op_str);
		~OR();
};

class CP : public Insn {
	public:
		CP(op_t op, std::string op_str);
		~CP();
};

class RET : public Insn {
	public:
		RET(op_t op, std::string op_str);
		~RET();
};

class POP : public Insn {
	public:
		POP(op_t op, std::string op_str);
		~POP();
};

class JP : public Insn {
	public:
		JP(op_t op, std::string op_str);
		~JP();
};

class CALL : public Insn {
	public:
		CALL(op_t op, std::string op_str);
		~CALL();
};

class PUSH : public Insn {
	public:
		PUSH(op_t op, std::string op_str);
		~PUSH();
};

class RST : public Insn {
	public:
		RST(op_t op, std::string op_str);
		~RST();
};

class PREFIX : public Insn {
	public:
		PREFIX(op_t op, std::string op_str);
		~PREFIX();
};

class INVALID : public Insn {
	public:
		INVALID(op_t op, std::string op_str);
		~INVALID();
};

class RETI : public Insn {
	public:
		RETI(op_t op, std::string op_str);
		~RETI();
};

class LDH : public Insn {
	public:
		LDH(op_t op, std::string op_str);
		~LDH();
};

class DI : public Insn {
	public:
		DI(op_t op, std::string op_str);
		~DI();
};

class EI : public Insn {
	public:
		EI(op_t op, std::string op_str);
		~EI();
};

#endif // GB_INSN_H
