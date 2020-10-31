#ifndef UNITS_H
#define UNITS_H
#include "./functional_unit_status.h"
#include "../tipos_instrucoes/instructions_op.h"

typedef enum UnitInstruction
{
  empty = -1,
  mult1 = 0,
  mult2 = 1,
  add = 2,
  divide = 3,
  log = 4
} UnitInstruction_t;

UnitInstruction_t getTypeOp(unsigned int opcode)
{
  switch (opcode)
  {
  case ADD_DECIMAL: // add
    return add;
  case ADDI_DECIMAL: //addi
    return add;
  case AND_DECIMAL: //and
    return log;
  case ANDI_DECIMAL: //andi
    return log;
  case OR_DECIMAL: //or
    return log;
  case ORI_DECIMAL: //ori
    return log;
  case SLT_DECIMAL: //slt
    return log;
  case SUB_DECIMAL: //sub
    return add;
  case MULT_DECIMAL: //mult1 ou mult2 arrumar
    return mult1;
  case DIV_DECIMAL:
    return divide;
  case LI_DECIMAL: //LI -> arrumar
    return log;
  case MOVE_DECIMAL: //mov -> arrumar
    return log;
  default:
    printf("Erro em Units.h\n");
    return empty;
  }
}

#endif
