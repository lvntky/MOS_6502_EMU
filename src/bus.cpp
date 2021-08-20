#include "include/bus.h"

Bus::Bus()
{
        // clear all the ram
        for(auto &i : ram) i = 0x00;

        // connect cpu to communication bus
        cpu.connectBus(this);
}

Bus::~Bus()
{

}

void Bus::write(uint16_t addr, uint8_t data)
{
        if (addr >= 0x0000 && addr <= 0xFFFF){
                ram[addr] = data;
        }
                
}

uint8_t Bus::read(uint16_t addr, bool bReadOnly = false)
{       
        if (addr >= 0x0000 && addr <= 0xFFFF){
                return ram[addr];
        }
                
        else{
                return 0x00;
        }
                
}