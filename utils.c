#include "utils.h"

uint16_t reg[R_SIZE];
uint16_t memory[65535];

/* memory-mapped I/O: memory addresses xFE00 through xFFFF have been allocated to designate each I/O device register. */
enum mem_registers
{
  M_KBSR = 0xFE00, // keyboard status register
  M_KBDR = 0xFE02, // keyboard data register
  M_DSR = 0xFE04,  // display status register
  M_DDR = 0xFE06,  // display data register
  M_MCR = 0xFFFE   // machine control register
};

/* General Helper Functions */

uint16_t get_sign_extension(uint16_t n, int num_bits)
{
  n = n & (0xFFFF >> (16 - num_bits));
  uint16_t n_first = n >> (num_bits - 1);
  if (n_first & 0x1)
  {
    uint16_t var = ((0xFFFF << num_bits) | n);
    return var;
  }
  return n;
}

void update_flag(uint16_t value)
/*
 Update the condition flag register depending on the passed in value.
*/

{
    if (reg[value] == 0)
    {
        reg[R_F] = F_Z;
    }
    else if (reg[value] >> 15) // 1 in msb means it's negative
    {
        reg[R_F] = F_N;
    }
    else
    {
        reg[R_F] = F_P;
    }
}

uint16_t read_from_memory(uint16_t address)
{
  if (address == M_KBSR) {
    // we check to see if the address is coming from keyboard status
    if (check_key()) {
      // keeping track of status
      memory[M_KBSR] = (1 << 15);
      // accessing last char from keyboard data register because we know that we need the value,
      // as it just updated
      memory[M_KBDR] = getchar();
    }
    else {
      // updating the value at keyboard status back to 0 because the hardware won't do it
      memory[M_KBSR] = 0;
    }
  }
  return memory[address];
}

void write_to_memory(uint16_t address, uint16_t value)
{
  memory[address] = value;
}

int read_program_code_into_memory(const char *path_to_code)
{
  FILE *code_file = fopen(path_to_code, "r");

  /* Return error if we cannot read file */
  if (!code_file)
  {
    fprintf(stderr, "Error: Could not find file %s\n", path_to_code);
    return 0;
  }

  /* The first 16 bits of the program file
  specify the address in memory where the program should start. */
  uint16_t program_start;
  fread(&program_start, sizeof(uint16_t), 1, code_file);
  // convert to little endian
  program_start = (program_start << 8) | (program_start >> 8);

  /* reading once because we are reading the entire file */
  uint16_t max_space = 65535 - program_start; // 2^16 - program_start

  // memory defined earlier
  uint16_t *point_to_mem = memory + program_start;

  // reading in 16-bit increments
  size_t read_bits = fread(point_to_mem, sizeof(uint16_t), max_space, code_file);
  while (read_bits-- > 0) {
    // converting to little endian
    *point_to_mem = (*point_to_mem << 8) | (*point_to_mem >> 8);
    point_to_mem++;
  }

  fclose(code_file);
  return 1;
}

uint16_t check_key()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    return select(1, &readfds, NULL, NULL, &timeout) != 0;
}

struct termios original_tio, new_tio;

void disable_input_buffering()
{
    tcgetattr(STDIN_FILENO, &original_tio);
    struct termios new_tio = original_tio;
    new_tio.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_input_buffering()
{
  /* restore the old port settings */
  tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

void handle_interrupt(int signal)
{
    restore_input_buffering();
    printf("\n");
    exit(-2);
}
