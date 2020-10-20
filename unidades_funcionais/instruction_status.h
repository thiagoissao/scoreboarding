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
