#include <Cpu.h>
#include <cstdint>
#include <utility>

using namespace std;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;

constexpr uint8_t MAX_8BIT_INT = 0xFF;
constexpr uint16_t ZERO_PAGE_ADDRESS_COUNT = 256;
constexpr uint8_t LAST_8BIT_INT_MASK = 0B10000000;

constexpr uint8_t ADC_IMMEDIATE_ADDRESSING_OPCODE = 0x69;
constexpr uint8_t ADC_ZEROPAGE_ADDRESSING_OPCODE = 0x65;
constexpr uint8_t ADC_ZEROPAGE_X_ADDRESSING_OPCODE = 0x75;

Cpu::Cpu(std::shared_ptr<Emulator::Memory::Memory> memory, std::shared_ptr<Emulator::Cpu::Registers> registers)
: memory((std::move(memory)))
, registers((std::move(registers)))
{ }

void Cpu::execute_next_instruction() {
// TODO add back later
//	if (this->nmi)
//		this->NMI();

	uint8_t opcode = this->memory->get_from(this->registers->get_program_counter());
	this->execute_instruction(opcode);
}

void Cpu::execute_instruction(uint8_t opcode) {
	switch (opcode) {
		case ADC_IMMEDIATE_ADDRESSING_OPCODE:
			// 2 cycles 
			this->ADC(this->load_from_memory_with_immediate_addressing());
			break;
		case ADC_ZEROPAGE_ADDRESSING_OPCODE:
			// 3 cycles
			this->ADC(this->load_from_memory_with_zero_page_value_addressing());
			break;
		case ADC_ZEROPAGE_X_ADDRESSING_OPCODE:
			// 4 cycles
			this->ADC(this->load_from_memory_with_zero_page_x_value_addressing());
		default:
			// handle incorrect opcode, throw exception ??
			break;
	}
}

uint8_t Cpu::load_from_memory_with_zero_page_x_value_addressing() {
	this->registers->increment_program_counter();
	uint16_t target_memory_address = (0x0000
		+ this->memory->get_from(this->registers->get_program_counter())
		+ this->registers->get_index_register_x())
		% ZERO_PAGE_ADDRESS_COUNT;
	
	return this->memory->get_from(target_memory_address);
}

uint8_t Cpu::load_from_memory_with_zero_page_value_addressing() {
	this->registers->increment_program_counter();
	uint16_t target_memory_address = 0x0000 + this->memory->get_from(this->registers->get_program_counter());
	
	return this->memory->get_from(target_memory_address);
}

uint8_t Cpu::load_from_memory_with_immediate_addressing() {
    this->registers->increment_program_counter();
    return this->memory->get_from(this->registers->get_program_counter());
}

void Cpu::ADC(uint8_t value) {
	uint16_t result = this->registers->get_accumulator() + value;

	if (this->registers->is_carry_remain())
		++result;

	this->registers->set_carry_remain(result > MAX_8BIT_INT);

	this->registers->set_zero_result((result & MAX_8BIT_INT) == 0);
	this->registers->set_overflow_happened((~(this->registers->get_accumulator() ^ value) & (this->registers->get_accumulator() ^ result) & LAST_8BIT_INT_MASK) != 0);
	this->registers->set_negative_flag_set((result & LAST_8BIT_INT_MASK) != 0);

	this->registers->set_accumulator(static_cast<uint8_t>(result));

	this->registers->increment_program_counter();
}
