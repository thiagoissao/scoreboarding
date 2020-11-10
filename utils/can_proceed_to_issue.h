#ifndef CAN_PROCEED_TO_ISSUE_H
#define CAN_PROCEED_TO_ISSUE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../components/functional_unit_status.h"
#include "../components/register_result_status.h"
#include "../types/i_types.h"
#include "../conversor.h"
#include "../utils/utils.h"
#include "../components/units.h"

bool can_proceed_to_issue(
    unsigned int instruction,
    functional_unit_status_table_t *fu_status_table,
    register_result_status_table_t *rr_status_table)
{
  unsigned int opcode = desconverteOp(instruction);
  unsigned int funct = desconverteFunct(instruction);
  unsigned int rs = desconverteRs(instruction);
  unsigned int rd = desconverteRd(instruction);

  bool isTypeR = isR(instruction);
  bool wawDependency = false;
  char *regChar;
  if (isTypeR)
  {
    regChar = registerToString(rd);
  }
  else
  {
    regChar = registerToString(rs);
  }

  if (strcmp(regChar, zero_reg) == 0 && rr_status_table->zero != empty)
    wawDependency = true;

  if (strcmp(regChar, at_reg) == 0 && rr_status_table->at != empty)
    wawDependency = true;

  if (strcmp(regChar, v0_reg) == 0 && rr_status_table->v0 != empty)
    wawDependency = true;

  if (strcmp(regChar, v1_reg) == 0 && rr_status_table->v1 != empty)
    wawDependency = true;

  if (strcmp(regChar, a0_reg) == 0 && rr_status_table->a0 != empty)
    wawDependency = true;

  if (strcmp(regChar, a1_reg) == 0 && rr_status_table->a1 != empty)
    wawDependency = true;

  if (strcmp(regChar, a2_reg) == 0 && rr_status_table->a2 != empty)
    wawDependency = true;

  if (strcmp(regChar, a3_reg) == 0 && rr_status_table->a3 != empty)
    wawDependency = true;

  if (strcmp(regChar, t0_reg) == 0 && rr_status_table->t0 != empty)
    wawDependency = true;

  if (strcmp(regChar, t1_reg) == 0 && rr_status_table->t1 != empty)
    wawDependency = true;

  if (strcmp(regChar, t2_reg) == 0 && rr_status_table->t2 != empty)
    wawDependency = true;

  if (strcmp(regChar, t3_reg) == 0 && rr_status_table->t3 != empty)
    wawDependency = true;

  if (strcmp(regChar, t4_reg) == 0 && rr_status_table->t4 != empty)
    wawDependency = true;

  if (strcmp(regChar, t5_reg) == 0 && rr_status_table->t5 != empty)
    wawDependency = true;

  if (strcmp(regChar, t6_reg) == 0 && rr_status_table->t6 != empty)
    wawDependency = true;

  if (strcmp(regChar, t7_reg) == 0 && rr_status_table->t7 != empty)
    wawDependency = true;

  if (strcmp(regChar, s0_reg) == 0 && rr_status_table->s0 != empty)
    wawDependency = true;

  if (strcmp(regChar, s1_reg) == 0 && rr_status_table->s1 != empty)
    wawDependency = true;

  if (strcmp(regChar, s2_reg) == 0 && rr_status_table->s2 != empty)
    wawDependency = true;

  if (strcmp(regChar, s3_reg) == 0 && rr_status_table->s3 != empty)
    wawDependency = true;

  if (strcmp(regChar, s4_reg) == 0 && rr_status_table->s4 != empty)
    wawDependency = true;

  if (strcmp(regChar, s5_reg) == 0 && rr_status_table->s5 != empty)
    wawDependency = true;

  if (strcmp(regChar, s6_reg) == 0 && rr_status_table->s6 != empty)
    wawDependency = true;

  if (strcmp(regChar, s7_reg) == 0 && rr_status_table->s7 != empty)
    wawDependency = true;

  if (strcmp(regChar, t8_reg) == 0 && rr_status_table->t8 != empty)
    wawDependency = true;

  if (strcmp(regChar, t9_reg) == 0 && rr_status_table->t9 != empty)
    wawDependency = true;

  if (strcmp(regChar, k0_reg) == 0 && rr_status_table->k0 != empty)
    wawDependency = true;

  if (strcmp(regChar, k1_reg) == 0 && rr_status_table->k1 != empty)
    wawDependency = true;

  if (strcmp(regChar, gp_reg) == 0 && rr_status_table->gp != empty)
    wawDependency = true;

  if (strcmp(regChar, sp_reg) == 0 && rr_status_table->sp != empty)
    wawDependency = true;

  if (strcmp(regChar, fp_reg) == 0 && rr_status_table->fp != empty)
    wawDependency = true;

  if (strcmp(regChar, ra_reg) == 0 && rr_status_table->ra != empty)
    wawDependency = true;

  //Verifica se está a unidade está ocupada
  if (isTypeR)
  {
    return !getBusy(fu_status_table, funct) && !wawDependency;
  }
  return !getBusy(fu_status_table, opcode) && !wawDependency;
}

#endif
