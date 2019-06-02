#include "Insn.h"
#include "Reg.h"

Insn::Insn(unsigned char* bytes, int size):
	rd(REG_INVALID),
	rs(REG_INVALID),
	imm(0)
{
	
}
