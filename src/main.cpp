#include <iostream>

// gamboy components
#include "CPU.h"

using namespace std;

void printUsage() {
	cout << "./gameboy <ROM file>" << endl;
	return;
}

int main(int argc, char* argv[]) {
	cout << "GameBoy Emulator" << endl;
	if(argc < 2) {
		printUsage();
		return 1;
	}
	
	CPU cpu(argv[1]);
	int pc = 0;
	unsigned char code[3] = {0x11, 0x45, 0x87};
	cpu.decode(code, 3, pc);
	
	return 0;
}
