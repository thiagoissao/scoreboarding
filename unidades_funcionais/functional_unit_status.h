#ifndef FUNCTIONAL_UNIT_STATUS_H
#define FUNCTIONAL_UNIT_STATUS_H

#include <stdio.h>
#include <unistd.h>
#include "./units.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct functional_unit_status
{
  int time;
  UnitInstruction_t name;
  bool busy;
  unsigned int op : 6;
  unsigned int dest_Fi : 5;
  unsigned int s1_Fj : 5;
  unsigned int s2_Fk : 5;
  UnitInstruction_t fu_Qj;
  UnitInstruction_t fu_Qk;
  bool fj_Rj;
  bool fj_Rk;
} functional_unit_status_t;

typedef struct functional_unit_status_table
{
  functional_unit_status_t add;
  functional_unit_status_t addi;
  functional_unit_status_t and;
  functional_unit_status_t andi;
  functional_unit_status_t or ;
  functional_unit_status_t ori;
  functional_unit_status_t slt;
  functional_unit_status_t sub;
  functional_unit_status_t mult;
  functional_unit_status_t div;
  functional_unit_status_t li;
  functional_unit_status_t move;
} functional_unit_status_table_t;

#endif
