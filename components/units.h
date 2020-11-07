#ifndef UNITS_H
#define UNITS_H
#include "./functional_unit_status.h"
#include "../types/instructions_op.h"

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

#endif
