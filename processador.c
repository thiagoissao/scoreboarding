#include <stdio.h>
#include "unidades_funcionais/functional_unit_status.h"
#include "unidades_funcionais/instruction_status.h"
#include "unidades_funcionais/register_result_status.h"
#include "tipos_instrucoes/i_types.h"
#include "conversor.h"

void execute(
    unsigned int instruction,
    functional_unit_status_table_t *fu_status_table,
    instruction_status_linked_t *inst_status_list,
    register_result_status_linked_t *rr_status_list)
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
