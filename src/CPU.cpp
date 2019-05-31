#include <stdio.h> // printf() ; I hate cout
#include <fstream> // reading files

#include "CPU.h"
#include "Insn.h"

CPU::CPU(char* rom_name) {
	printf("CPU constructed!\n");
	// initialize registers
	for(int i=0; i<NUM_REGS; i++) {
		regs[i] = 0;
	}
	// initial values on power up
	sp = 0xFFFE;
	pc = 0x0100;
	this->rom = nullptr;

	// load ROM
	std::ifstream rom_file(rom_name, std::ifstream::binary);
	if(!rom_file) {
		printf("Failed to open %s\n", rom_name);
		return;
	}

	// get ROM size
	rom_file.seekg(0, std::ios::end); // go to end of file
	this->num_bytes_rom = rom_file.tellg();
	printf("%s (%i bytes)\n", rom_name, this->num_bytes_rom);
	rom_file.seekg(0, std::ios::beg); // go back to beginning

	this->rom = new char[num_bytes_rom];
	rom_file.read(this->rom, this->num_bytes_rom);
	if(!this->rom) {
		printf("Failed to read %s\n", rom_name);
		delete[] this->rom;
		return;
	}

	// print out bytes
	for(int i=0; i<this->num_bytes_rom; i++) {
		if(i % 32 == 0 && i != 0) printf("\n");
		printf("%02x ", (unsigned char) this->rom[i]);
	}
	printf("\n");

}

void CPU::decode(unsigned char* bytes, int num_bytes) {
	
	unsigned char opcode = bytes[num_bytes-1];
	reg_t rd = REG_INVALID;
	reg_t rs = REG_INVALID;

	switch(opcode) {
		case 0x06:
			rd = REG_D;
			printf("0x06 here! rd=%i\n", rd);
			//this->insn = LD8; // 8-bit Load
			//break;
		case 0x0E:
			rd = REG_C;
			printf("0x0E here! rd=%i\n", rd);
			//this->insn = LD8; // 8-bit Load
			//break;
		case 0x16:
			rd = REG_C;
			//this->insn = LD8; // 8-bit Load
			//break;
		case 0x1E:
			rd = REG_E;
			//this->insn = LD8; // 8-bit Load
			//break;
		case 0x26:
			rd = REG_H;
			//this->insn = LD8; // 8-bit Load
			//break;
		case 0x2E:
			rd = REG_L;
			break;
		default:
			printf("%02x invalid opcode.\n", opcode);
			break;
	}
	printf("opcode %02x, rd=%i\n", opcode, rd);
	//switch(insn.opcode) {
	//	// LD, nn, n
	//	case 0x60:
	//		printf("LD B n\n");
	//		break;
	//	default:
	//		printf("opcode %02x unknown\n", opcode);
	//		break;
	//}
}

CPU::~CPU() {
	if(this->rom) {
		printf("Deleting ROM\n");
		delete[] this->rom;
	}
	printf("CPU destructed.\n");
}
