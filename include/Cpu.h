#pragma once

#include <cstdint>
#include <memory>

#include <Memory.h>
#include <Registers.h>

namespace Emulator::Cpu
{
	class Cpu
	{
		private: std::shared_ptr<Emulator::Memory::Memory> memory;
		private: std::shared_ptr<Emulator::Cpu::Registers> registers;
		private: bool nmi;

		private: void execute_instruction(uint8_t opcode);

		private: uint8_t pull_stack();
		private: void push_stack(uint8_t value);

		private: void NMI();
		private: void PHA();
		private: void PLA();
		private: void PHP();
		private: void PLP();
		private: void SEC();
		private: void SED();
		private: void SEI();
		private: void CLC();
		private: void CLD();
		private: void CLI();
		private: void CLV();
		private: void TAX();
		private: void TAY();
		private: void TSX();
		private: void TXA();
		private: void TXS();
		private: void TYA();
		private: void NOP();
		private: void DEX();
		private: void INX();
		private: void INY();
		private: void DEY();
		private: void BIT(uint8_t value);
		private: void BCC(int8_t value);
		private: void BCS(int8_t value);
		private: void BMI(int8_t value);
		private: void BEQ(int8_t value);
		private: void BNE(int8_t value);
		private: void BPL(int8_t value);
		private: void BVC(int8_t value);
		private: void BVS(int8_t value);
		private: void ASLAccumulator();
		private: void ASL(uint16_t address);
		private: void AND(uint8_t value);
		private: void STA(uint16_t address);
		private: void STX(uint16_t address);
		private: void STY(uint16_t address);
		private: void ADC(uint8_t value);
		private: void SBC(uint8_t value);
		private: void JMP(uint16_t address);
		private: void LDA(uint8_t value);
		private: void LDX(uint8_t value);
		private: void LDY(uint8_t value);
		private: void DEC(uint16_t address);
		private: void INC(uint16_t address);
		private: void ROL(uint16_t address);
		private: void ROLAccumulator();
		private: void RORAccumulator();
		private: void ROR(uint16_t address);
		private: void LSRAccumulator();
		private: void LSR(uint16_t address);
		private: void CMP(uint8_t value);
		private: void CPX(uint8_t value);
		private: void CPY(uint8_t value);
		private: void EOR(uint8_t value);
		private: void ORA(uint8_t value);
		private: void JSR(uint16_t address);
		private: void RTS();
		private: void RTI();
		private: void BRK();

		private: uint8_t immediate_addressing();
		private: uint8_t zero_page_addressing();
		private: uint8_t zero_page_x_addressing();
		private: uint8_t zero_page_y_addressing();
		private: uint8_t zero_page_value_addressing();
		private: uint8_t zero_page_x_value_addressing();
		private: uint8_t zero_page_y_value_addressing();
		private: uint8_t absolute_value_addressing();
		private: uint8_t absolute_x_value_addressing();
		private: uint8_t absolute_y_value_addressing();
		private: uint16_t absolute_location_addressing();
		private: uint16_t absolute_x_location_addressing();
		private: uint16_t absolute_y_location_addressing();
		private: uint16_t indirect_address();
		private: uint16_t indexed_indirect_address();
		private: uint16_t indirect_indexed_address();
		private: uint8_t indexed_indirect_value();
		private: uint8_t indirect_indexed_value();

		public: explicit Cpu();
		public: explicit Cpu(std::shared_ptr<Emulator::Memory::Memory> memory, std::shared_ptr<Emulator::Cpu::Registers> registers);

		public: void execute_next_instruction();

		public: void reset();

	};
}
