#include <iostream>
#include <stdio.h> 
#include <fstream> // reading files
#include <sstream> // tokenizing opcodes
#include <string> // getline

#include "CPU.h"
#include "Insn.h"

CPU::CPU(char* rom_name) {
	// create the instruction set table from opcodes.csv
	std::ifstream csv_file("opcodes.csv");
	std::string line;
	int line_num = -1; 
	std::string op;
	unsigned char row = 0;
	unsigned char col = 0;	
	while(std::getline(csv_file, line)) { // read in entire line
		line_num++;
		if(line_num == 0) continue; // ignore the header
		
		// format: op,size,cycles,rd,rd_mem,rs,rs_mem,z_f,n_f,h_f,c_f
		std::istringstream ss(line);
		std::string token;
		
		// the first value is the op
		std::getline(ss, op, ',');

		// create the instruction
		Insn** insn = &this->insn_table[row][col];
		if(op.compare("NOP") == 0) *insn = new NOP(INSN_NOP);
		else if(op.compare("LD") == 0) *insn = new LD(INSN_LD);	
		else if(op.compare("INC") == 0) *insn = new INC(INSN_INC);
		else if(op.compare("DEC") == 0) *insn = new DEC(INSN_DEC);
		else if(op.compare("RLCA") == 0) *insn = new RLCA(INSN_RLCA);
		else if(op.compare("ADD") == 0) *insn = new ADD(INSN_ADD);
		else if(op.compare("RRCA") == 0) *insn = new RRCA(INSN_RRCA);
		else if(op.compare("STOP") == 0) *insn = new STOP(INSN_STOP);
		else if(op.compare("RLA") == 0) *insn = new RLA(INSN_RLA);
		else if(op.compare("JR") == 0) *insn = new JR(INSN_JR);
		else if(op.compare("RRA") == 0) *insn = new RRA(INSN_RRA);
		else if(op.compare("DAA") == 0) *insn = new DAA(INSN_DAA);
		else if(op.compare("CPL") == 0) *insn = new CPL(INSN_CPL);
		else if(op.compare("SCF") == 0) *insn = new SCF(INSN_SCF);
		else if(op.compare("CCF") == 0) *insn = new CCF(INSN_CCF);
		else if(op.compare("HALT") == 0) *insn = new HALT(INSN_HALT);
		else if(op.compare("ADC") == 0) *insn = new ADC(INSN_ADC);
		else if(op.compare("SUB") == 0) *insn = new SUB(INSN_SUB);
		else if(op.compare("SBC") == 0) *insn = new SBC(INSN_SBC);
		else if(op.compare("AND") == 0) *insn = new AND(INSN_AND);
		else if(op.compare("XOR") == 0) *insn = new XOR(INSN_XOR);
		else if(op.compare("OR") == 0) *insn = new OR(INSN_OR);
		else if(op.compare("CP") == 0) *insn = new CP(INSN_CP);
		else if(op.compare("RET") == 0) *insn = new RET(INSN_RET);
		else if(op.compare("POP") == 0) *insn = new POP(INSN_POP);
		else if(op.compare("JP") == 0) *insn = new JP(INSN_JP);
		else if(op.compare("CALL") == 0) *insn = new CALL(INSN_CALL);
		else if(op.compare("PUSH") == 0) *insn = new PUSH(INSN_PUSH);
		else if(op.compare("RST") == 0) *insn = new RST(INSN_RST);
		else if(op.compare("PREFIX") == 0) *insn = new PREFIX(INSN_PREFIX);
		else if(op.compare("RETI") == 0) *insn = new RETI(INSN_RETI);
		else if(op.compare("LDH") == 0) *insn = new LDH(INSN_LDH);
		else if(op.compare("DI") == 0) *insn = new DI(INSN_DI);
		else if(op.compare("EI") == 0) *insn = new EI(INSN_EI);
		else *insn = new INVALID(INSN_INVALID);

		// format: op,size,cycles,rd,rd_mem,rs,rs_mem,z_f,n_f,h_f,c_f
		
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

		col = (col+1) % 16;
		if(col == 0) row = (row+1) % 16;
	}
	csv_file.close();

	// print insn table
	//for(int r=0; r<16; r++) {
	//	for(int c=0; c<16; c++) {
	//		this->insn_table[r][c]->print();
	//	}
	//}

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

	//// column and row from GameBoy instruction set table:
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
