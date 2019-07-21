#include <iostream>

#include "CPU.h"

void printUsage() {
	std::cout << "./gameboy <ROM file>" << std::endl;
	return;
}

int main(int argc, char* argv[]) {
	std::cout << "GameBoy Emulator" << std::endl;
	//if(argc < 2) {
	//	printUsage();
	//	return 1;
	//}

	// for faster testing, if a ROM is not provided, the bootstrap ROM is chosen
	const char* rom;
	if(argv[1])	rom = argv[1];
	else rom = "../roms/DMG_ROM.bin";
	
	CPU cpu(rom);
	int num_insn = 3;
	for(int i=0; i<num_insn; i++) {
		Insn insn = cpu.decode();	
		insn.print();
		//cpu.execute(insn);
		//cpu.print(-1);
	}

	// test get_operand_type
	//operand_t op = EA_a16;
	//operand_t type = get_operand_type(op);
	//printf("operand type %s\n", operand_to_str(type).c_str());
	
	return 0;
}
