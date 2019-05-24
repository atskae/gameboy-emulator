#include <stdio.h> // printf() ; I hate cout
#include <fstream> // reading files

#include "CPU.h"

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
	if(!rom) {
		printf("Failed to open %s\n", rom_name);
		return;
	}

	// get ROM size
	rom_file.seekg(0, std::ios::end); // go to end of file
	this->num_bytes_rom = rom_file.tellg();
	printf("%s (%i bytes)\n", rom_name, this->num_bytes_rom);
	rom_file.seekg(0, std::ios::beg); // go back to beginning

	this->rom = new char[this->num_bytes_rom];
	rom_file.read(this->rom, this->num_bytes_rom);
	if(!rom) {
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

void CPU::decode(unsigned char opcode) {
	printf("opcode: %02x\n", opcode);
	switch(opcode) {
		case 0x60:
			printf("LD B n\n");
			break;
		default:
			printf("opcode %02x unknown\n", opcode);
			break;
	}
}

CPU::~CPU() {
	if(this->rom) {
		printf("Deleting ROM\n");
		delete[] this->rom;
	}
	printf("CPU destructed.\n");
}
