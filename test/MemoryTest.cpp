#include <gtest/gtest.h>
#include <cstdint>
#include <iostream>
#include <memory.h>

using namespace Emulator::Memory;

class MemoryTest : public ::testing::Test {
	
	protected: Memory memory;

	protected: void SetUp() override {
	}

	protected: void TearDown() override {
	}
};

TEST_F(MemoryTest, empty_on_init) {
	for (int i = 0; i < MEMORY_SIZE; ++i)
		EXPECT_EQ(this->memory.get_from(i), 0);
}

TEST_F(MemoryTest, ram_section_correctly_mirrored_4_times) {
	// GIVEN: ram address
		constexpr uint16_t ADDRESS_TO_WRITE = 0x0201;

	// AND: a value to write to given
		constexpr uint8_t VALUE = 42;

	// WHEN: the value is written to the address
		this->memory.set_at(ADDRESS_TO_WRITE, VALUE);

	// THEN: the value found 4 times in the memory
		uint16_t total_hits = 0;
		for (int i = 0; i < MEMORY_SIZE; ++i)
			if (this->memory.get_from(i) == VALUE)
				total_hits++;
		
		EXPECT_EQ(total_hits, 4);
	
	// AND: the the value correctly mored to the same portion of the mirror sections
		EXPECT_EQ(this->memory.get_from(ADDRESS_TO_WRITE), VALUE);
		EXPECT_EQ(this->memory.get_from(ADDRESS_TO_WRITE + 0x0800), VALUE);
		EXPECT_EQ(this->memory.get_from(ADDRESS_TO_WRITE + (0x0800 *2)), VALUE);
		EXPECT_EQ(this->memory.get_from(ADDRESS_TO_WRITE + (0x0800 *3)), VALUE);
}

TEST_F(MemoryTest, io_registers_correctly_mirrored_) {
	// GIVEN: a value to write to the io registers
		constexpr uint8_t VALUE = 42;

	// AND: an address to write the value to
		constexpr uint16_t ADDRESS_TO_WRITE = 0x2002;

	// WHEN: the value is written to the address
		this->memory.set_at(ADDRESS_TO_WRITE, VALUE);

	// THEN: the set value correctly mirrored accross io register section 1024 times
		for (auto i = 0; i < 1024; ++i)
			EXPECT_EQ(this->memory.get_from(ADDRESS_TO_WRITE + (8 * i)), VALUE);
}
