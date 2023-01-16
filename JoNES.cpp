// JoNES.cpp : Defines the entry point for the application.
//

#include "JoNES.h"
#include "JoNES_6502_Core.h"
#include <stdio.h>

//using namespace std;

int testing(JoNES* NES, int location, char *arg);

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cout << "NEED INPUT, ABORTING..." << std::endl;
		return 0;
	}
	std::cout << "Initializing" << std::endl;

	JoNES *NES = new JoNES();

	// basic testing
	testing(NES, 0, argv[1]);

	delete NES;
	return 0;
}

int testing(JoNES* NES, int location, char *arg)
{

	// load program into memory
	std::ifstream program(arg, std::ios_base::binary);

	int j = 0;
	if (program.is_open())
	{
		char c;
		while (program.get(c))
		{
			//std::cout << std::hex << c;
			printf("%x ", (uint8_t)c);
			NES->memory[j] = (uint8_t)c;
			j++;
		}
		puts("");
	}
	std::cout << std::endl;
	// jump to addr on reset vector (should be 0 for now)
	NES->coreExec(0x6c);
	int i = 0;


	// i think a brk (0x00) instruct should simply "turn off" the cpu functionally
	// howerver, for now this will just run through the number of bytes

	while (i < j)
	{
		printf("OP: %x\n", NES->memory[i]);
		NES->coreExec(NES->memory[i]);
		NES->printRegs();
		i += bytes6502[NES->memory[i]];
		puts("");
	}


	return 1;
}
