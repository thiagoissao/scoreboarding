#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdio.h>
#include <stdbool.h>
#include "../types/i_types.h"
#include "../conversor.h"

bool isR(unsigned int instr)
{
  unsigned int opcode;
  opcode = desconverteOp(instr);

  return opcode == R;
}

#endif
