#include <cstdint>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <stdio.h>


typedef uint8_t reg8;
typedef uint16_t reg16;

// bytes for all opcodes (illegal ones will have 0 for now)
static uint8_t bytes6502[256] = {
	1, 2, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 0, 3, 3, 0,
	2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
	3, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
	2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
	1, 2, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
	2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
	1, 2, 0, 0, 0, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
	2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
	0, 2, 0, 0, 2, 2, 2, 0, 1, 0, 1, 0, 3, 3, 3, 0,
	2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 0, 3, 0, 0,
	2, 2, 2, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
	2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
	2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
	2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0,
	2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
	2, 2, 0, 0, 0, 2, 2, 0, 1, 3, 0, 0, 0, 3, 3, 0
};

// cycles for all opcodes (illegal ones will have 0 for now)
static uint8_t cycles6502[256] = {
	7, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 0, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	6, 6, 0, 0, 3, 3, 5, 0, 4, 2, 2, 0, 4, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	6, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 3, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	6, 6, 0, 0, 0, 3, 5, 0, 4, 2, 2, 0, 5, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	0, 6, 0, 0, 3, 3, 3, 0, 2, 0, 2, 0, 4, 4, 4, 0,
	2, 6, 0, 0, 4, 4, 4, 0, 2, 5, 2, 0, 0, 5, 0, 0,
	2, 6, 2, 0, 3, 3, 3, 0, 2, 2, 2, 0, 4, 4, 4, 0,
	2, 5, 0, 0, 4, 4, 4, 0, 2, 4, 2, 0, 4, 4, 4, 0,
	2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0
};

class JoNES
{
public:
	JoNES(char* arg);
	~JoNES();

	int coreInit();

	int coreReset();

	int coreExec(uint8_t opcode);

	int getContext();

	int resetContext();

	int interruptSignal();

	int coreStop();


	void printRegs()
	{
		printf("Stack: %x\nX: %x\nY: %x\nA: %x\nPC: %x\n\n",
			this->stack_ptr, this->x_reg, this->y_reg, this->accum, this->PC);
	}
	uint8_t getOp()
	{
		return this->memory[this->PC];
	}
private:

	// full addr range; 
	uint8_t memory[65536] = { 0 };
	// registers
	uint8_t status = 0x34; //011100; 
	uint8_t stack_ptr = 0xFD;
	uint8_t x_reg = 0;
	uint8_t y_reg = 0;
	uint8_t accum = 0;
	uint16_t PC = 0xFFFB; // reset vector is FFFC, but opcode func does PC++ first

	// flags
	int flag_N, flag_V, flag_B, flag_D, flag_I, flag_Z, flag_C;


	int indexTrans(int i)
	{
		int flag = i & 0xF000; // get first 4 bits

		if (flag < 0x2000)
			return i & 0x07FF;
		if (flag < 0x4000)
			return i & 0x2007;
		return i;
	}

	uint8_t getX()
	{
		return memory[x_reg];
	}
	uint8_t getY()
	{
		return memory[y_reg];
	}
	// addressing methods
	uint8_t &absolute(uint8_t val=0);
	uint8_t &zero_page(uint8_t val=0);
	uint8_t &index_indirect_x();
	uint8_t &indirect_index_y();

	// function methods
	int ADC(uint8_t val);
	int AND(uint8_t val);
	int ASL(uint8_t &reg);
	int BR();
	int BIT(uint8_t val);
	int CM(uint8_t &reg, uint8_t val);
	int DE(uint8_t &reg);
	int EOR(uint8_t val);
	int IN(uint8_t &reg);
	int LD(uint8_t &reg, uint8_t val);
	int LSR(uint8_t &reg);
	int ORA(uint8_t val);
	int PLP();
	int ROL(uint8_t &reg);
	int ROR(uint8_t &reg);
	int RTS();
	int SBC(uint8_t val);


	// status set
	int setZN(uint8_t val);
	int setFlags(uint16_t out, uint8_t flags, uint16_t M=0, uint16_t N=0);
	uint8_t statusReg()
	{
		uint8_t status = 0x20;
		status |= this->flag_C;
		status |= this->flag_Z << 1;
		status |= this->flag_I << 2;
		status |= this->flag_B << 4;
		status |= this->flag_V << 6;
		status |= this->flag_N << 7;

		return status;
	}
};