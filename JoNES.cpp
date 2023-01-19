// JoNES.cpp : Defines the entry point for the application.
//

#include "JoNES.h"
#include "JoNES_6502_Core.h"
#include <stdio.h>

//using namespace std;

int testing(JoNES* NES, int location, char *arg);
int runCore(JoNES* NES, bool debug=false);

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cout << "NEED INPUT, ABORTING..." << std::endl;
		return 0;
	}
	std::cout << "Initializing" << std::endl;

	JoNES *NES = new JoNES(argv[1]);
	runCore(NES);
	// basic testing
	//testing(NES, 0, argv[1]);

	delete NES;
	return 0;
}

int testing(JoNES* NES, int location, char *arg)
{
	return 1;
}

// TODO: move this to JoNES.cpp
int runCore(JoNES* NES, bool debug)
{
	int cycles_per_sec = 1789773; // NTSC hrtz; TODO: have this value set from outside
	// second to milliseconds

	while (1)
	{

		int cycles_todo = cycles_per_sec;
		int cycles_done = 0;

		auto start = std::chrono::high_resolution_clock::now();

		while (cycles_done < cycles_todo)
		{

			uint8_t opcode = (NES->getOp());
			NES->coreExec(opcode);
			cycles_done += cycles6502[opcode];
			NES->printRegs();
			if (opcode == 0)
			{
				std::cout << "FIN (BRK)" << std::endl;
				return 0;
			}
			//this->PC += bytes6502[opcode]; // do this in coreExec

		}
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
		// sleep for 1 second - exec time
		if (debug)
			std::cout << "Sleeping for: "
			<< std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(1000000) - elapsed).count()
			<< std::endl;

		std::this_thread::sleep_for(std::chrono::microseconds(1000000) - elapsed);
	}
	return 1;
}