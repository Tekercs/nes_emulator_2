#pragma once

#include <cstdint>
#include <memory>

#include <Memory.h>
#include <Registers.h>

namespace Emulator::Cpu
{
	/**
	 * @class Cpu
	 *
	 * @brief 6502 nes CPU implementation
	 *
	 * @details implementing CPU and all it's addressing and instructions
	 */
	class Cpu
	{
		/**
		 * @var memory 
		 *
		 * @brief pointer to a memory object
		 *
		 * @details using this pointer to access memory and do opeartoins on it
		 */
		private: std::shared_ptr<Emulator::Memory::Memory> memory;

		/**
		 * @var registers 
		 *
		 * @brief pointer to registers object
		 *
		 * @details this registers are used  to execute instructions 
		 */
		private: std::shared_ptr<Emulator::Cpu::Registers> registers;

		/**
		 * @brief executes the given opcode 
		 *
		 * @param opcode 
		 *
		 * @details executes the instruction implementations based on the incoming opcode
		 */
		private: void execute_instruction(uint8_t opcode);

		/**
		 * @brief add with carry between two 8 bit number
		 *
		 * @param value we want to add to the accumulator current value
		 *
		 * @details the value is added to the the current content of the accumulator register 
		 * if the registers carry remaining flag is set then +1 added to the result 
		 * if the result is zero the registers zero result flag is set to true otherwise set to false
		 * the register's carry reminaing flag set based on if the result is larger than what fitss in 8bit
		 * overflow register flag set based on If the result's sign is different from both A's and memory's, signed overflow (or underflow) occurred.
		 */
		private: void ADC(uint8_t value);

		/**
		 * @brief load value from memory based on program counter
		 *
		 * @return the 8bit value result from memory load
		 *
		 * @details read an 8bit value from memory using the program counte register's 
		 * value as the memory address
		 */
		private: uint8_t load_from_memory_with_immediate_addressing();

		/**
		 * @brief creates a new CPU object, stores a memory and register smartptr to use them for executing instructions
		 */
		public: explicit Cpu(std::shared_ptr<Emulator::Memory::Memory> memory, std::shared_ptr<Emulator::Cpu::Registers> registers);

		/**
		 * @brief based on the program counter, execute the next instruction 
		 *
		 * @details loads in the next opcode from memory location represented by
		 * the register's program counter value which get's executed based on the opcode mapping
		 */
		public: void execute_next_instruction();
	};
}
