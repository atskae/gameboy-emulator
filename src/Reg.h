#ifndef GB_REG_H
#define GB_REG_H

#include <string>

enum reg_t {
	REG_A,
	REG_AF,
	REG_A8,
	REG_A16,
	REG_B,
	REG_BC,
	REG_C,
	REG_CB,
	REG_D,
	REG_DE,
	REG_D8,
	REG_D16,
	REG_E,
	REG_F, // flag register
	REG_H,
	REG_HL,
	REG_HL_P, // HL+ ; "HL-plus"
	REG_HL_M, // HL- ; HL-minus
	REG_00H,
	REG_08H,
	REG_10H,
	REG_18H,
	REG_20H,
	REG_28H,
	REG_R8,
	REG_30H,
	REG_38H,
	REG_L,
	REG_NZ,
	REG_NC,
	REG_SP,
	REG_SP_R8, // why???
	REG_Z,
	NUM_REGS,
	REG_INVALID
};

reg_t get_reg(std::string token);

// describes what occurs to the flag on insn execution
enum flag_op_t {
	FLAG_EXEC, // set flag depending on the outcome of the insn execution
	FLAG_SET, // always set flag to True when insn executes
	FLAG_RESET, // always set set flag to False when insn executes
	FLAG_NONE, // insn execution does not affect flag
};

#endif // GB_REG_H
