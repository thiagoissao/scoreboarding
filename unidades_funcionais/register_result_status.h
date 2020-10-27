#ifndef REGISTER_RESULT_STATUS_H
#define REGISTER_RESULT_STATUS_H

#include <stdio.h>
#include <unistd.h>
#include "./units.h"

typedef struct register_result_status
{
  int clock;
  UnitInstruction_t f0;
  UnitInstruction_t f2;
  UnitInstruction_t f3;
  UnitInstruction_t f4;
  UnitInstruction_t f5;
  UnitInstruction_t f6;
  UnitInstruction_t f7;
  UnitInstruction_t f8;
  UnitInstruction_t f9;
  UnitInstruction_t f10;
} register_result_status_t;

#endif
