#ifndef REGISTER_RESULT_STATUS_H
#define REGISTER_RESULT_STATUS_H

#include <stdio.h>
#include <unistd.h>
#include "./units.h"

typedef struct register_result_status_table
{
  int clock;
  UnitInstruction_t zero;
  UnitInstruction_t at;
  UnitInstruction_t v0;
  UnitInstruction_t v1;
  UnitInstruction_t a0;
  UnitInstruction_t a1;
  UnitInstruction_t a2;
  UnitInstruction_t a3;
  UnitInstruction_t t0;
  UnitInstruction_t t1;
  UnitInstruction_t t2;
  UnitInstruction_t t3;
  UnitInstruction_t t4;
  UnitInstruction_t t5;
  UnitInstruction_t t6;
  UnitInstruction_t t7;
  UnitInstruction_t s0;
  UnitInstruction_t s1;
  UnitInstruction_t s2;
  UnitInstruction_t s3;
  UnitInstruction_t s4;
  UnitInstruction_t s5;
  UnitInstruction_t s6;
  UnitInstruction_t s7;
  UnitInstruction_t t8;
  UnitInstruction_t t9;
  UnitInstruction_t k0;
  UnitInstruction_t k1;
  UnitInstruction_t gp;
  UnitInstruction_t sp;
  UnitInstruction_t fp;
  UnitInstruction_t ra;
} register_result_status_table_t;

#endif
