#include <iostream>
#include <stdio.h> 
#include <fstream> // reading files
#include <sstream> // tokenizing opcodes
#include <string> // getline

#include "CPU.h"
#include "Insn.h"

CPU::CPU(char* rom_name) {
	// create the instruction.val table from opcodes.csv
	std::ifstream csv_file("opcodes.csv");
	std::string line;
	int line_num = -1; 
	std::string op;
	unsigned char row = 0;
	unsigned char col = 0;	
	while(std::getline(csv_file, line)) { // read in entire line
		line_num++;
		if(line_num == 0) continue; // ignore the header
		
		// format: op,size,cycles,rd,rd_mem,rs,rs_mem,z_f,n_f,h_f,c_f,insn_str
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

		// target register rd
		std::getline(ss, token, ',');
		(*insn)->rd = get_reg(token);

		// rd_mem
		std::getline(ss, token, ',');
		if(token.compare("1") == 0) (*insn)->rd_mem = true;
		else (*insn)->rd_mem = false;

		// source register rs
		std::getline(ss, token, ',');
		(*insn)->rs = get_reg(token);
		
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
			(*insn)->insn_str += token;
		}

		//printf("(%i %i) %s\n", row, col, (*insn)->insn_str.c_str());

		col = (col+1) % 16;
		if(col == 0) row = (row+1) % 16;
	}
	csv_file.close();

	// print insn table
	for(int r=0; r<16; r++) {
		for(int c=0; c<16; c++) {
			std::cout << this->insn_table[r][c]->insn_str << ' ';
		}
		std::cout << std::endl;
	}

	// initialize registers
	for(int i=0; i<NUM_REGS; i++) {
		regs[i] = 0;
	}
	// initial values on power up
	sp = 0xFFFE;
	pc = 0x0100;
	this->rom.bytes = nullptr;

	// load ROM
	std::ifstream rom_file(rom_name, std::ifstream::binary);
	if(!rom_file) {
		printf("Failed to open %s\n", rom_name);
		return;
	}

	// get ROM size
	rom_file.seekg(0, std::ios::end); // go to end of file
	this->rom.size = rom_file.tellg();
	printf("%s (%i bytes)\n", rom_name, this->rom.size);
	rom_file.seekg(0, std::ios::beg); // go back to beginning

	this->rom.bytes = new char[this->rom.size];
	rom_file.read(this->rom.bytes, this->rom.size);
	if(!this->rom.bytes) {
		printf("Failed to read %s\n", rom_name);
		delete[] this->rom.bytes;
		return;
	}

	// print out bytes
	for(int i=0; i<this->rom.size; i++) {
		if(i % 32 == 0 && i != 0) printf("\n");
		printf("%02x ", (unsigned char) this->rom.bytes[i]);
	}
	printf("\n");

}

// decodes one instruction
void CPU::decode(unsigned char* bytes, int size) {
	
	//unsigned char opcode = bytes[0];
	//reg_t rd = REG_INVALID;
	//reg_t rs = REG_INVALID;

	//// column and row from GameBoy instruction.val table:
	//// http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
	//
	//unsigned char row = (opcode & ~0xF0) >> 4; // read the upper nibble
	//unsigned char col = opcode & ~0x0F; // read the lower nibble
	//printf("opcode %02x, rd=%i\n", opcode, rd);

}

CPU::~CPU() {
	if(this->rom.bytes) {
		printf("Deleting ROM\n");
		delete[] this->rom.bytes;
	}
	printf("CPU destructed.\n");
}
