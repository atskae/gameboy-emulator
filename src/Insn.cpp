#include "Insn.h"
#include "Reg.h"

Insn::Insn(unsigned char* bytes, int num_bytes): // raw insn bytes
	insn(INVALID),
	rd(REG_INVALID),
	rs(REG_INVALID),
	imm(0)
{
	
}
