#include "include/cpu_6502.h"

cpu_6502::cpu_6502()
{

}
cpu_6502::~cpu_6502()
{

}

void cpu_6502::write(uint16_t a, uint8_t d)
{
        bus->write(a, d);
}

uint8_t cpu_6502::read(uint16_t a)
{
        bus->read(a, false);
}