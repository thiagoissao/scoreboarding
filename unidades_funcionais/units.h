#ifndef UNITS_H
#define UNITS_H
#include "./functional_unit_status.h"
#include "../tipos_instrucoes/instructions_op.h"

#define emptyText ""
#define mult1Text "mult1"
#define mult2Text "mult2"
#define addText "add"
#define divideText "div"
#define logText "log"

typedef enum UnitInstruction
{
  empty = -1,
  mult1 = 0,
  mult2 = 1,
  add = 2,
  divide = 3,
  log = 4
} UnitInstruction_t;

char *typeOpToString(int id)
{
  switch (id)
  {
  case empty:
    return emptyText;
  case mult1:
    return mult1Text;
  case mult2:
    return mult2Text;
  case add:
    return addText;
  case divide:
    return divideText;
  case log:
    return logText;
  default:
    return "";
  }
}

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
