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

void init_register_status_table(register_result_status_table_t *rr_status_table){
  rr_status_table->zero = empty;
  rr_status_table->at = empty;
  rr_status_table->v0 = empty;
  rr_status_table->v1 = empty;
  rr_status_table->a0 = empty;
  rr_status_table->a1 = empty;
  rr_status_table->a2 = empty;
  rr_status_table->a3 = empty;
  rr_status_table->t0 = empty;
  rr_status_table->t1 = empty;
  rr_status_table->t2 = empty;
  rr_status_table->t3 = empty;
  rr_status_table->t4 = empty;
  rr_status_table->t5 = empty;
  rr_status_table->t6 = empty;
  rr_status_table->t7 = empty;
  rr_status_table->s0 = empty;
  rr_status_table->s1 = empty;
  rr_status_table->s2 = empty;
  rr_status_table->s3 = empty;
  rr_status_table->s4 = empty;
  rr_status_table->s5 = empty;
  rr_status_table->s6 = empty;
  rr_status_table->s7 = empty;
  rr_status_table->t8 = empty;
  rr_status_table->t9 = empty;
  rr_status_table->k0 = empty;
  rr_status_table->k1 = empty;
  rr_status_table->gp = empty;
  rr_status_table->sp = empty;
  rr_status_table->fp = empty;
  rr_status_table->ra = empty;
}

#endif
