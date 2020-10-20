#include <stdio.h>
#include <unistd.h>

typedef struct instruction_status
{
  int instruction;
  int issue;
  int readOperand;
  int execComp;
  int writeResult;
} instruction_status_t;

int getOpcode(int instruction)
{
  return 0;
}
