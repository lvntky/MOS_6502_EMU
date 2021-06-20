#ifndef CPU_6502_H
#define CPU_6502_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct cpu_6502
{

  /** 6502 STATUS FLAGS **/
   /*****************************************************
   *    7  bit  0                                       *
   *    ---- ----                                       *
   *     NVss DIZC                                      *
   *     |||| ||||                                      *
   *     |||| |||+- Carry                               *
   *     |||| ||+-- Zero                                *
   *     |||| |+--- Interrupt Disable                   *
   *     |||| +---- Decimal                             *
   *     ||++------ No CPU effect, see: the B flag      *
   *     |+-------- Overflow                            *
   *     +--------- Negative                            *
   ******************************************************/
  /** All the flags are 1 by default **/
  bool c_flag : 1;
  bool z_flag : true;
  bool i_flag : true;
  bool d_flag : true;
  bool b_flag : true;
  bool v_flag : true;
  bool n_flag : true;

  /** Helper Flags**/
  bool page_crossed : true; // keep track of page crossing
  bool enable_bcd : true; // Eanble/Disable BCD
  // bool cpu_65c02_mode = true;

  /** 6502 Registers **/
  uint8_t a; // Register A
  uint8_t x; // Register x
  uint8_t y; // Register Y
  uint8_t sp; // Stack Pointer

  /** 16-bit Program Counter **/
  uint16_t pc;

  /** Cycle Counter **/
  unsigned long cyc;

  /** Read/Write from memory functions**/
  uint8_t (*read_mem)(void*, uint16_t);
  void (*write_mem)(void*, uint16_t, uint8_t);

  /** User custom pointer **/
  void* user_data;
}cpu_6502;

void cpu_6502_init(cpu_6502* const c);
void cpu_6502_step(cpu_6502* const c);
void cpu_6502_debug_output(cpu_6502* const c);

/** Interrupts  **/
void cpu_6502_gen_nmi(cpu_6502* const c);
void cpu_6502_gen_res(cpu_6502* const c);
void cpu_6502_gen_irq(cpu_6502* const c);

#endif
