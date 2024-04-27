#include <registers.h>

using namespace Emulator::Cpu;

Registers::Registers()
: accumulator(INITVAL_ACCUMULATOR)
, indexRegisterX(INITVAL_INDEXREGISTERX)
, indexRegisterY(INITVAL_INDEXREGISTERY)
, statusFlags(INITVAL_STATUSFLAGS)
, programCounter(INITVAL_PROGRAMCOUNTER)
, stackPointerOffset(INITVAL_STACKPOINTEROFFSET) {

}

void Registers::set_flag_bit(uint8_t flagBit, bool value) {
	this->statusFlags ^= (-(uint8_t)value ^ this->statusFlags) & (0x01 << flagBit);
}

void Registers::set_carry_remain(bool value) {
	this->set_flag_bit(FLAGBIT_CARRY, value);
}

void Registers::set_zero_result(bool value) {
	this->set_flag_bit(FLAGBIT_ZERO, value);
}

void Registers::set_interrupts_disabled(bool value) {
	this->set_flag_bit(FLAGBIT_INTERRUPT, value);
}

void Registers::set_decimal_mode_on(bool value) {
	this->set_flag_bit(FLAGBIT_DECMODE, value);
}

void Registers::set_break_executed(bool value) {
	this->set_flag_bit(FLAGBIT_BREAK, value);
}

void Registers::set_overflow_happened(bool value) {
	this->set_flag_bit(FLAGBIT_OVERFLOW, value);
}

void Registers::set_negative_flag_set(bool value) {
	this->set_flag_bit(FLAGBIT_NEGATIVE, value);
}

bool Registers::check_flag_bit(uint8_t flagBit) const {
	return (this->statusFlags & (0x01 << flagBit)) != 0;
}

bool Registers::is_carry_remain() const {
	return this->check_flag_bit(FLAGBIT_CARRY);
}

bool Registers::is_zero_result() const {
	return this->check_flag_bit(FLAGBIT_ZERO);
}

bool Registers::is_interrupts_disabled() const {
	return this->check_flag_bit(FLAGBIT_INTERRUPT);
}

bool Registers::is_decimal_mode_on() const {
	return this->check_flag_bit(FLAGBIT_DECMODE);
}

bool Registers::is_break_executed() const {
	return this->check_flag_bit(FLAGBIT_BREAK);
}

bool Registers::is_negative_flag_set() const {
	return this->check_flag_bit(FLAGBIT_NEGATIVE);
}

bool Registers::is_overflow_happened() const {
	return this->check_flag_bit(FLAGBIT_OVERFLOW);
}

uint16_t Registers::get_program_counter() const {
	return programCounter;
}

void Registers::set_program_counter(uint16_t programCounter) {
	this->programCounter = programCounter;
}

uint8_t Registers::get_stack_pointer_offset() const {
	return stackPointerOffset;
}

void Registers::set_stack_pointer_offset(uint8_t stackPointerOffset) {
	this->stackPointerOffset = stackPointerOffset;
}

uint8_t Registers::get_accumulator() const {
	return accumulator;
}

void Registers::set_accumulator(uint8_t accumulator) {
	this->accumulator = accumulator;
}

uint8_t Registers::get_index_register_x() const {
	return indexRegisterX;
}

void Registers::set_index_register_x(uint8_t indexRegisterX) {
	this->indexRegisterX = indexRegisterX;
}

uint8_t Registers::get_index_register_y() const {
	return indexRegisterY;
}

void Registers::set_index_register_y(uint8_t indexRegisterY) {
	this->indexRegisterY = indexRegisterY;
}

void Registers::increment_stack_pointer_offset() {
	++this->stackPointerOffset;
}

void Registers::decrement_stack_pointer_offset() {
	--this->stackPointerOffset;
}

void Registers::increment_program_counter() {
	++this->programCounter;
}

void Registers::set_status_flags(uint8_t statusFlags) {
	this->statusFlags = statusFlags;
}

uint8_t Registers::get_status_flags() const {
	return statusFlags;
}

