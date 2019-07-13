#include "Insn.h"
#include "Reg.h"

#include <string>
#include <iostream>

Insn::Insn(op_t op, std::string op_str):
	rd(REG_INVALID),
	rs(REG_INVALID),
	imm(0)
{
	this->op = op;
	this->op_str = op_str;	
}

void Insn::print() {
	printf("%s | ", this->insn_str.c_str());
	// printf("%i, ", this->size);
	for(int i=0; i<this->size; i++) {
		printf("%02x ", this->bytes[i]);
	}
	printf("\n");
}

// destructor
Insn::~Insn() {

}

/* Instruction Classes */

NOP::NOP(op_t op, std::string op_str):
	Insn(op, op_str) 
{
}

LD::LD(op_t op, std::string op_str):
	Insn(op, op_str) 
{
}

INC::INC(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

DEC::DEC(op_t op, std::string op_str):
	Insn(op, op_str)
{
}


RLCA::RLCA(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

ADD::ADD(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

RRCA::RRCA(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

STOP::STOP(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

RLA::RLA(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

JR::JR(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

RRA::RRA(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

DAA::DAA(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

CPL::CPL(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

SCF::SCF(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

CCF::CCF(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

HALT::HALT(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

ADC::ADC(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

SUB::SUB(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

SBC::SBC(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

AND::AND(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

XOR::XOR(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

OR::OR(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

CP::CP(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

RET::RET(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

POP::POP(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

JP::JP(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

CALL::CALL(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

PUSH::PUSH(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

RST::RST(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

PREFIX::PREFIX(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

INVALID::INVALID(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

RETI::RETI(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

LDH::LDH(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

DI::DI(op_t op, std::string op_str):
	Insn(op, op_str)
{
}

EI::EI(op_t op, std::string op_str):
	Insn(op, op_str)
{
}
