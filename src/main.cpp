#include <iostream>

// gamboy components
#include "CPU.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "GameBoy Emulator" << endl;
	if(argc < 2) {
		cout << "./gameboy <ROM file>" << endl;
		return 1;
	}
	
	CPU cpu(argv[1]);
	unsigned char insn = 0x06;
	cpu.decode(&insn, 1);
	
	return 0;
}
