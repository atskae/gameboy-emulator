#include "Insn.h"
#include "Reg.h"

#include <string>

Insn::Insn(insn_t insn):
	rd(REG_INVALID),
	rs(REG_INVALID),
	imm(0)
{
	this->insn = insn;	
}

/* Instruction Classes */

NOP::NOP(insn_t insn):
	Insn(insn) 
{
}

LD::LD(insn_t insn):
	Insn(insn) 
{
}

INC::INC(insn_t insn):
	Insn(insn)
{
}

DEC::DEC(insn_t insn):
	Insn(insn)
{
}


RLCA::RLCA(insn_t insn):
	Insn(insn)
{
}

ADD::ADD(insn_t insn):
	Insn(insn)
{
}

RRCA::RRCA(insn_t insn):
	Insn(insn)
{
}

STOP::STOP(insn_t insn):
	Insn(insn)
{
}

RLA::RLA(insn_t insn):
	Insn(insn)
{
}

JR::JR(insn_t insn):
	Insn(insn)
{
}

RRA::RRA(insn_t insn):
	Insn(insn)
{
}

DAA::DAA(insn_t insn):
	Insn(insn)
{
}

CPL::CPL(insn_t insn):
	Insn(insn)
{
}

SCF::SCF(insn_t insn):
	Insn(insn)
{
}

CCF::CCF(insn_t insn):
	Insn(insn)
{
}

HALT::HALT(insn_t insn):
	Insn(insn)
{
}

ADC::ADC(insn_t insn):
	Insn(insn)
{
}

SUB::SUB(insn_t insn):
	Insn(insn)
{
}

SBC::SBC(insn_t insn):
	Insn(insn)
{
}

AND::AND(insn_t insn):
	Insn(insn)
{
}

XOR::XOR(insn_t insn):
	Insn(insn)
{
}

OR::OR(insn_t insn):
	Insn(insn)
{
}

CP::CP(insn_t insn):
	Insn(insn)
{
}

RET::RET(insn_t insn):
	Insn(insn)
{
}

POP::POP(insn_t insn):
	Insn(insn)
{
}

JP::JP(insn_t insn):
	Insn(insn)
{
}

CALL::CALL(insn_t insn):
	Insn(insn)
{
}

PUSH::PUSH(insn_t insn):
	Insn(insn)
{
}

RST::RST(insn_t insn):
	Insn(insn)
{
}

PREFIX::PREFIX(insn_t insn):
	Insn(insn)
{
}

INVALID::INVALID(insn_t insn):
	Insn(insn)
{
}

RETI::RETI(insn_t insn):
	Insn(insn)
{
}

LDH::LDH(insn_t insn):
	Insn(insn)
{
}

DI::DI(insn_t insn):
	Insn(insn)
{
}

EI::EI(insn_t insn):
	Insn(insn)
{
}
