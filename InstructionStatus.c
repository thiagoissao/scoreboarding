#include <stdio.h>

typedef struct InstructionStatus
{
  int instruction;
  int issue;
  int readOperand;
  int execComp;
  int writeResult;
};

int getOpcode(int instruction)
{
  return 0;
}
