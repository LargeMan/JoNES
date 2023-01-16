#include "JoNES_6502_Core.h"

JoNES::JoNES()
{

}

JoNES::~JoNES()
{

}

int JoNES::coreInit()
{

	return 1;
}

int JoNES::coreReset()
{

	return 1;
}

int JoNES::coreExec(uint8_t opcode)
{
	this->PC++;
	switch (opcode)
	{
	case 0x00: // BRK
	{
		this->PC++; // actually a two byte op
		this->memory[this->stack_ptr] = this->PC >> 8;
		this->memory[this->stack_ptr - 1] = this->PC & 0xFF;

		uint8_t status = this->statusReg();
		this->memory[this->stack_ptr - 2] = status;

		uint16_t new_PC = this->memory[0xFFFE];
		new_PC |= (uint16_t)(this->memory[0xFFFF]) << 8;

		this->PC = new_PC;
	} break;

	case 0x01: // ORA (Indirect, X)
		this->ORA(this->index_indirect_x());
		break;

	case 0x05: // ORA Zero Page
		this->ORA(this->zero_page());
		break;
	case 0x06: // ASL Zero Page
		this->ASL(this->zero_page());
		break;

	case 0x08: // PHP
		this->memory[this->stack_ptr--] = this->statusReg();
		break;
	case 0x09: // ORA Immediate
		this->ORA(this->memory[this->PC++]);
		break;
	case 0x0A: // ASL Accumulator
		this->ASL(this->accum);
		break;

	case 0x0D: // ORA Absolute
		this->ORA(this->absolute());
		break;
	case 0x0E: // ASL Absolute
		this->ASL(this->absolute());
		break;

	case 0x10: // BPL
		if (!this->flag_N) this->BR();
		break;
	case 0x11: // ORA (Indirect), Y
		this->ORA(this->indirect_index_y());
		break;

	case 0x15: // ORA Zero Page, X
		this->ORA(this->zero_page(this->getX()));
		break;
	case 0x16: // ASL Zero Page, X
		this->ASL(this->zero_page(this->getX()));
		break;

	case 0x18: // CLC
		this->flag_C = 0;
		break;
	case 0x19: // ORA Absolute, Y
		this->ORA(this->absolute(this->getY()));
		break;

	case 0x1D: // ORA Absolute, X
		this->ORA(this->absolute(this->getX()));
		break;
	case 0x1E: // ASL Absolute, X
		this->ASL(this->absolute(this->getX()));
		break;

	case 0x20: // JSR
	{
		uint16_t target = this->memory[this->PC++];
		// no PC++ since curr PC gets pushed onto the stack
		target |= this->memory[this->PC] << 8;

		this->memory[this->stack_ptr--] = this->PC & 0xFF;
		this->memory[this->stack_ptr--] = this->PC >> 8;

		this->PC = target;
	}
		break;
	case 0x21: // AND (Indirect, X)
		this->AND(this->index_indirect_x());
		break;

	case 0x24: // BIT Zero Page
		this->BIT(this->zero_page());
		break;
	case 0x25: // AND Zero Page
		this->AND(this->zero_page());
		break;
	case 0x26: // ROL Zero Page
		this->ROL(this->zero_page());
		break;

	case 0x28: // PLP
		this->PLP();
		break;
	case 0x29: // AND Immediate
		this->AND(this->memory[this->PC++]);
		break;
	case 0x2A: // ROL Accumulator
		this->ROL(this->accum);
		break;

	case 0x2C: // BIT Absolute
		this->BIT(this->absolute());
		break;
	case 0x2D: // AND Absolute
		this->AND(this->absolute());
		break;
	case 0x2E: // ROL Absolute
		this->ROL(this->absolute());
		break;

	case 0x30: // BMI
		if (this->flag_N) this->BR();
		break;
	case 0x31: // AND (Indirect), Y
		this->AND(this->indirect_index_y());
		break;

	case 0x35: // AND Zero Page, X
		this->AND(this->zero_page(this->getX()));
		break;
	case 0x36: // ROL Zero Page, X
		this->ROL(this->zero_page(this->getX()));
		break;

	case 0x38: // SEC
		this->flag_C = 1;
		break;
	case 0x39: // AND Absolute, Y
		this->AND(this->absolute(this->getY()));
		break;

	case 0x3D: // AND Absolute, X
		this->AND(this->absolute(this->getX()));
		break;
	case 0x3E: // ROL Absolute, X
		this->ROL(this->absolute(this->getX()));
		break;

	case 0x40: // RTI
		this->PLP(); // get status first
		this->RTS(); // get and set PC
		break;
	case 0x41: // EOR (Indirect, X)
		this->EOR(this->index_indirect_x());
		break;

	case 0x45: // EOR Zero Page
		this->EOR(this->zero_page());
		break;
	case 0x46: // LSR Zero Page
		this->LSR(this->zero_page());
		break;

	case 0x48: // PHA
		this->memory[this->stack_ptr--] = this->accum;
		break;
	case 0x49: // EOR Immediate
		this->EOR(this->memory[this->PC++]);
		break;
	case 0x4A: // LSR Accumulator
		this->LSR(this->accum);
		break;

	case 0x4C: // JMP Absolute
		this->PC = this->absolute();
		break;
	case 0x4D: // EOR Absolute
		this->EOR(this->absolute());
		break;
	case 0x4E: // LSR Absolute
		this->LSR(this->absolute());
		break;

	case 0x50: // BVC
		if (!this->flag_V) this->BR();
		break;
	case 0x51: // EOR (Indirect), Y
		this->EOR(this->indirect_index_y());
		break;

	case 0x55: // EOR Zero Page, X
		this->EOR(this->zero_page(this->getX()));
		break;
	case 0x56: // LSR Zero Page, X
		this->LSR(this->zero_page(this->getX()));
		break;

	case 0x58: // CLI
		this->flag_I = 0;
		break;
	case 0x59: // EOR Absolute, Y
		this->EOR(this->absolute(this->getY()));
		break;
	
	case 0x5D: // EOR Absolute, X
		this->EOR(this->absolute(this->getX()));
		break;
	case 0x5E: // LSR Absolute, X
		this->LSR(this->absolute(this->getX()));
		break;

	case 0x60: // RTS
		this->RTS();
		break;
	case 0x61: // ADC (Indirect, X)
		this->ADC(this->index_indirect_x());
		break;
	
	case 0x65: // ADC zero-page
		this->ADC(this->zero_page());
		break;

	case 0x66: // ROR Zero Page
		this->ROR(this->zero_page());
		break;
	
	case 0x68: // PLA
		this->accum = this->memory[this->stack_ptr++];
		this->setZN(this->accum);
		break;
	case 0x69: // ADC Immediate
		this->ADC(this->memory[this->PC++]);
		break;

	case 0x6A: // ROR Accumulator
		this->ROR(this->accum);
		break;
	
	case 0x6C: // JMP Indirect
	{
		// there is an error in the original 6502 with this op; it is replicated for accuracy.
		uint16_t addr = this->memory[this->PC++]; // get lower byte
		// you would think upper byte is just addr + 1,
		// but the bug makes it so if addr == xxFF for LSB, MSB comes from xx00 instead
		if (addr == 0xFF)
			addr |= this->memory[addr & 0xFF00] << 8;
		else
			addr |= this->memory[addr + 1] << 8;
		
		
		//addr |= this->memory[this->PC++] << 8; // get upper byte


		this->PC = this->memory[addr];

	} break;
	case 0x6D: // ADC absolute
		this->ADC(this->absolute());
		break;
	case 0x6E: // ROR Absolute
		this->ROR(this->absolute());
		break;
	
	case 0x70: // BVS
		if (this->flag_Z) this->BR();
		break;
	case 0x71: // ADC (Indirect), Y
		this->ADC(this->indirect_index_y());
		break;
	
	case 0x75: // ADC Zero-page, X
		this->ADC(this->zero_page(this->getX()));
		break;
	case 0x76: // ROR Zero Page, X
		this->ROR(this->zero_page(this->getX()));
		break;

	case 0x78: // SEI
		this->flag_I = 1;
		break;
	case 0x79: // ADC absolute, Y
		this->ADC(this->absolute(this->getY()));
		break;
	
	case 0x7D: // ADC absolute, X
		this->ADC(this->absolute(this->getX()));
		break;
	case 0x7E: // ROR Absolute X
		this->ROR(this->absolute(this->getX()));
		break;

	case 0x81: // STA (Indirect, X)
		this->LD(this->index_indirect_x(), this->accum);
		break;

	case 0x84: // STY Zero Page
		this->LD(this->zero_page(), this->y_reg);
		break;
	case 0x85: // STA Zero Page
		this->LD(this->zero_page(), this->accum);
		break;
	case 0x86: // STX Zero Page
		this->LD(this->zero_page(), this->x_reg);
		break;

	case 0x88: // DEY
		this->DE(this->memory[this->y_reg]);
		break;

	case 0x8A: // TXA
		this->accum = this->x_reg;
		this->setZN(this->accum);
		break;

	case 0x8C: // STY Absolute
		this->LD(this->absolute(), this->y_reg);
		break;
	case 0x8D: // STA Absolute
		this->LD(this->absolute(), this->accum);
		break;
	case 0x8E: // STX Absolute
		this->LD(this->absolute(), this->x_reg);
		break;

	case 0x90: // BCC
		if (!this->flag_C) this->BR();
		break;
	case 0x91: // STA (Indirect), Y
		this->LD(this->indirect_index_y(), this->accum);
		break;

	case 0x94: // STY Zero Page, X
		this->LD(this->zero_page(this->getX()), this->y_reg);
		break;
	case 0x95: // STA Zero Page, X
		this->LD(this->zero_page(this->getX()), this->accum);
		break;
	case 0x96: // STX Zero Page, Y
		this->LD(this->zero_page(this->getY()), this->x_reg);
		break;

	case 0x98: // TYA
		this->accum = this->y_reg;
		this->setZN(this->accum);
		break;
	case 0x99: // STA Absolute, Y
		this->LD(this->absolute(this->getY()), this->accum);
		break;
	case 0x9A: // TXS
		this->stack_ptr = this->x_reg;
		break;

	case 0x9D: // STA Absolute, X
		this->LD(this->absolute(this->getX()), this->accum);
		break;

	case 0xA0: // LDY Immediate
		this->LD(this->y_reg, this->memory[this->PC++]);
		break;
	case 0xA1: // LDA (Indirect, X)
		this->LD(this->accum, this->index_indirect_x());
		break;
	case 0xA2: // LDX Immediate
		this->LD(this->x_reg, this->memory[this->PC++]);
		break;

	case 0xA4: // LDY Zero Page
		this->LD(this->y_reg, this->zero_page());
		break;
	case 0xA5: // LDA Zero Page
		this->LD(this->accum, this->zero_page());
		break;
	case 0xA6: // LDX Zero Page
		this->LD(this->x_reg, this->zero_page());
		break;

	case 0xA8: // TAY
		this->y_reg = this->accum;
		this->setZN(this->y_reg);
		break;
	case 0xA9: // LDA Immediate
		this->LD(this->accum, this->memory[this->PC++]);
		break;
	case 0xAA: // TAX
		this->x_reg = this->accum;
		this->setZN(this->x_reg);
		break;

	case 0xAC: // LDY Absolute
		this->LD(this->y_reg, this->absolute());
		break;
	case 0xAD: // LDA Absolute
		this->LD(this->accum, this->absolute());
		break;
	case 0xAE: // LDX Absolute
		this->LD(this->x_reg, this->absolute());
		break;

	case 0xB0: // BCS
		if (this->flag_C) this->BR();
		break;
	case 0xB1: // LDA (Indirect), Y
		this->LD(this->accum, this->indirect_index_y());
		break;

	case 0xB4: // LDY Zero Page, X
		this->LD(this->y_reg, this->zero_page(this->getX()));
		break;
	case 0xB5: // LDA Zero Page, X
		this->LD(this->accum, this->zero_page(this->getX()));
		break;
	case 0xB6: // LDX Zero Page, Y
		this->LD(this->x_reg, this->zero_page(this->getY()));
		break;

	case 0xB8: // CLV
		this->flag_V = 0;
		break;
	case 0xB9: // LDA Absolute, Y
		this->LD(this->accum, this->absolute(this->getY()));
		break;
	case 0xBA: // TSX
		this->x_reg = this->stack_ptr;
		this->setZN(this->x_reg);
		break;

	case 0xBC: // LDY Absolute, X
		this->LD(this->y_reg, this->absolute(this->getX()));
		break;
	case 0xBD: // LDA Absolute, X
		this->LD(this->accum, this->absolute(this->getX()));
		break;
	case 0xBE: // LDX Absolute, Y
		this->LD(this->y_reg, this->absolute(this->getY()));
		break;

	case 0xC0: // CPY Immediate
		this->CM(this->y_reg, this->memory[this->PC++]);
		break;
	case 0xC1: // CMP (Indirect, X)
		this->CM(this->accum, this->index_indirect_x());
		break;
	
	case 0xC4: // CPY Zero Page
		this->CM(this->y_reg, this->zero_page());
		break;
	case 0xC5: // CMP Zero Page
		this->CM(this->accum, this->zero_page());
		break;
	case 0xC6: // DEC Zero Page
		this->DE(this->zero_page());
		break;
	
	case 0xC8: // INY
		this->IN(this->y_reg);
		break;
	case 0xC9: // CMP Immediate
		this->CM(this->accum, this->memory[this->PC++]);
		break;
	case 0xCA: // DEX
		this->DE(this->memory[this->x_reg]);
		break;
	
	case 0xCC: // CPY Absolute
		this->CM(this->y_reg, this->absolute());
		break;
	case 0xCD: // CMP Absolute
		this->CM(this->accum, this->absolute());
		break;
	case 0xCE: // DEC Absolute
		this->DE(this->absolute());
		break;
	
	case 0xD0: // BNE
		if (!this->flag_Z) this->BR();
		break;
	case 0xD1: // CMP (Indirect), Y
		this->CM(this->accum, this->indirect_index_y());
		break;
	
	case 0xD5: // CMP Zero Page, X
		this->CM(this->accum, this->zero_page(this->getX()));
		break;
	case 0xD6: // DEC Zero Page, X
		this->DE(this->zero_page(this->getX()));
		break;
	
	case 0xD8: // CLD
		this->flag_D = 0;
		break;
	case 0xD9: // CMP Absolute, Y
		this->CM(this->accum, this->absolute(this->getY()));
		break;
	
	case 0xDD: // CMP Absolute, X
		this->CM(this->accum, this->absolute(this->getX()));
		break;
	case 0xDE: // DEC Absolute, X
		this->DE(this->absolute(this->getX()));
		break;
	
	case 0xE0: // CPX IMM
		this->CM(this->x_reg, this->memory[this->PC++]);
		break;
	case 0xE1: // SBC (Indirect, X)
		this->SBC(this->index_indirect_x());
		break;
	
	case 0xE4: // CPX Zero Page
		this->CM(this->x_reg, this->zero_page());
		break;
	case 0xE5: // SBC Zero Page
		this->SBC(this->zero_page());
		break;
	case 0xE6: // INC Zero Page
		this->IN(this->zero_page());
		break;
	
	case 0xE8: // INX
		this->IN(this->x_reg);
		break;
	case 0xE9: // SBC Immediate
		this->SBC(this->memory[this->PC++]);
		break;
	case 0xEA: // NOP
		// lol
		break;
	
	case 0xEC: // CPX Absolute
		this->CM(this->x_reg, this->absolute());
		break;
	case 0xED: // SBC Absolute
		this->SBC(this->absolute());
		break;
	case 0xEE: // INC Absolute
		this->IN(this->absolute());
		break;
	
	case 0xF0: // BEQ
		if (this->flag_Z) this->BR();
		break;
	case 0xF1: // SBC (Indirect), Y
		this->SBC(this->indirect_index_y());
		break;
	
	case 0xF5: // SBC Zero Page, X
		this->SBC(this->zero_page(this->getX()));
		break;
	case 0xF6: // INC Zero Page, X
		this->IN(this->zero_page(this->getX()));
		break;
	
	case 0xF8: // SED
		this->flag_D = 1;
		break;
	case 0xF9: // SBC Absolute, Y
		this->SBC(this->absolute(this->getY()));
		break;
	
	case 0xFD: // SBC Absolute, X
		this->SBC(this->absolute(this->getX()));
		break;
	case 0xFE: // INC Absolute, X
		this->IN(this->absolute(this->getX()));
		break;

	default: break;
	}
	return 1;
}

int JoNES::getContext()
{
	return 1;
}

int JoNES::resetContext()
{
	return 1;
}

int JoNES::interruptSignal()
{
	return 1;
}

int JoNES::coreStop()
{
	return 1;
}

// TODO: move this to JoNES.cpp
int JoNES::runCore(bool debug)
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

			uint8_t opcode = (this->memory[this->PC]);
			this->coreExec(opcode);
			cycles_done += cycles6502[opcode];
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

// =============== Indexing Modes ==============
// pass mem[x] or mem[y] reg to this
uint8_t& JoNES::absolute(uint8_t val)
{
	uint32_t addr = this->memory[this->PC++];
	addr |= this->memory[this->PC++] << 8;
	addr += val;
	
	return this->memory[(uint16_t)(addr & 0xFFFF)];
}
// pass mem[x] or mem[y]  to this
uint8_t& JoNES::zero_page(uint8_t val)
{
	// get addr, increase PC, then add value at addr w/ X val
	uint16_t addr = this->memory[this->PC++] + val;
	return this->memory[addr & 0xFF];
}

uint8_t& JoNES::index_indirect_x()
{
	// get addr and add X val to it (ensure wrap around)
	uint16_t addr = this->memory[this->PC++] + this->getX();
	addr &= 0xFF; // eliminate any carry

	// load LSB
	uint16_t res = this->memory[addr];
	// load MSB
	res |= this->memory[(addr + 1) & 0xFF] << 8;

	return this->memory[res];
}

uint8_t& JoNES::indirect_index_y()
{
	// get addr, add to Y val
	uint8_t param = this->memory[this->PC++];
	uint16_t addr = this->memory[param] + this->getY();
	// addr is LSB; MSB will be bit 9 (carry) + 1 + LSB
	addr |= this->memory[(param + 1) && 0xFF] + (addr >> 8);

	return this->memory[addr];
}


// =============== Functions ==============
int JoNES::ADC(uint8_t val)
{
	uint16_t res = val + this->accum;
	this->setFlags(res, 0b11100011, val, this->accum);
	this->accum = (uint8_t)(res & 0xFF); // update A

	return 1; // success
}

int JoNES::AND(uint8_t val)
{
	this->accum &= val;
	this->setZN(this->accum);

	return 1;
}

int JoNES::ASL(uint8_t &reg)
{
	uint16_t res = reg << 1;
	this->setFlags(res, 0b10100011);
	reg <<= 1;

	return 1;
}

int JoNES::BR()
{
	uint8_t val = this->memory[this->PC++];
	// uint to int is implementation defined in C/CPP
	// this hack is meant to ensure a two's comp subtraction
	if (val < 0x80)
		this->PC += val;
	else
		this->PC -= (~val + 1);

	return 1;
}

// this one is weird
int JoNES::BIT(uint8_t val)
{
	uint8_t res = val & this->accum;
	this->flag_N = res >> 7;
	this->flag_V = res & 0x40 >> 6;
	this->flag_C = res & 0x01;

	return 1;
}

int JoNES::CM(uint8_t &reg, uint8_t val)
{
	this->flag_C = (this->accum >= val);
	this->flag_Z = (this->accum == val);
	this->flag_N = this->accum >> 7;
	return 1;
}

int JoNES::DE(uint8_t& reg)
{
	reg -= 1;
	this->setZN(reg);
	return 1;
}

int JoNES::EOR(uint8_t val)
{
	this->accum ^= val;
	this->setZN(this->accum);

	return 1;
}

int JoNES::IN(uint8_t& reg)
{
	reg += 1;
	this->setZN(reg);

	return 1;
}

int JoNES::LD(uint8_t &reg, uint8_t val)
{
	reg = val;
	this->setZN(val);

	return 1; // success
}

int JoNES::LSR(uint8_t& reg)
{
	this->flag_C = reg & 0x1;
	reg >>= 1;
	this->setZN(reg);

	return 1;
}

int JoNES::ORA(uint8_t val)
{
	this->accum |= val;
	this->setZN(this->accum);
	return 1;
}

int JoNES::PLP()
{
	uint8_t status = this->memory[this->stack_ptr++];
	this->flag_C = status & 0x01;
	this->flag_Z = status & (0x02 >> 1);
	this->flag_I = status & (0x04 >> 2);
	this->flag_D = status & (0x08 >> 3);
	this->flag_B = status & (0x10 >> 4);
	this->flag_V = status & (0x40 >> 6);
	this->flag_N = status & (0x80 >> 7);

	return status;
}

int JoNES::ROL(uint8_t& reg)
{
	uint8_t bit0 = this->flag_C;
	this->flag_C = reg >> 7;

	reg <<= 1;
	reg |= bit0;
	this->setZN(reg);

	return 1;
}

int JoNES::ROR(uint8_t& reg)
{
	uint8_t bit7 = this->flag_C << 7;
	this->flag_C = reg & 0x1;

	reg >>= 1;
	reg |= bit7;
	this->setZN(reg);

	return 1;
}

int JoNES::RTS()
{
	uint16_t new_PC = this->memory[this->stack_ptr++]; // LSB
	new_PC |= this->memory[this->stack_ptr++] << 8; // MSB

	this->PC = new_PC;

	return 1;
}

int JoNES::SBC(uint8_t val)
{
	//https://stackoverflow.com/questions/29193303/6502-emulation-proper-way-to-implement-adc-and-sbc
	this->ADC(~val);
	return 1;
}




// ========== set status flags ==========
// NV-BDIZC
// 76543210
// http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
// set only Z and N (very common)
int JoNES::setZN(uint8_t val)
{
	this->flag_Z = val == 0;
	this->flag_N = val >> 7;
	return 1;
}
// set all flags
int JoNES::setFlags(uint16_t out, uint8_t flags, uint16_t M, uint16_t N)
{
	if (flags & 0x01) // carry
		this->flag_C = (out >> 8);
	if (flags & 0x02 >> 1) // zero
		this->flag_Z = (out & 0xFF) == 0;
	if (flags & 0x04 >> 2) // interrupt disable
		this->flag_I = 1;
	if (flags & 0x0F >> 4) // break
		this->flag_B = 1;
	if (flags & 0x40 >> 6) // overflow
		this->flag_V = ((M ^ out) & (N ^ out) & 0x80) != 0;
	if (flags & 0x80 >> 7) // Negative
		this->flag_N = (out & 0x80) >> 7;
	return 1;
}

