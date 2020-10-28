#ifndef INSTRUCTION_STATUS_H
#define INSTRUCTION_STATUS_H

#include <stdio.h>
#include <unistd.h>

typedef struct instruction_status
{
  unsigned int instruction : 32;
  int issue;
  int readOperand;
  int execComp;
  int writeResult;
} instruction_status_t;

typedef struct instruction_status_linked
{
  instruction_status_t instruction_status;
  struct instruction_status_linked *next;
} instruction_status_linked_t;

void push_instruction_status(instruction_status_linked_t *head, instruction_status_t instr_s)
{
  instruction_status_linked_t *current = head;
  while (current->next != NULL)
  {
    current = current->next;
  }
  current->next = (instruction_status_linked_t *)malloc(sizeof(instruction_status_linked_t));
  current->next->instruction_status = instr_s;
  current->next->next = NULL;
}

#endif
