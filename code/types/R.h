#include <unistd.h>

typedef struct R
{
  unsigned int op : 6;
  unsigned int rs : 5;    // first register operand
  unsigned int rt : 5;    // second register operand
  unsigned int rd : 5;    // register destination
  unsigned int shamt : 5; // shift amount
  unsigned int funct : 6; // function code
} R_t;
