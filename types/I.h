#include <unistd.h>

typedef struct I
{
  unsigned int opcode : 6;
  unsigned int rs : 5;         //regiter containing base address
  unsigned int rt : 5;         //register destination/source
  unsigned int immediate : 16; //value or offset
} I_t;

/*
beq $1, $2, 100
addi $1, $2, 100
lw $t0, 32($s3)
*/
