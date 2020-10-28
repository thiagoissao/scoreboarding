#include <stdio.h>
#include <stdbool.h>
#include "unidades_funcionais/functional_unit_status.h"
#include "unidades_funcionais/instruction_status.h"
#include "unidades_funcionais/register_result_status.h"
#include "tipos_instrucoes/i_types.h"
#include "conversor.h"

bool verifyIfAllWasWrited(instruction_status_t *inst_status_table, unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
    if (inst_status_table->writeResult == -1)
    {
      return false;
    }
  }
  return true;
}

void executeIssue(unsigned int instruction)
{
}

void readOperands(unsigned int instruction)
{
}

void executeOperands(unsigned int instruction)
{
}

void writeResult(unsigned int instruction)
{
}

void executeScoreboarding(
    unsigned int numberOfInstructions,
    functional_unit_status_table_t *fu_status_table,
    instruction_status_t *inst_status_table,
    register_result_status_table_t *rr_status_table)
{
  unsigned int clock = 0;
  bool allWasWrited = false;
  while (!allWasWrited)
  {
    executeIssue(inst_status_table[0].instruction);
    readOperands(inst_status_table[0].instruction);
    executeOperands(inst_status_table[0].instruction);
    writeResult(inst_status_table[0].instruction);

    allWasWrited = verifyIfAllWasWrited(inst_status_table, numberOfInstructions);
  }

  // unsigned int opcode = desconverteOp(instruction);
  // unsigned int rs = desconverteRs(instruction);
  // unsigned int rt = desconverteRt(instruction);

  // if (opcode == R)
  // {
  //   unsigned int rd = desconverteRd(instruction);
  //   unsigned int shamt = desconverteShamt(instruction);
  //   unsigned int funct = desconverteFunct(instruction);
  // }
  // else //tipo I
  // {
  //   unsigned int immediate = desconverteImmediate(instruction);
  // }
}
