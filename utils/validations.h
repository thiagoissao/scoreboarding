#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdio.h>
#include "../tipos_instrucoes/i_types.h"
#include "../conversor.h"

bool isR(unsigned int instr)
{
  unsigned int opcode = desconverteOp(instr);
  return opcode == R;
}

#endif
