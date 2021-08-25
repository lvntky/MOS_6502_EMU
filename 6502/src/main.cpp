#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem
{
        static constexpr u32 MAX_MEM = 1024 * 64;
        Byte data[MAX_MEM];
        
        void initialise(){
                for(u32 i; i < MAX_MEM; i++){
                        data[i] = 0;
                }
        }

        // read 1 byte function
        Byte operator[](u32 Adress) const {
                return data[Adress];
        }

        // read 1 byte
        Byte& operator[](u32 Adress){
                return data[Adress];
        }
};


struct CPU
{
        void PrintStatus() const
        {       
	printf( "A: %d X: %d Y: %d\n", A, X, Y );
	printf( "PC: %d SP: %d\n", PC, SP );
	//printf( "PS: %d\n", PS );
        }

        Word PC;        // Program counter
        Word SP;        // Stack Pointer

        Byte A, X, Y;   // Accumulator, index and Y registers
        
        /**********************STATUS FLAGS**********************   
         *                                                      *
         *      7  bit  0                                       *
         *      ---- ----                                       *
         *      NVss DIZC                                       *
         *      |||| ||||                                       *
         *      |||| |||+- Carry                                *                                        
         *      |||| ||+-- Zero                                 *
         *      |||| |+--- Interrupt Disable                    *
         *      |||| +---- Decimal                              *
         *      ||++------ No CPU effect, see: the B flag       *
         *      |+-------- Overflow                             *
         *       +--------- Negative                            *
         *                                                      *
         ********************************************************/

        Byte C : 1;
        Byte Z : 1;
        Byte I : 1;
        Byte D : 1;                 
        Byte B : 1;
        Byte V : 1;
        Byte N : 1;

        // CPU reset routine
        void reset(Mem& memory){
                PC = 0XFFFC;
                SP = 0X0100;
                C = Z = I = D = B = V = N = 0;
                A = Y = X = 0;
                
                memory.initialise();
        }
        
        // Fetch an instruction on the memory
        Byte fetchByte(u32& clockCycles, const Mem& memory){
                Byte Data = memory[PC];
                PC++;
                clockCycles--;
                return Data;
        }

        // read an instruction on the memory but dont increase the PC
        Byte readByte(u32& clockCycles, Byte Address ,const Mem& memory){
                Byte Data = memory[Address];
                clockCycles--;
                return Data;
        }

        // Opcodes
        static constexpr Byte 
                INS_LDA_IM = 0XA9,
                INS_LD_ZP = 0XA5; 
        
        // LDA Status Flags
        void LDASetStatus(){
                Z = (A == 0);
                N = (A & 0b10000000) > 0;
        }

        // CPU execute opcodes function
        void execute(u32 clockCycles, Mem& memory){
                while(clockCycles > 0){
                        Byte Instrc = fetchByte(clockCycles, memory);
                        switch (Instrc)
                        {
                        case INS_LDA_IM:
                        {
                                // the value after comes instruction
                                Byte value = fetchByte(clockCycles, memory);
                                A = value;
                                LDASetStatus(); 
                                break;
                        }
                        case INS_LD_ZP:
                        {
                                Byte zeroPageAdress = fetchByte(clockCycles, memory);
                                A = readByte(clockCycles, zeroPageAdress, memory);
                                LDASetStatus();
                        }
                        default:
                        {
                                printf("Wrong instructions %d !", Instrc);
                                break;
                        }
                        }
                }
        }
};

int main()
{
        Mem mem;
        CPU cpu;
        cpu.reset(mem);
        // start -- inline tiny program
        mem[0XFFFC] = CPU::INS_LDA_IM;
        mem[0XFFFD] = 0x1F;
        // end -- inline tiny program
        cpu.execute(2, mem);

        cpu.PrintStatus();
        return 0;
}