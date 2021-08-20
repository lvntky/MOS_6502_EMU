#ifndef BUS_H
#define BUS_H
#pragma once

#include <cstdint>
#include <array>
#include "cpu_6502.h"

class Bus
{
        public:
                Bus();
                ~Bus();
                // Bus read & write
                void write(uint16_t addr, uint8_t data);
                uint8_t read(uint16_t addr, bool bReadOnly = false);
                // Devices on bus
                cpu_6502 cpu;
                // fake ram
                std::array<uint8_t, 64 * 1024> ram; 

};

#endif