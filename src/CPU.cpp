#include <iostream>
#include <stdio.h> 
#include <fstream> // reading files
#include <sstream> // tokenizing opcodes
#include <string> // getline
#include <assert.h>

#include "CPU.h"
#include "Insn.h"

CPU::CPU(const char* rom_name) {
	// create the instruction.val table from opcodes.csv
	std::ifstream csv_file("opcodes.csv");
	if(!csv_file) {
		printf("Failed to open opcodes.csv\n");
		return;
	}
	
	std::string line;
	int line_num = -1; 
	std::string op;
	unsigned char row = 0;
	unsigned char col = 0;	
	while(std::getline(csv_file, line)) { // read in entire line
		line_num++;
		if(line_num == 0) continue; // ignore the header
		
		// line format: op,size,cycles,rd,rd_mem,rs,rs_mem,z_f,n_f,h_f,c_f,insn_str
		std::istringstream ss(line);
		std::string token;
		
		// the first value is the op
		std::getline(ss, op, ',');

		// create the instruction
		Insn** insn = &this->insn_table[row][col];
		if(op.compare("NOP") == 0) *insn = new NOP(OP_NOP, op);
		else if(op.compare("LD") == 0) *insn = new LD(OP_LD, op);	
		else if(op.compare("INC") == 0) *insn = new INC(OP_INC, op);
		else if(op.compare("DEC") == 0) *insn = new DEC(OP_DEC, op);
		else if(op.compare("RLCA") == 0) *insn = new RLCA(OP_RLCA, op);
		else if(op.compare("ADD") == 0) *insn = new ADD(OP_ADD, op);
		else if(op.compare("RRCA") == 0) *insn = new RRCA(OP_RRCA, op);
		else if(op.compare("STOP") == 0) *insn = new STOP(OP_STOP, op);
		else if(op.compare("RLA") == 0) *insn = new RLA(OP_RLA, op);
		else if(op.compare("JR") == 0) *insn = new JR(OP_JR, op);
		else if(op.compare("RRA") == 0) *insn = new RRA(OP_RRA, op);
		else if(op.compare("DAA") == 0) *insn = new DAA(OP_DAA, op);
		else if(op.compare("CPL") == 0) *insn = new CPL(OP_CPL, op);
		else if(op.compare("SCF") == 0) *insn = new SCF(OP_SCF, op);
		else if(op.compare("CCF") == 0) *insn = new CCF(OP_CCF, op);
		else if(op.compare("HALT") == 0) *insn = new HALT(OP_HALT, op);
		else if(op.compare("ADC") == 0) *insn = new ADC(OP_ADC, op);
		else if(op.compare("SUB") == 0) *insn = new SUB(OP_SUB, op);
		else if(op.compare("SBC") == 0) *insn = new SBC(OP_SBC, op);
		else if(op.compare("AND") == 0) *insn = new AND(OP_AND, op);
		else if(op.compare("XOR") == 0) *insn = new XOR(OP_XOR, op);
		else if(op.compare("OR") == 0) *insn = new OR(OP_OR, op);
		else if(op.compare("CP") == 0) *insn = new CP(OP_CP, op);
		else if(op.compare("RET") == 0) *insn = new RET(OP_RET, op);
		else if(op.compare("POP") == 0) *insn = new POP(OP_POP, op);
		else if(op.compare("JP") == 0) *insn = new JP(OP_JP, op);
		else if(op.compare("CALL") == 0) *insn = new CALL(OP_CALL, op);
		else if(op.compare("PUSH") == 0) *insn = new PUSH(OP_PUSH, op);
		else if(op.compare("RST") == 0) *insn = new RST(OP_RST, op);
		else if(op.compare("PREFIX") == 0) *insn = new PREFIX(OP_PREFIX, op);
		else if(op.compare("RETI") == 0) *insn = new RETI(OP_RETI, op);
		else if(op.compare("LDH") == 0) *insn = new LDH(OP_LDH, op);
		else if(op.compare("DI") == 0) *insn = new DI(OP_DI, op);
		else if(op.compare("EI") == 0) *insn = new EI(OP_EI, op);
		else *insn = new INVALID(OP_INVALID, "INVALID");

		// format: op,size,cycles,rd,rd_mem,rs,rs_mem,z_f,n_f,h_f,c_f,insn_str
		
		// insn size in bytes
		std::getline(ss, token, ',');
		(*insn)->size = atoi(token.c_str());

		// duration in cycles
		std::getline(ss, token, ',');
		(*insn)->cycles = atoi(token.c_str());

		// destination 
		std::getline(ss, token, ',');
		(*insn)->des = str_to_operand(token);

		// rd_mem
		std::getline(ss, token, ',');
		if(token.compare("1") == 0) (*insn)->rd_mem = true;
		else (*insn)->rd_mem = false;

		// source 
		std::getline(ss, token, ',');
		(*insn)->src = str_to_operand(token);
		
		// rs_mem
		std::getline(ss, token, ',');
		if(token.compare("1") == 0) (*insn)->rs_mem = true;
		else (*insn)->rs_mem = false;

		// z flag
		std::getline(ss, token, ',');
		(*insn)->flags[FLAG_Z].val = false;
		(*insn)->flags[FLAG_Z].flag_op = get_flag_op(token);
		
		// n flag
		std::getline(ss, token, ',');
		(*insn)->flags[FLAG_N].val = false;
		(*insn)->flags[FLAG_N].flag_op = get_flag_op(token);
		
		// h flag
		std::getline(ss, token, ',');
		(*insn)->flags[FLAG_H].val = false;
		(*insn)->flags[FLAG_H].flag_op = get_flag_op(token);
		
		// c flag
		std::getline(ss, token, ',');
		(*insn)->flags[FLAG_C].val = false;
		(*insn)->flags[FLAG_C].flag_op = get_flag_op(token);
		
		// insn_str
		(*insn)->insn_str = "";
		while(std::getline(ss, token, ',')) {
 			// '\r' causes the cursor to move to beginning when printing ; remove '\r' to printf() correctly
			token.erase( std::remove(token.begin(), token.end(), '\r'), token.end() );
			token.erase( std::remove(token.begin(), token.end(), '\"'), token.end() );
			(*insn)->insn_str += (token + ",");
		}
		(*insn)->insn_str.pop_back(); // remove extra comma
		//printf("(%i %i) %s\n", row, col, (*insn)->insn_str.c_str());

		col = (col+1) % 16;
		if(col == 0) row = (row+1) % 16;
	}
	csv_file.close();

	// print insn table
	//for(int r=0; r<16; r++) {
	//	for(int c=0; c<16; c++) {
	//		std::cout << this->insn_table[r][c]->insn_str << std::endl;
	//	}
	//	std::cout << std::endl;
	//}

	// initialize registers
	for(int i=0; i<NUM_REGS; i++) {
		regs[i] = 0;
	}
	// initial values on power up
	sp = 0xFFFE; // p.64
	pc = 0x0100; // p.63 ; where the ROM is loaded
	memset(this->memory, 0, MEMORY_SIZE);

	// load ROM
	std::ifstream rom_file(rom_name, std::ifstream::binary);
	if(!rom_file) {
		printf("Failed to open %s\n", rom_name);
		return;
	}

	// get ROM size
	rom_file.seekg(0, std::ios::end); // go to end of file
	this->rom_size = rom_file.tellg();
	printf("%s (%i bytes)\n", rom_name, this->rom_size);
	rom_file.seekg(0, std::ios::beg); // go back to beginning
	rom_file.read(&this->memory[ROM_START_ADDR], this->rom_size); // read in file into memory
	rom_file.close();
	
	// print out bytes
	this->print_mem(ROM_START_ADDR, ROM_START_ADDR + this->rom_size);
	//for(int i=ROM_START_ADDR; i<ROM_START_ADDR + this->rom_size; i++) {
	//	if(i % 32 == 0 && i != ROM_START_ADDR) printf("\n");
	//	printf("%02x ", (unsigned char) this->memory[i]);
	//}
	//printf("\n");

}

void CPU::print_mem(int start, int end) {
	for(int i=start; i<end; i++) {
		if(i % 32 == 0 && i != ROM_START_ADDR) printf("\n");
		printf("%02x ", (unsigned char) this->memory[i]);
	}
	printf("\n");
}

unsigned short CPU::read_reg(operand_t reg) {
	
	if(get_operand_type(reg) != OPERAND_REG) return 0;
	
	switch(reg) {
		case REG_AF:
		case REG_BC:
		case REG_DE:
		case REG_HL:
			return this->regs[reg];
		// upper nibble
		case REG_A:
		case REG_B:
		case REG_D:
		case REG_H:
			return this->regs[get_parent_reg(reg)] & 0xFF00;
		// lower nibble
		case REG_F:
		case REG_C:
		case REG_E:
		case REG_L:
			return this->regs[get_parent_reg(reg)] & 0x00FF;
		default:
			printf("Value not read from register.\n");
			return 0;
	}

}

void CPU::write_reg(operand_t reg, unsigned short val) {
	
	if(get_operand_type(reg) != OPERAND_REG) return;
	
	switch(reg) {
		case REG_AF:
		case REG_BC:
		case REG_DE:
		case REG_HL:
			this->regs[reg] = val;
			return;
		// upper nibble
		case REG_A:
		case REG_B:
		case REG_D:
		case REG_H:
			{
			unsigned short* r = &this->regs[get_parent_reg(reg)];
			*r |= (val << 8);
			}
			return;
		// lower nibble
		case REG_F:
		case REG_C:
		case REG_E:
		case REG_L:
			{	
			unsigned short* r = &this->regs[get_parent_reg(reg)];
			*r |= (val & ~0xFF00);
			}
			return;
		default:
			printf("Value not written to register.\n");
			return;
	}

}

void CPU::print(short mem_start) {
	printf("== CPU State ==\n");
	printf("pc=0x%04x, sp=0x%04x\n", this->pc, this->sp);
	printf("%-4s %-4s %-4s %-4s\n", "A F", "B C", "D E", "H L");
	printf("%04x %04x %04x %04x\n", regs[REG_AF], regs[REG_BC], regs[REG_DE], regs[REG_HL]);
	printf("==\n");

	if(mem_start < 0) return;
	this->print_mem(mem_start, MEMORY_SIZE);	
}

// decodes one instruction at insn pointed by pc
Insn CPU::decode() {
	
	unsigned char opcode = memory[this->pc];
	
	// row and column from GameBoy instruction.val table:
	// http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
	
	unsigned char row = (opcode & 0xF0) >> 4; // read the upper nibble
	unsigned char col = opcode & 0x0F; // read the lower nibble
	Insn insn = *insn_table[row][col]; // create a copy

	// obtain raw bytes
	for(int i=0; i<insn.size; i++) {
		insn.bytes[i] = memory[this->pc + i];
	}

	// save program counter of this instruction
	insn.pc = this->pc;

	// get immediate/effective-addresses/XXH value, if any	
	switch(insn.src) { // rs = source operand
		case IMM_d8:
			assert(insn.size == 2 && pc+1 < ROM_START_ADDR + rom_size);
			insn.imm = memory[this->pc+1];
			break;
		case IMM_d16:
			;
			assert(insn.size == 3 && this->pc+2 < ROM_START_ADDR + rom_size);
			insn.imm = 0x0000;
			insn.imm |= memory[this->pc+1];
			insn.imm = insn.imm << 8;
			insn.imm |= memory[this->pc+2];
			break;
		case IMM_r8: // 8-bit signed data to be added to pc
			assert(insn.size == 2 && this->pc+1 < ROM_START_ADDR + rom_size);
			insn.offset_pc = memory[this->pc+1];
			break;
		case IMM_00H:
			insn.imm = 0x00;
			break;
		case IMM_08H:
			insn.imm = 0x08;
			break;
		case IMM_10H:
			insn.imm = 0x10;
			break;
		case IMM_18H:
			insn.imm = 0x18;
			break;
		case IMM_20H:
			insn.imm = 0x20;
			break;
		case IMM_28H:
			insn.imm = 0x28;
			break;
		case IMM_30H:
			insn.imm = 0x30;
			break;
		case IMM_38H:
			insn.imm = 0x38;
			break;
		case EA_a8:
			assert(insn.size == 2 && this->pc+1 < ROM_START_ADDR + rom_size);
			insn.ea = memory[this->pc+1];
			break;
		case EA_a16:
			;
			assert(insn.size == 3 && this->pc+2 < ROM_START_ADDR + rom_size);
			insn.ea = 0x0000;
			insn.ea |= memory[this->pc+1];
			insn.ea = insn.ea << 8;
			insn.ea |= memory[this->pc+2];
			break;
		default:
			//printf("No immediate value.\n");
			break; // no immediate value
	}

	// update program counter
	this->pc += insn.size;

	//printf("row=%i, col=%i\n", row, col);
	//// starts to overwrite itself if I print "imm" after insn_str... weird
	//printf(
	//	"opcode %02x,"
	//	"rd=%s,"
	//	"rs=%s,"
	//	"imm=%i,"
	//	"size=%i bytes,"
	//	"%s\n",
	//	opcode,
	//	operand_to_str(rd).c_str(),
	//	operand_to_str(rs).c_str(),
	//	insn.imm,
	//	insn.size,
	//	insn.insn_str.c_str()
	//);
	return insn;
}

void CPU::execute(Insn insn) {
	
	// get source value
	unsigned short src_val = 0;
	switch(get_operand_type(insn.src)) {
		case OPERAND_REG:
			;
			src_val = this->read_reg(insn.src);
			if(insn.rs_mem) src_val = this->memory[src_val]; // dereference the value 
			break;
		case OPERAND_IMM:
			if(insn.src == IMM_r8) src_val = insn.offset_pc;
			else src_val = insn.imm;
			break;
		case OPERAND_EA:
			src_val = insn.ea;
			break;
		case OPERAND_FLAGS:
			printf("Didn't implement obtaining flag values as source operand.\n");
			break;
		default:
			break;
	}

	// no need to have insn classes if we use switch-statement...
	switch(insn.op) {
		case OP_NOP:
			break;
		case OP_LD:
			if(insn.des == OPERAND_REG) {
				if(insn.rd_mem) {
					unsigned short addr = this->read_reg(insn.des);
					this->memory[addr] = src_val;
				}
				else this->write_reg(insn.des, src_val);
			}
			else if(insn.des == OPERAND_EA) this->memory[insn.ea] = src_val;
			break;
		default:
			break;
	}
}

CPU::~CPU() {
	printf("CPU destructed.\n");
}
