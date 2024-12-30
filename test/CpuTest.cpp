#include <cstdint>
#include <gtest/gtest.h>
#include <Cpu.h>
#include <Memory.h>
#include <Registers.h>
#include <memory>

using namespace std;
using namespace Emulator::Cpu;
using namespace Emulator::Memory;

class CpuTest : public ::testing::Test {

	protected: shared_ptr<Memory> memory = make_shared<Memory>();
	protected: shared_ptr<Emulator::Cpu::Registers> registers = make_shared<Registers>();
	protected: Cpu cpu {memory, registers};

	protected: void SetUp() override {
	}

	protected: void TearDown() override {
	}

};

TEST_F(CpuTest, adc_immediate_addressing_two_small_number) {
	// GIVEN: register set up with the staring values for simple addition with remianing carry
	this->registers->set_accumulator(2);
	this->registers->set_zero_result(false);
	this->registers->set_overflow_happened(false);
	this->registers->set_negative_flag_set(false);
	this->registers->set_carry_remain(false);

	// AND: a memory set up with ADC immediate addressing for the current program counter
	this->memory->set_at(this->registers->get_program_counter(), 0x69);
	this->memory->set_at(this->registers->get_program_counter() +1, 2);

	// AND: we record the start program counter for later check
	uint16_t start_program_counter = this->registers->get_program_counter();

	// WHEN: the CPU executes a cycle 
	this->cpu.execute_next_instruction();

	// THEN: the program counter should be forwarded by two
	EXPECT_EQ(start_program_counter +2, this->registers->get_program_counter());

	// AND: the result should be stored in the accumulator register
	EXPECT_EQ(this->registers->get_accumulator(), 4);

	// AND: the negative flag set to false as the result is a positive number 
	EXPECT_EQ(this->registers->is_negative_flag_set(), false);

	// AND: carry remianing flag set to false as there is no carry 
	EXPECT_EQ(this->registers->is_carry_remain(), false);

	// AND: overflow flag should be set to false, as no overflow happend 
	EXPECT_EQ(this->registers->is_overflow_happened(), false);

	// AND: zero flag is set to false as the result is a nonzero number 
	EXPECT_EQ(this->registers->is_zero_result(), false);
}

TEST_F(CpuTest, adc_immediate_addressing_two_small_number_with_carry) {
	// GIVEN: register set up with the staring values for simple addition
	this->registers->set_accumulator(2);
	this->registers->set_zero_result(false);
	this->registers->set_overflow_happened(false);
	this->registers->set_negative_flag_set(false);
	this->registers->set_carry_remain(true);

	// AND: a memory set up with ADC immediate addressing for the current program counter
	this->memory->set_at(this->registers->get_program_counter(), 0x69);
	this->memory->set_at(this->registers->get_program_counter() +1, 2);

	// AND: we record the start program counter for later check
	uint16_t start_program_counter = this->registers->get_program_counter();

	// WHEN: the CPU executes a cycle 
	this->cpu.execute_next_instruction();

	// THEN: the program counter should be forwarded by two
	EXPECT_EQ(start_program_counter +2, this->registers->get_program_counter());

	// AND: the result should be stored in the accumulator register
	EXPECT_EQ(this->registers->get_accumulator(), 5);

	// AND: the negative flag set to false as the result is a positive number 
	EXPECT_EQ(this->registers->is_negative_flag_set(), false);

	// AND: carry remianing flag set to false as there is no carry 
	EXPECT_EQ(this->registers->is_carry_remain(), false);

	// AND: overflow flag should be set to false, as no overflow happend 
	EXPECT_EQ(this->registers->is_overflow_happened(), false);

	// AND: zero flag is set to false as the result is a nonzero number 
	EXPECT_EQ(this->registers->is_zero_result(), false);
}

TEST_F(CpuTest, adc_immediate_addressing_small_and_large_number_for_overflow) {
	// GIVEN: register set up with the staring values for simple addition
	this->registers->set_accumulator(0x7F);
	this->registers->set_zero_result(false);
	this->registers->set_overflow_happened(false);
	this->registers->set_negative_flag_set(false);
	this->registers->set_carry_remain(false);

	// AND: a memory set up with ADC immediate addressing for the current program counter
	this->memory->set_at(this->registers->get_program_counter(), 0x69);
	this->memory->set_at(this->registers->get_program_counter() +1, 2);

	// AND: we record the start program counter for later check
	uint16_t start_program_counter = this->registers->get_program_counter();

	// WHEN: the CPU executes a cycle 
	this->cpu.execute_next_instruction();

	// THEN: the program counter should be forwarded by two
	EXPECT_EQ(start_program_counter +2, this->registers->get_program_counter());

	// AND: the result should be stored in the accumulator register
	EXPECT_EQ(this->registers->get_accumulator(), 129);

	// AND: due to the overflow, the result is negative so the flag is set
	EXPECT_EQ(this->registers->is_negative_flag_set(), true);

	// AND: carry remianing flag set to false as there is no carry 
	EXPECT_EQ(this->registers->is_carry_remain(), false);

	// AND: overflow happend so the flag is set
	EXPECT_EQ(this->registers->is_overflow_happened(), true);

	// AND: zero flag is set to false as the result is a nonzero number 
	EXPECT_EQ(this->registers->is_zero_result(), false);
}

TEST_F(CpuTest, adc_immediate_addressing_two_number_0_as_result) {
	// GIVEN: register set up with the staring values for simple addition
	this->registers->set_accumulator(0xFF);
	this->registers->set_zero_result(false);
	this->registers->set_overflow_happened(false);
	this->registers->set_negative_flag_set(false);
	this->registers->set_carry_remain(false);

	// AND: a memory set up with ADC immediate addressing for the current program counter
	this->memory->set_at(this->registers->get_program_counter(), 0x69);
	this->memory->set_at(this->registers->get_program_counter() +1, 1);

	// AND: we record the start program counter for later check
	uint16_t start_program_counter = this->registers->get_program_counter();

	// WHEN: the CPU executes a cycle 
	this->cpu.execute_next_instruction();

	// THEN: the program counter should be forwarded by two
	EXPECT_EQ(start_program_counter +2, this->registers->get_program_counter());

	// AND: the result should be stored in the accumulator register
	EXPECT_EQ(this->registers->get_accumulator(), 0);

	// AND: the result is 0 so it is treated as positive
	EXPECT_EQ(this->registers->is_negative_flag_set(), false);

	// AND: carry remianing flag is set because the unsigned ovetflow
	EXPECT_EQ(this->registers->is_carry_remain(), true);

	// AND: overflow did not happend as we added 1 to -1
	EXPECT_EQ(this->registers->is_overflow_happened(), false);

	// AND: zero flag is set to true as the result is a exactly 0 
	EXPECT_EQ(this->registers->is_zero_result(), true);
}
