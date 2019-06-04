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
	// values to read in from each line
	int row;
	int col;
	std::string op;
	int size;
	int cycles;
	int rd;
	char rd_mem;
	int rs;
	char rs_mem;
	std::string z_f;
	while(std::getline(csv_file, line)) { // read in entire line
		line_num++;
		if(line_num == 0) continue; // ignore the header
		// format: row,col,op,size,cycles,rd,rd_mem,rs,rs_mem,z_f,n_f,h_f,c_f
		std::istringstream ss(line);
		std::string token;
		while(std::getline(ss, token, ',')) {
			//std::cout << token << std::endl;
			std::cout << token << std::endl;
		}
	}
	csv_file.close();

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
	
	unsigned char opcode = bytes[0];
	reg_t rd = REG_INVALID;
	reg_t rs = REG_INVALID;

	// column and row from GameBoy instruction set table:
	// http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
	
	unsigned char row = (opcode & ~0xF0) >> 4; // read the upper nibble
	unsigned char col = opcode & ~0x0F; // read the lower nibble
	printf("opcode %02x, rd=%i\n", opcode, rd);

}

CPU::~CPU() {
	if(this->rom.bytes) {
		printf("Deleting ROM\n");
		delete[] this->rom.bytes;
	}
	printf("CPU destructed.\n");
}
