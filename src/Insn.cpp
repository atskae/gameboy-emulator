#include "Insn.h"
#include "Reg.h"

Insn::Insn(unsigned char* bytes, int num_bytes): // raw insn bytes
	insn(INVALID),
	rd(REG_INVALID),
	rs(REG_INVALID),
	imm(0)
{
	this->bytes = bytes;
	this->num_bytes = num_bytes;
	unsigned char opcode = bytes[num_bytes-1];

	switch(opcode) {
		case 0x06:
			this->rd = REG_D;
			this->insn = LD8; // 8-bit Load
			break;
		case 0x0E:
			this->rd = REG_C;
			this->insn = LD8; // 8-bit Load
			break;
		case 0x16:
			this->rd = REG_C;
			this->insn = LD8; // 8-bit Load
			break;
		case 0x1E:
			this->rd = REG_E;
			this->insn = LD8; // 8-bit Load
			break;
		case 0x26:
			this->rd = REG_H;
			this->insn = LD8; // 8-bit Load
			break;
		case 0x2E:
			this->rd = REG_L;
			this->insn = LD8; // 8-bit Load
			break;
		default:
			this->insn = INVALID;
			break;
	}
}
