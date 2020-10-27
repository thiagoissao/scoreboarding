#include <stdio.h>
#include "unidades_funcionais/functional_unit_status.h"
#include "unidades_funcionais/instruction_status.h"
#include "unidades_funcionais/register_result_status.h"
#include "tipos_instrucoes/i_types.h"
#include "conversor.h"

void execute(
    unsigned int instruction,
    functional_unit_status_t functional_unit_status,
    instruction_status_t instruction_status,
    register_result_status_t register_result_status)
{
  unsigned int opcode = desconverteOp(instruction);
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);

  if (opcode == R)
  {
    unsigned int rd = desconverteRd(instruction);
    unsigned int shamt = desconverteShamt(instruction);
    unsigned int funct = desconverteFunct(instruction);
  }
  else //tipo I
  {
    unsigned int immediate = desconverteImmediate(instruction);
  }
}
