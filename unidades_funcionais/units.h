#ifndef UNITS_H
#define UNITS_H
#include "./functional_unit_status.h"

typedef enum UnitInstruction
{
  empty = -1,
  mult1 = 0,
  mult2 = 1,
  add = 2,
  divide = 3,
  integer = 4 // d onde log
} UnitInstruction_t;

UnitInstruction_t getTypeOp(unsigned int opcode)
{
  switch (opcode)
    {
    case 32: // add
      return add;
    case 8: //addi
      return add;
    case 36: //and
      return integer;
    case 12: //andi
      return integer;
    case 37: //or
      return integer;
    case 13: //ori
      return integer;
    case 42: //slt
      return integer;
    case 34: //sub
      return add;
    case 24: //mult1 arrumar
      return mult1;
    case 25: //mult2 arrumar 
      return mult2;
    case 1: //LI -> arrumar
      return integer;
    case 2: //mov -> arrumar
      return integer;
    default:
      printf("Erro em Units.h\n");
      return empty;
    }
}

#endif
