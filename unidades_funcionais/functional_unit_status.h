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

typedef struct functional_unit_status_linked
{
  functional_unit_status_t functional_unit_status;
  struct functional_unit_status_linked *next;
} functional_unit_status_linked_t;

void push_functional_unit_status(functional_unit_status_linked_t *head, functional_unit_status_t fu)
{
  functional_unit_status_linked_t *current = head;
  while (current->next != NULL)
  {
    current = current->next;
  }
  current->next = (functional_unit_status_linked_t *)malloc(sizeof(functional_unit_status_linked_t));
  current->next->functional_unit_status = fu;
  current->next->next = NULL;
}

#endif
