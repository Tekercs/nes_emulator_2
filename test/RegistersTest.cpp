#include <gtest/gtest.h>
#include <registers.h>

using namespace Emulator::Cpu;

class RegistersTest : public ::testing::Test {
	
	protected: Registers registers;

	protected: void SetUp() override {
	}

	protected: void TearDown() override {
	}
};

TEST_F(RegistersTest, correctly_inited) {
	EXPECT_EQ(this->registers.get_program_counter(), INITVAL_PROGRAMCOUNTER);
	EXPECT_EQ(this->registers.get_accumulator(), INITVAL_ACCUMULATOR);
	EXPECT_EQ(this->registers.get_index_register_x(), INITVAL_INDEXREGISTERX);
	EXPECT_EQ(this->registers.get_index_register_y(), INITVAL_INDEXREGISTERY);
	EXPECT_EQ(this->registers.get_status_flags(), INITVAL_STATUSFLAGS);
	EXPECT_EQ(this->registers.get_stack_pointer_offset(), INITVAL_STACKPOINTEROFFSET);
}

TEST_F(RegistersTest, program_counter_can_be_incremented) {
	// WHEN: incrementing the program counter after init
		this->registers.increment_program_counter();

	// THEN: the program counter is init val +1
		EXPECT_EQ(this->registers.get_program_counter(), INITVAL_PROGRAMCOUNTER +1);
}

TEST_F(RegistersTest, stack_pointer_can_be_decremented) {
	this->registers.decrement_stack_pointer_offset();
	EXPECT_EQ(this->registers.get_stack_pointer_offset(),INITVAL_STACKPOINTEROFFSET -1);
}

TEST_F(RegistersTest, stack_pointer_can_be_incremented) {
	this->registers.increment_stack_pointer_offset();
	EXPECT_EQ(this->registers.get_stack_pointer_offset(), INITVAL_STACKPOINTEROFFSET +1);
}
