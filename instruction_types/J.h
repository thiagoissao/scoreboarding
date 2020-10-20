#include <unistd.h>

typedef struct J
{
  unsigned int opcode : 6;
  unsigned int address : 26;
} J_t;

/*
j 10000
j LOOP
*/
