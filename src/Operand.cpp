#include <string>

#include "Operand.h"

operand_t str_to_operand(std::string token) {
	
	operand_t op = OPERAND_INVALID;
	if(token.compare("A") == 0) op = REG_A;
	else if(token.compare("AF") == 0) op = REG_AF;
	else if(token.compare("a8") == 0) op = EA_a8;
	else if(token.compare("a16") == 0) op = EA_a16;
	else if(token.compare("B") == 0) op = REG_B;
	else if(token.compare("BC") == 0) op = REG_BC;
	else if(token.compare("C") == 0) op = REG_C;
	else if(token.compare("CB") == 0) op = PREFIX_CB;
	else if(token.compare("D") == 0) op = REG_D;
	else if(token.compare("DE") == 0) op = REG_DE;
	else if(token.compare("d8") == 0) op = IMM_d8;
	else if(token.compare("d16") == 0) op = IMM_d16;
	else if(token.compare("E") == 0) op = REG_E;
	else if(token.compare("H") == 0) op = REG_H;
	else if(token.compare("HL") == 0) op = REG_HL;
	else if(token.compare("HL+") == 0) op = REG_HL_P;
	else if(token.compare("HL-") == 0) op = REG_HL_M;
	else if(token.compare("L") == 0) op = REG_L;
	else if(token.compare("NC") == 0) op = FLAGS_NC;
	else if(token.compare("NZ") == 0) op = FLAGS_NZ;
	else if(token.compare("r8") == 0) op = IMM_r8;
	else if(token.compare("SP") == 0) op = REG_SP;
	else if(token.compare("SP+r8") == 0) op = REG_SP_R8;
	else if(token.compare("00H") == 0) op = IMM_00H;
	else if(token.compare("08H") == 0) op = IMM_08H;
	else if(token.compare("10H") == 0) op = IMM_10H;
	else if(token.compare("18H") == 0) op = IMM_18H;
	else if(token.compare("20H") == 0) op = IMM_20H;
	else if(token.compare("28H") == 0) op = IMM_28H;
	else if(token.compare("30H") == 0) op = IMM_30H;
	else if(token.compare("38H") == 0) op = IMM_38H;
	else if(token.compare("Z") == 0) op = FLAGS_Z;
	
	return op;	
}

std::string operand_to_str(operand_t operand) {
	switch(operand) {
		case REG_A:
			return "A";
		case REG_AF:
			return "AF";
		case EA_a8:
			return "a8";
		case EA_a16:
			return "a16";
		case REG_B:
			return "B";
		case REG_BC:
			return "BC";
		case REG_C:
			return "C";
		case PREFIX_CB:
			return "CB";
		case REG_D:
			return "D";
		case REG_DE:
			return "DE";
		case IMM_d8:
			return "d8";
		case IMM_d16:
			return "d16";
		case REG_E:
			return "E";
		case REG_H:
			return "H";
		case REG_HL:
			return "HL";
		case REG_HL_P:
			return "HL+";
		case REG_HL_M:
			return "HL-";
		case REG_L:
			return "L";
		case FLAGS_NC:
			return "NC";
		case FLAGS_NZ:
			return "NZ";
		case IMM_r8:
			return "r8";
		case REG_SP:
			return "SP";
		case REG_SP_R8:
			return "SP+r8";
		case IMM_00H:
			return "00H";
		case IMM_08H:
			return "08H";
		case IMM_10H:
			return "10H";
		case IMM_18H:
			return "18H";	
		case IMM_20H:
			return "20H";
		case IMM_28H:
			return "28H";
		case IMM_30H:
			return "30H";
		case IMM_38H:
			return "38H";
		case FLAGS_Z:
			return "Z";
		default:
			printf("Unknown operand.\n");
			break;
	}

	return "OPERAND_INVALID";
}

std::string operand_type_to_str(operand_type_t operand_type) {
	switch(operand_type) {
		case OPERAND_TYPE_REG:
			return "OPERAND_TYPE_REG";
		case OPERAND_TYPE_IMM:
			return "OPERAND_TYPE_IMM";
		case OPERAND_TYPE_EA:
			return "OPERAND_TYPE_EA";
		case OPERAND_TYPE_FLAGS:
			return "OPERAND_TYPE_FLAGS";
		case OPERAND_TYPE_PREFIX:
			return "OPERAND_TYPE_PREFIX";
		default:
			printf("Unknown operand type.\n");
			break;
	}
	return "OPERAND_TYPE_INVALID";
}

flag_op_t get_flag_op(std::string token) {
	
	flag_op_t flag_op = FLAG_OP_INVALID;
	if(token.compare("-") == 0) flag_op = FLAG_OP_NONE;
	else if(token.compare("0") == 0) flag_op = FLAG_OP_RESET;
	else if(token.compare("1") == 0) flag_op = FLAG_OP_SET;
	else if(token.compare("Z") == 0 || token.compare("H") == 0 ||token.compare("N") == 0 || token.compare("C") == 0) flag_op = FLAG_OP_EXEC;

	return flag_op;
}

operand_type_t get_operand_type(operand_t operand) {
	operand_type_t type = OPERAND_TYPE_INVALID;
	
	switch(operand) {
		case REG_AF:
		case REG_BC:
		case REG_DE:
		case REG_HL:
		case REG_A:
		case REG_B:
		case REG_C:
		case REG_D:
		case REG_E:
		case REG_F:
		case REG_H:
		case REG_L:
		case REG_SP:
		case REG_SP_R8:
		case REG_HL_P:
		case REG_HL_M:
			type = OPERAND_TYPE_REG;
			break;
		case IMM_d8:
		case IMM_d16:
		case IMM_r8:
		case IMM_00H:
		case IMM_08H:
		case IMM_10H:
		case IMM_18H:
		case IMM_20H:
		case IMM_28H:
		case IMM_30H:
		case IMM_38H:
			type = OPERAND_TYPE_IMM;
			break;
		case EA_a8: 
		case EA_a16:
			type = OPERAND_TYPE_EA;
			break;
		case FLAGS_NZ:
		case FLAGS_NC:
		case FLAGS_Z:
			type = OPERAND_TYPE_FLAGS;
			break;
		default:
			break;
	}
	
	return type;
}

operand_t get_parent_reg(operand_t reg) {
	switch(reg) {
		case REG_A:
		case REG_F:
			return REG_AF;
		case REG_B:
		case REG_C:
			return REG_BC;
		case REG_D:
		case REG_E:
			return REG_DE;
		case REG_H:
		case REG_L:
			return REG_HL;
		default:
			return reg;
	}
}

operand_t get_upper_reg(operand_t reg) {
	switch(reg) {
		case REG_AF:
			return REG_A;
		case REG_BC:
			return REG_B;
		case REG_DE:
			return REG_D;
		case REG_HL:
			return REG_H;
		default:
			return reg;
	}
}

operand_t get_lower_reg(operand_t reg) {
	switch(reg) {
		case REG_AF:
			return REG_F;
		case REG_BC:
			return REG_C;
		case REG_DE:
			return REG_E;
		case REG_HL:
			return REG_L;
		default:
			return reg;
	}
}
