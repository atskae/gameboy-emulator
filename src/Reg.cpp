#include <string>

#include "Reg.h"

reg_t get_reg(std::string token) {
	
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
	else if(token.compare("d8") == 0) reg = REG_D8;
	else if(token.compare("d16") == 0) reg = REG_D16;
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
