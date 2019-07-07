#include <string>

#include "Reg.h"

reg_t str_to_reg(std::string token) {
	
	reg_t reg = REG_INVALID;
	if(token.compare("A") == 0) reg = REG_A;
	else if(token.compare("AF") == 0) reg = REG_AF;
	else if(token.compare("a8") == 0) reg = REG_A8;
	else if(token.compare("a16") == 0) reg = REG_A16;
	else if(token.compare("B") == 0) reg = REG_B;
	else if(token.compare("BC") == 0) reg = REG_BC;
	else if(token.compare("C") == 0) reg = REG_C;
	else if(token.compare("CB") == 0) reg = REG_CB;
	else if(token.compare("D") == 0) reg = REG_D;
	else if(token.compare("DE") == 0) reg = REG_DE;
	else if(token.compare("d8") == 0) reg = REG_d8;
	else if(token.compare("d16") == 0) reg = REG_d16;
	else if(token.compare("E") == 0) reg = REG_E;
	else if(token.compare("H") == 0) reg = REG_H;
	else if(token.compare("HL") == 0) reg = REG_HL;
	else if(token.compare("HL+") == 0) reg = REG_HL_P;
	else if(token.compare("HL-") == 0) reg = REG_HL_M;
	else if(token.compare("L") == 0) reg = REG_L;
	else if(token.compare("NC") == 0) reg = REG_NC;
	else if(token.compare("NZ") == 0) reg = REG_NZ;
	else if(token.compare("r8") == 0) reg = REG_R8;
	else if(token.compare("SP") == 0) reg = REG_SP;
	else if(token.compare("SP+r8") == 0) reg = REG_SP_R8;
	else if(token.compare("00H") == 0) reg = REG_00H;
	else if(token.compare("08H") == 0) reg = REG_08H;
	else if(token.compare("10H") == 0) reg = REG_10H;
	else if(token.compare("18H") == 0) reg = REG_18H;
	else if(token.compare("20H") == 0) reg = REG_20H;
	else if(token.compare("28H") == 0) reg = REG_28H;
	else if(token.compare("30H") == 0) reg = REG_30H;
	else if(token.compare("38H") == 0) reg = REG_38H;
	else if(token.compare("Z") == 0) reg = REG_Z;
	
	return reg;	
}

std::string reg_to_str(reg_t reg) {
	switch(reg) {
		case REG_A:
			return "A";
		case REG_AF:
			return "AF";
		case REG_A8:
			return "a8";
		case REG_A16:
			return "a16";
		case REG_B:
			return "B";
		case REG_BC:
			return "BC";
		case REG_C:
			return "C";
		case REG_CB:
			return "CB";
		case REG_D:
			return "D";
		case REG_DE:
			return "DE";
		case REG_d8:
			return "d8";
		case REG_d16:
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
		case REG_NC:
			return "NC";
		case REG_NZ:
			return "NZ";
		case REG_R8:
			return "r8";
		case REG_SP:
			return "SP";
		case REG_SP_R8:
			return "SP+r8";
		case REG_00H:
			return "00H";
		case REG_08H:
			return "08H";
		case REG_10H:
			return "10H";
		case REG_18H:
			return "18H";	
		case REG_20H:
			return "20H";
		case REG_28H:
			return "28H";
		case REG_30H:
			return "30H";
		case REG_38H:
			return "38H";
		case REG_Z:
			return "Z";
		default:
			printf("Unknown register.\n");
			break;
	}

	return "INVALID";
}

flag_op_t get_flag_op(std::string token) {
	
	flag_op_t flag_op = FLAG_OP_INVALID;
	if(token.compare("-") == 0) flag_op = FLAG_OP_NONE;
	else if(token.compare("0") == 0) flag_op = FLAG_OP_RESET;
	else if(token.compare("1") == 0) flag_op = FLAG_OP_SET;
	else if(token.compare("Z") == 0 || token.compare("H") == 0 ||token.compare("N") == 0 || token.compare("C") == 0) flag_op = FLAG_OP_EXEC;

	return flag_op;
}
