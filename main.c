/**
 * Garbage Eaters: LC-3 Virtual Machine
 *
 * Date: 03/06/2021
 * Authors: Gati Aher, Navi Sai, Caitlin Coffey, Zoe McGinnis
 **/

/* includes */
#include <stdint.h>
#include <stdio.h>
#include "opcode.h"

/**
 *  static memory:
 * 2^16 memory locations of 16 bits each.
 * Addresses are numbered from 0 (x0000) to 65,535 (xFFFF)
 */
uint16_t memory[65535];

// TODO: function headers
// TODO: TRAP functions (are we writing those in C or assembly?)
// TODO: other input handling functions?
// TODO: functions for terminal interfacing?
// TODO: functions for keyboard interfacing?
// uint16_t get_sign_extension(uint16_t n, int num_bits);
// void update_flag(uint16_t value);

// uint16_t read_from_memory(uint16_t address);
// void write_to_memory(uint16_t address, uint16_t value);
// int read_program_code_into_memory(const char *path_to_code);

/* instruction set function definitions */
/** NOTE: I think we should divide and conquer to write them all
 * and then we join them together with pipelining in the main functions?
 * I still need to figure out what exactly that entails*/
/* each function gets an instruction with the first four bits (opcode) removed */

// void op_add(uint16_t bits);
// void op_and(uint16_t bits);
// void op_not(uint16_t bits);
// void op_ld(uint16_t bits);
// void op_ldi(uint16_t bits);
// void op_ldr(uint16_t bits);
// void op_lea(uint16_t bits);
// void op_trap(uint16_t bits);

/* ENUMS */

/* registers: 8 general, 1 program counter (PC), 1 condition register */
// enum registers
// {
//   R_0 = 0,
//   R_1,
//   R_2,
//   R_3,
//   R_4,
//   R_5,
//   R_6,
//   R_7,
//   R_PC,
//   R_F,
//   R_SIZE
// };

uint16_t reg[R_SIZE];

/* instruction set: 14 instructions, 1 reserved, 1 unused */
/* represent 4 bit binary opcodes with numbers 0-15 */
enum instruction_set
{
  OP_BR = 0, /* branch */
  OP_ADD,    /* add  */
  OP_LD,     /* load */
  OP_ST,     /* store */
  OP_JSR,    /* jump register */
  OP_AND,    /* bitwise and */
  OP_LDR,    /* load register */
  OP_STR,    /* store register */
  OP_RTI,    /* unused */
  OP_NOT,    /* bitwise not */
  OP_LDI,    /* load indirect */
  OP_STI,    /* store indirect */
  OP_JMP,    /* jump */
  OP_RES,    /* reserved (unused) */
  OP_LEA,    /* load effective address */
  OP_TRAP    /* execute trap */
};

/* condition flags: three 1-bit registers: N (negative) Z (zero) P (positive) */
enum cond_flag
{
  F_N = 0b100,
  F_Z = 0b010,
  F_P = 0b001
};

/* trap codes: 6 trap code operations */
enum trap_codes
{
  T_GETC = 0x20,
  T_OUT,
  T_PUTS,
  T_IN,
  T_PUTSP,
  T_HALT
};

/* memory-mapped I/O: memory addresses xFE00 through xFFFF have been allocated to designate each I/O device register. */
enum mem_registers
{
  M_KBSR = 0xFE00, // keyboard status register
  M_KBDR = 0xFE02, // keyboard data register
  M_DSR = 0xFE04,  // display status register
  M_DDR = 0xFE06,  // display data register
  M_MCR = 0xFFFE   // machine control register
};



/* priority level, processor status register, privilege mode, privilege mode exception? */
/* QUESTION: do we need to implement operating system and supervisor stack: memory adresses x0200 through x2FFF */
/* QUESTION: is user stack the same as the available stack space for user programs, or something else we have to implement? */

int main(int argc, const char *argv[])
{
  // NOTE: if anything goes wrong, change this status
  int status = 1;

  if (argc <= 1)
  {
    fprintf(stderr, "Error: No input files\n");
    return 0;
  }

  // File path to to program LC-3 should run
  char *path_to_code = argv[1];
  read_program_code_into_memory(path_to_code);

  /* 0x3000 is the default PC position, start of memory available for user programs. */
  int PC_INIT = 0x3000;

  while (1)
  {
    // Follow Classic RISC Pipeline
    /**
         * 1. IF. instruction fetch
         * load one instruction from memory at the address of PC register,
         * increment PC register by 4,
         * and choose whether to take that as next PC or to take result of a branch / jump calculation as the next PC
         * */
    uint16_t opcode;

    /**
         * 2. ID. instruction decode and register fetch
         * look at opcode to determine which type of instruction it should perform and on what values,
         * if instruction is a branch or jump, the target address of the branch or jump is computed in parallel with reading the register file
         * */
    switch (opcode)
    {
    case 1:
      // NOTE: I think 3 and 4 and specific to the opcode and should happen in the function
      // QUESTION: is 5 going to be the same for all the opcodes?
      /* 3. EX. execute */
      /* 4. MEM. memory access */
      /** 5. WB. register write back
             * update general registers with output
             * update COND register with N Z P value
             * */
      op_add(1);
      break;

    default:
      break;
    }
  }

  return status;
}
