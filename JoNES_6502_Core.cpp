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
	case 0x00: break;
	case 0x01: break;

	case 0x05: break;
	case 0x06: // ASL Zero Page
		this->ASL(this->zero_page());
		break;

	case 0x08: break;
	case 0x09: break;
	case 0x0A: // ASL Accumulator
		this->ASL(this->accum);
		break;

	case 0x0D: break;
	case 0x0E: // ASL Absolute
		this->ASL(this->absolute());
		break;

	case 0x10: break;
	case 0x11: break;

	case 0x15: break;
	case 0x16: // ASL Zero Page, X
		this->ASL(this->zero_page(this->getX()));
		break;

	case 0x18: break;
	case 0x19: break;

	case 0x1D: break;
	case 0x1E: // ASL Absolute, X
		this->ASL(this->absolute(this->getX()));
		break;

	case 0x20: break;
	case 0x21: // AND (Indirect, X)
		this->AND(this->index_indirect_x());
		break;

	case 0x24: break;
	case 0x25: // AND Zero Page
		this->AND(this->zero_page());
		break;
	case 0x26: break;

	case 0x28: break;
	case 0x29: // AND Immediate
		this->AND(this->memory[this->PC++]);
		break;
	case 0x2A: break;

	case 0x2C: break;
	case 0x2D: // AND Absolute
		this->AND(this->absolute());
		break;
	case 0x2E: break;

	case 0x30: break;
	case 0x31: // AND (Indirect), Y
		this->AND(this->indirect_index_y());
		break;

	case 0x35: // AND Zero Page, X
		this->AND(this->zero_page(this->getX()));
		break;
	case 0x36: break;

	case 0x38: break;
	case 0x39: // AND Absolute, Y
		this->AND(this->absolute(this->getY()));
		break;

	case 0x3D: // AND Absolute, X
		this->AND(this->absolute(this->getX()));
		break;
	case 0x3E: break;

	case 0x40: break;
	case 0x41: break;

	case 0x45: break;
	case 0x46: break;

	case 0x48: break;
	case 0x49: break;
	case 0x4A: break;

	case 0x4C: break;
	case 0x4D: break;
	case 0x4E: break;

	case 0x50: break;
	case 0x51: break;

	case 0x55: break;
	case 0x56: break;

	case 0x58: break;
	case 0x59: break;
	
	case 0x5D: break;
	case 0x5E: break;

	case 0x60: break;
	case 0x61: // ADC (Indirect, X)
		this->ADC(this->index_indirect_x());
		break;
	
	case 0x65: // ADC zero-page
		this->ADC(this->zero_page());
		break;

	case 0x66: break;
	
	case 0x68: break;
	case 0x69: // ADC Immediate
		this->ADC(this->memory[this->PC++]);
		break;

	case 0x6A: break;
	
	case 0x6C: break;
	case 0x6D: // ADC absolute
		this->ADC(this->absolute());
		break;
	case 0x6E: break;
	
	case 0x70: break;
	case 0x71: // ADC (Indirect), Y
		this->ADC(this->indirect_index_y());
		break;
	
	case 0x75: // ADC Zero-page, X
		this->ADC(this->zero_page(this->getX()));
		break;
	case 0x76: break;

	case 0x78: break;
	case 0x79: // ADC absolute, Y
		this->ADC(this->absolute(this->getY()));
		break;
	
	case 0x7D: // ADC absolute, X
		this->ADC(this->absolute(this->getX()));
		break;
	case 0x7E: break;

	case 0x81: break;

	case 0x84: break;
	case 0x85: break;
	case 0x86: break;

	case 0x88: break;

	case 0x8A: break;

	case 0x8C: break;
	case 0x8D: break;
	case 0x8E: break;

	case 0x90: break;
	case 0x91: break;

	case 0x94: break;
	case 0x95: break;
	case 0x96: break;

	case 0x98: break;
	case 0x99: break;
	case 0x9A: break;

	case 0x9D: break;

	case 0xA0: break;
	case 0xA1: // LDA (Indirect, X)
		this->LD(this->accum, this->index_indirect_x());
		break;
	case 0xA2: // LDX Immediate
		this->LD(this->x_reg, this->memory[this->PC++]);
		break;

	case 0xA4: break;
	case 0xA5: // LDA Zero Page
		this->LD(this->accum, this->zero_page());
		break;
	case 0xA6: // LDX Zero Page
		this->LD(this->x_reg, this->zero_page());
		break;

	case 0xA8: break;
	case 0xA9: // LDA Immediate
		this->LD(this->accum, this->memory[this->PC++]);
		break;
	case 0xAA: break;

	case 0xAC: break;
	case 0xAD: // LDA Absolute
		this->LD(this->accum, this->absolute());
		break;
	case 0xAE: // LDX Absolute
		this->LD(this->x_reg, this->absolute());
		break;

	case 0xB0: break;
	case 0xB1: // LDA (Indirect), Y
		this->LD(this->accum, this->indirect_index_y());
		break;

	case 0xB4: break;
	case 0xB5: // LDA Zero Page, X
		this->LD(this->accum, this->zero_page(this->getX()));
		break;
	case 0xB6: // LDX Zero Page, Y
		this->LD(this->x_reg, this->zero_page(this->getY()));
		break;

	case 0xB8: break;
	case 0xB9: // LDA Absolute, Y
		this->LD(this->accum, this->absolute(this->getY()));
		break;
	case 0xBA: break;

	case 0xBC: break;
	case 0xBD: // LDA Absolute, X
		this->LD(this->accum, this->absolute(this->getX()));
		break;
	case 0xBE: // LDX Absolute, Y
		this->LD(this->y_reg, this->absolute(this->getY()));
		break;

	case 0xC0: break;
	case 0xC1: break;
	
	case 0xC4: break;
	case 0xC5: break;
	case 0xC6: break;
	
	case 0xC8: break;
	case 0xC9: break;
	case 0xCA: break;
	
	case 0xCC: break;
	case 0xCD: break;
	case 0xCE: break;
	
	case 0xD0: break;
	case 0xD1: break;
	
	case 0xD5: break;
	case 0xD6: break;
	
	case 0xD8: break;
	case 0xD9: break;
	
	case 0xDD: break;
	case 0xDE: break;
	
	case 0xE0: break;
	case 0xE1: break;
	
	case 0xE4: break;
	case 0xE5: break;
	case 0xE6: break;
	
	case 0xE8: break;
	case 0xE9: break;
	case 0xEA: break;
	
	case 0xEC: break;
	case 0xED: break;
	case 0xEE: break;
	
	case 0xF0: break;
	case 0xF1: break;
	
	case 0xF5: break;
	case 0xF6: break;
	
	case 0xF8: break;
	case 0xF9: break;
	
	case 0xFD: break;
	case 0xFE: break;
	
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

int JoNES::runCore(bool debug=false)
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
uint8_t& JoNES::absolute(uint8_t val=0)
{
	uint32_t addr = this->memory[this->PC++];
	addr |= this->memory[this->PC++] << 8;
	addr += val;

	return this->memory[(uint16_t)(addr & 0xFFFF)];
}
// pass mem[x] or mem[y]  to this
uint8_t& JoNES::zero_page(uint8_t val=0)
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
	this->setFlags(val, 0b10100010);

	return 1;
}

int JoNES::ASL(uint8_t &reg)
{
	uint16_t res = reg << 1;
	this->setFlags(res, 0b10100011);
	reg <<= 1;

	return 1;
}

int JoNES::LD(uint8_t &reg, uint8_t val)
{
	reg = val;
	this->setFlags(val, 0b10100010);

	return 1; // success
}

// TODO: NOT CURRENTLY USED; maybe find a way to utilize this later?
// ========== set status flags ==========
// NV-BDIZC
// 76543210
// http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
int JoNES::setFlags(uint16_t out, uint8_t flags, uint16_t M=0, uint16_t N=0)
{
	if (flags & 0x01) // carry
		this->flag_C = (out >> 8);
	if (flags & 0x02 >> 1) // zero
		this->flag_Z = (out & 0xFF == 0);
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

