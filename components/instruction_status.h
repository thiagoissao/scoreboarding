#ifndef INSTRUCTION_STATUS_H
#define INSTRUCTION_STATUS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct instruction_status
{
  unsigned int instruction;
  int issue;
  int readOperand;
  int execComp;
  int writeResult;
} instruction_status_t;

void init_instruction_status_table(instruction_status_t *table, unsigned int *instruction_set, int numberOfInstructions)
{
  for (int i = 0; i < numberOfInstructions; i++)
  {
    table[i].instruction = instruction_set[i];
    table[i].issue = -1;
    table[i].readOperand = -1;
    table[i].execComp = -1;
    table[i].writeResult = -1;
  }
}

#endif
