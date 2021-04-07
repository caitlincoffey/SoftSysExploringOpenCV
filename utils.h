#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>
#include <stdio.h>
#include <sys/termios.h>
#include <sys/types.h>
#include <unistd.h>
#include "opcode.h"

extern uint16_t memory[65535];

/* registers: 8 general, 1 program counter (PC), 1 condition register */
enum registers
{
    R_0 = 0,
    R_1,
    R_2,
    R_3,
    R_4,
    R_5,
    R_6,
    R_7,
    R_PC,
    R_F,
    R_SIZE
};

/* Condition Flags */
enum cond_flag
{
    F_P = 1 << 0, // positive
    F_Z = 1 << 1, // zero
    F_N = 1 << 2, // negative
};

extern uint16_t reg[R_SIZE];

uint16_t get_sign_extension(uint16_t n, int num_bits);
void update_flag(uint16_t value);
uint16_t read_from_memory(uint16_t address);
void write_to_memory(uint16_t address, uint16_t value);
int read_program_code_into_memory(const char *path_to_code);

uint16_t check_key();

void handle_interrupt(int signal);
void restore_input_buffering();
void disable_input_buffering();

#endif
