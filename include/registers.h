#pragma once

#include <cstdint>

constexpr uint8_t  FLAGBIT_CARRY              = 0;
constexpr uint8_t  FLAGBIT_ZERO               = 1;
constexpr uint8_t  FLAGBIT_INTERRUPT          = 2;
constexpr uint8_t  FLAGBIT_DECMODE            = 3;
constexpr uint8_t  FLAGBIT_BREAK              = 4;
constexpr uint8_t  FLAGBIT_OVERFLOW           = 6;
constexpr uint8_t  FLAGBIT_NEGATIVE           = 7;

constexpr uint8_t  INITVAL_ACCUMULATOR        = 0;
constexpr uint8_t  INITVAL_INDEXREGISTERX     = 0;
constexpr uint8_t  INITVAL_INDEXREGISTERY     = 0;
constexpr uint8_t  INITVAL_STATUSFLAGS        = 0x34;
constexpr uint16_t INITVAL_PROGRAMCOUNTER     = 0xFFFC;
constexpr uint8_t  INITVAL_STACKPOINTEROFFSET = 0xFD;

/**
 * @namespace Emulator::CPU
 *
 * @brief namespace for CPU related things
 * */
namespace Emulator::Cpu
{

	/**
	* @class Registers
	*
	* @brief CPU registers representation.
	*
	* @details This class represents the NES' Memory
	* module including it's mirroring properties
	* based on the specification.
	*/
	class Registers
	{
		/**
		 * @brief holds memory address of next value/opcode
		 */
		private: uint16_t programCounter;

		/**
		 * @brief offset register used for stack/PC manupilation
		 */
		private: uint8_t stackPointerOffset;

		/**
		 * @brief ALU supporting register
		 *
		 * @details most of the calculation based opcodes uses this register
		 * to execute calculations, alongisde with status flags, to record
		 * the correct result of the calculation
		 */
		private: uint8_t accumulator;

		/**
		 * @brief index value mostly for loop indexing
		 */
		private: uint8_t indexRegisterX;

		/**
		 * @brief same index value mostly used for loop indexing
		 */
		private: uint8_t indexRegisterY;

		/**
		 * @brief single variable holding all status flags value for memory efficiency
		 *
		 * @details 8 bit unsigned integer, each bit reflect a single flag
		 * from left to right:
		 * 1st - carry flag, TODO mit csinal
		 * 2nd - zero, if instruction has value result it's set based on if it is zero
		 * 3rd - interrupt, if the flag is on, interrupts are disabled except NMI
		 * 4th - decmode, can be modified, but decimal mode is disabled in NES
		 * 5th - break, BRK and PHP sets it to 1 and IRQ and NMI sets it to 0
		 * 6th - 1 flag
		 * 7th - overflow, set if signed operation resulted overflow during calc
		 * 8th - negative, contains the last bit of the result if there is any
		 */
		private: uint8_t statusFlags;

		public: Registers();

		public: [[nodiscard]] bool check_flag_bit(uint8_t flagBit) const;
		public: [[nodiscard]] bool is_carry_remain() const;
		public: [[nodiscard]] bool is_zero_result() const;
		public: [[nodiscard]] bool is_interrupts_disabled() const;
		public: [[nodiscard]] bool is_decimal_mode_on() const;
		public: [[nodiscard]] bool is_break_executed() const;
		public: [[nodiscard]] bool is_overflow_happened() const;
		public: [[nodiscard]] bool is_negative_flag_set() const;

		private: void set_flag_bit(uint8_t flagBit, bool value);
		public: void set_carry_remain(bool value);
		public: void set_zero_result(bool value);
		public: void set_interrupts_disabled(bool value);
		public: void set_decimal_mode_on(bool value);
		public: void set_break_executed(bool value);
		public: void set_overflow_happened(bool value);
		public: void set_negative_flag_set(bool value);

		public: [[nodiscard]] uint16_t get_program_counter() const;
		public: void set_program_counter(uint16_t programCounter);
		public: [[nodiscard]] uint8_t get_stack_pointer_offset() const;
		public: void set_stack_pointer_offset(uint8_t stackPointerOffset);
		public: [[nodiscard]] uint8_t get_accumulator() const;
		public: void set_accumulator(uint8_t accumulator);
		public: [[nodiscard]] uint8_t get_index_register_x() const;
		public: void set_index_register_x(uint8_t indexRegisterX);
		public: [[nodiscard]] uint8_t get_index_register_y() const;
		public: void set_index_register_y(uint8_t indexRegisterY);
		public: void set_status_flags(uint8_t statusFlags);
		public: [[nodiscard]] uint8_t get_status_flags() const;

		public: void increment_stack_pointer_offset();
		public: void decrement_stack_pointer_offset();
		public: void increment_program_counter();
	};
}
