#include <unistd.h>

typedef struct R
{
  unsigned int opcode : 6;
  unsigned int rs : 5;    // first register operand
  unsigned int rt : 5;    // second register operand
  unsigned int rd : 5;    // register destination
  unsigned int shamt : 5; //shift amount
  unsigned int funct : 6; // function code
} R_t;

/*
add $s0, $s1, $s2
http://max.cs.kzoo.edu/cs230/Resources/MIPS/MachineXL/InstructionFormats.html#:~:text=All%20MIPS%20instructions%20are%20encoded,instructions%20are%2032%20bits%20long.&text=There%20are%20three%20instruction%20categories,format%2C%20and%20J%2Dformat.
*/
