#ifndef GB_OPERAND_H
#define GB_OPERAND_H

#include <string>

enum operand_type_t {
	OPERAND_TYPE_REG,
	OPERAND_TYPE_IMM,
	OPERAND_TYPE_EA,
	OPERAND_TYPE_FLAGS,
	OPERAND_TYPE_PREFIX,
	OPERAND_TYPE_INVALID
};

enum operand_t {
	
	// general purpose registers
	REG_AF=0,
	REG_BC=1,
	REG_DE=2,
	REG_HL=3,
	
	REG_A,
	REG_B,
	REG_C,
	REG_D,
	REG_E,
	REG_F, // flag register
	REG_H,
	REG_L,
	
	REG_SP,
	REG_SP_R8, 
	
	REG_HL_P, // HL+ ; "HL-plus" ; HL is decremented after operation (p.72)
	REG_HL_M, // HL- ; HL-minus ; HL is incremented after operation
	// increment/decrement by one, I assume (src: https://eev.ee/blog/2018/06/19/cheezball-rising-a-new-game-boy-color-game/)

	// immediate values
	IMM_d8, // not a reg ; 8-bit immediate
	IMM_d16, // not a reg ; 16-bit immediate 
	IMM_r8, // not a reg ; 8-bit signed value added to SP
	
	// used in RST (restart) instruction
	// RST XXH pushes present address on stack and jumps to 0x0000 + XXH	
	IMM_00H,
	IMM_08H,
	IMM_10H,
	IMM_18H,
	IMM_20H,
	IMM_28H,
	IMM_30H,
	IMM_38H,

	// effective-address	
	EA_a8, // 8-bit effective address
	EA_a16, // 16-bit effective address
	
	// flags
	FLAGS_NZ,
	FLAGS_NC,
	FLAGS_Z,
	
	// CB prefix
	PREFIX_CB,
	
	OPERAND_INVALID
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

operand_t str_to_operand(std::string token);
std::string operand_to_str(operand_t operand);
std::string operand_type_to_str(operand_type_t operand_type);
flag_op_t get_flag_op(std::string token);
operand_type_t get_operand_type(operand_t operand);

operand_t get_parent_reg(operand_t reg);
operand_t get_upper_reg(operand_t reg);
operand_t get_lower_reg(operand_t reg);

#endif // GB_OPERAND_H
