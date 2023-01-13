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
	case 0x06: break;

	case 0x08: break;
	case 0x09: break;
	case 0x0A: break;

	case 0x0D: break;
	case 0x0E: break;

	case 0x10: break;
	case 0x11: break;

	case 0x15: break;
	case 0x16: break;

	case 0x18: break;
	case 0x19: break;

	case 0x1D: break;
	case 0x1E: break;

	case 0x20: break;
	case 0x21: break;

	case 0x24: break;
	case 0x25: break;
	case 0x26: break;

	case 0x28: break;
	case 0x29: break;
	case 0x2A: break;

	case 0x2C: break;
	case 0x2D: break;
	case 0x2E: break;

	case 0x30: break;
	case 0x31: break;

	case 0x35: break;
	case 0x36: break;

	case 0x38: break;
	case 0x39: break;

	case 0x3D: break;
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
		this->adc(this->index_indirect_x());
		break;
	
	case 0x65: // ADC zero-page
		this->adc(this->zero_page());
		break;

	case 0x66: break;
	
	case 0x68: break;
	case 0x69: // ADC Immediate
		this->adc(this->memory[this->PC++]);
		break;

	case 0x6A: break;
	
	case 0x6C: break;
	case 0x6D: // ADC absolute
		this->adc(this->absolute());
		break;
	case 0x6E: break;
	
	case 0x70: break;
	case 0x71: // ADC (Indirect), Y
		this->adc(this->indirect_index_y());
		break;
	
	case 0x75: // ADC Zero-page, X
		this->adc(this->zero_page(this->memory[this->x_reg]));
		break;
	case 0x76: break;

	case 0x78: break;
	case 0x79: // ADC absolute, Y
		this->adc(this->absolute(this->memory[this->y_reg]));
		break;
	
	case 0x7D: // ADC absolute, X
		this->adc(this->absolute(this->memory[this->x_reg]));
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
		this->lda(this->index_indirect_x());
		break;
	case 0xA2: break;

	case 0xA4: break;
	case 0xA5:// LDA Zero Page
		this->lda(this->zero_page());
		break;
	case 0xA6: break;

	case 0xA8: break;
	case 0xA9: // LDA Immediate
		this->lda(this->memory[this->PC++]);
		break;
	case 0xAA: break;

	case 0xAC: break;
	case 0xAD: // LDA Absolute
		this->lda(this->absolute());
		break;
	case 0xAE: break;

	case 0xB0: break;
	case 0xB1: // LDA (Indirect), Y
		this->lda(this->indirect_index_y());
		break;

	case 0xB4: break;
	case 0xB5: // LDA Zero Page, X
		this->lda(this->zero_page(this->memory[this->x_reg]));
		break;
	case 0xB6: break;

	case 0xB8: break;
	case 0xB9: // LDA Absolute, Y
		this->lda(this->absolute(this->memory[this->y_reg]));
		break;
	case 0xBA: break;

	case 0xBC: break;
	case 0xBD: // LDA Absolute, X
		this->lda(this->absolute(this->memory[this->x_reg]));
		break;
	case 0xBE: break;

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
uint16_t JoNES::absolute(uint8_t val=0)
{
	uint32_t addr = this->memory[this->PC++];
	addr |= this->memory[this->PC++] << 8;
	addr += val;

	return (uint16_t)(addr & 0xFFFF);
}
// pass mem[x] or mem[y]  to this
uint16_t JoNES::zero_page(uint8_t val=0)
{
	// get addr, increase PC, then add value at addr w/ X val
	uint16_t addr = this->memory[this->PC++] + val;
	uint16_t res = this->memory[addr & 0xFF]; // if addr overflows, wrap around
	return res;
}

uint16_t JoNES::index_indirect_x()
{
	// get addr and add X val to it (ensure wrap around)
	uint16_t addr = this->memory[this->PC++] + this->memory[this->x_reg];
	addr &= 0xFF; // eliminate any carry

	// load LSB
	uint16_t res = this->memory[addr];
	// load MSB
	res |= this->memory[(addr + 1) & 0xFF] << 8;

	return this->memory[res];
}

uint16_t JoNES::indirect_index_y()
{
	// get addr, add to Y val
	uint8_t param = this->memory[this->PC++];
	uint16_t addr = this->memory[param] + this->memory[this->y_reg];
	// addr is LSB; MSB will be bit 9 (carry) + 1 + LSB
	addr |= this->memory[(param + 1) && 0xFF] + (addr >> 8);

	return this->memory[addr];
}


// =============== Functions ==============
int JoNES::adc(uint16_t i)
{
	uint16_t val = i + this->accum;
	// deal with flags; check for carry
	//this->status |= (val & 0x80); // set N flag
	this->flag_N = (val & 0x80) >> 7;
	if (val > 0xFF)
		this->flag_C = 1; // set C  flag

	//http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
	if ((i ^ val) & (this->accum ^ val) & 0x80)
		this->flag_V = 1;

	this->accum = (uint8_t)(val & 0xFF); // update A

	if (this->accum == 0)
		this->flag_Z = 1;

	return 1; // success
}

int JoNES::lda(uint8_t val)
{
	this->accum = val;
	this->flag_N = (val & 0x80) >> 7;
	if (val == 0) this->flag_Z = 1;

	return 1; // success
}

