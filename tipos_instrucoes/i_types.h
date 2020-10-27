#ifndef I_TYPES_H
#define I_TYPES_H

#include <unistd.h>
#include <string.h>
#include "instructions_op.h"

typedef enum Instruction
{
  R = 0,
  I = 1,
  J = 2
} Instruction;

Instruction getInstructionType(char *opcode)
{
  //R = 0; I = 1; J = 2
  //retorna um inteiro que representa o tipo
  if (strcmp(opcode, ADD) == 0)
    return R;
  if (strcmp(opcode, ADDI) == 0)
    return I;
  if (strcmp(opcode, AND) == 0)
    return R;
  if (strcmp(opcode, ANDI) == 0)
    return I;
  if (strcmp(opcode, OR) == 0)
    return R;
  if (strcmp(opcode, ORI) == 0)
    return I;
  if (strcmp(opcode, SLT) == 0)
    return R;
  if (strcmp(opcode, SUB) == 0)
    return R;
  if (strcmp(opcode, MULT) == 0)
    return R;
  if (strcmp(opcode, DIV) == 0)
    return R;
  if (strcmp(opcode, LW) == 0)
    return I;
  return 0;
}

#endif
