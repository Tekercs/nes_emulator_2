#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>
#include <memory.h>

constexpr uint16_t ZEROPAGE            = 0x0000;
constexpr uint16_t STACK               = 0x0100;
constexpr uint16_t RAM                 = 0x0200;
constexpr uint16_t RAM_MIRROR          = 0x0800;

constexpr uint16_t IO_REGISTERS        = 0x2000;
constexpr uint16_t IO_REGISTERS_SIZE   = 8;
constexpr uint16_t IO_REGISTERS_MIRROR = 0x2008;
constexpr uint16_t IO_REGISTERS_SEC    = 0x4000;

//constexpr uint16_t EXP_ROM             =0x4020;
//constexpr uint16_t SRAM                =0x6000;
//constexpr uint16_t PRG_LOWER           =0x8000;
//constexpr uint16_t PRG_UPPER           =0xC000;

//constexpr uint16_t RESET_UPPER         =0xFFFD;
//constexpr uint16_t RESET_LOWER         =0xFFFC;
//constexpr uint16_t NMI_UPPER           =0xFFFB;
//constexpr uint16_t NMI_LOWER           =0xFFFA;

using namespace std;
using namespace Emulator::Memory;

Memory::Memory()
{
	for(auto i = 0; i < MEMORY_SIZE; ++i)
		this->memory.at(i) = make_shared<uint8_t>(0);

	this->generate_ram();
	this->generate_io_registers();
}

void Memory::generate_ram()
{
	array<shared_ptr<uint8_t>, RAM_MIRROR> ram{};
	for(auto i = 0; i < RAM_MIRROR; ++i)
		ram.at(i) = make_shared<uint8_t>(0);

	copy(begin(ram), end(ram), begin(this->memory));
	copy(begin(ram), end(ram), begin(this->memory) + RAM_MIRROR);
	copy(begin(ram), end(ram), begin(this->memory) + (RAM_MIRROR *2));
	copy(begin(ram), end(ram), begin(this->memory) + (RAM_MIRROR *3));
}

void Memory::generate_io_registers()
{
	array<shared_ptr<uint8_t>, IO_REGISTERS_SIZE> io_registers;
	for(auto i = 0; i < IO_REGISTERS_SIZE; ++i)
		io_registers.at(i) = make_shared<uint8_t>(0);

	copy(begin(io_registers), end(io_registers), begin(this->memory) + IO_REGISTERS);
	for(auto i = IO_REGISTERS_MIRROR; i < IO_REGISTERS_SEC; i += IO_REGISTERS_SIZE)
		copy(begin(io_registers), end(io_registers), begin(this->memory) + i);
}


uint8_t Memory::get_from(uint16_t address)
{
	// TODO replace with better observer pattern
	//this->notifyListeners({"memread", convertIntToHexString(address)});
	return *this->memory.at(address);
}

void Memory::set_at(uint16_t address, uint8_t value)
{
	// TODO replace with better observer pattern
	//    this->notifyListeners({"memwrite", convertIntToHexString(address), convertIntToHexString(value)});
	*this->memory.at(address) = value;
}
