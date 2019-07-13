#include <iostream>

#include "CPU.h"

void printUsage() {
	std::cout << "./gameboy <ROM file>" << std::endl;
	return;
}

int main(int argc, char* argv[]) {
	std::cout << "GameBoy Emulator" << std::endl;
	if(argc < 2) {
		printUsage();
		return 1;
	}
	
	CPU cpu(argv[1]);
	Insn insn = cpu.decode();	
	insn.print();
	
	return 0;
}
