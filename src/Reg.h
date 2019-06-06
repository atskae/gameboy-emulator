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
	REG_30H,
	REG_38H,
	REG_L,
	REG_NZ,
	REG_NC,
	REG_R8,
	REG_SP,
	REG_SP_R8, // why???
	REG_Z,
	NUM_REGS,
	REG_INVALID
};

// describes what occurs to the flag on insn execution
enum flag_op_t {
	FLAG_OP_EXEC, // set flag depending on the outcome of the insn execution
	FLAG_OP_RESET, // always set set flag to False when insn executes
	FLAG_OP_SET, // always set flag to True when insn executes
	FLAG_OP_NONE, // insn execution does not affect flag
	FLAG_OP_INVALID
};

// each insn will have an array of flag_t, for each flag: z, n, h, c
struct flag_t {
	bool val;
	flag_op_t flag_op;
};

// index into the flags array of each insn
#define FLAG_Z 0
#define FLAG_N 1
#define FLAG_H 2
#define FLAG_C 3

reg_t get_reg(std::string token);
flag_op_t get_flag_op(std::string token);

#endif // GB_REG_H
