#ifndef REGISTER_RESULT_STATUS_H
#define REGISTER_RESULT_STATUS_H

#include <stdio.h>
#include <unistd.h>
#include "./units.h"

typedef struct register_result_status
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
} register_result_status_t;

typedef struct register_result_status_linked
{
  register_result_status_t register_result_status;
  struct register_result_status_linked *next;
} register_result_status_linked_t;

void push_register_result_status(register_result_status_linked_t *head, register_result_status_t reg_res)
{
  register_result_status_linked_t *current = head;
  while (current->next != NULL)
  {
    current = current->next;
  }
  current->next = (register_result_status_linked_t *)malloc(sizeof(register_result_status_linked_t));
  current->next->register_result_status = reg_res;
  current->next->next = NULL;
}

#endif
