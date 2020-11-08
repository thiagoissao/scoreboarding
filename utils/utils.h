#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "../types/i_types.h"
#include "../conversor.h"
#include "verifications.h"
#include "../components/functional_unit_status.h"
#include "../components/instruction_status.h"
#include "../components/register_result_status.h"

bool isR(unsigned int instr)
{
  unsigned int opcode;
  opcode = desconverteOp(instr);

  return opcode == R;
}

bool opera_latencia(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp)
{
  switch (typeOp)
  {
  case mult1:
    fu_status_table->mult1.time -= 1;
    return fu_status_table->mult1.time == 0;

  case mult2:
    fu_status_table->mult2.time -= 1;
    return fu_status_table->mult2.time == 0;

  case add:
    fu_status_table->add.time -= 1;
    return fu_status_table->add.time == 0;

  case divide:
    fu_status_table->divide.time -= 1;
    return fu_status_table->divide.time == 0;

  case log:
    fu_status_table->log.time -= 1;
    return fu_status_table->log.time == 0;

  default:
    printf("Erro ao operar latencia!");
    return false;
  }
}

void define_next_step(bool *nextStep, unsigned int numberInst)
{
  int i;
  for (i = 0; i < numberInst; i++)
  {
    nextStep[i] = true;
  }
}

void update_functional_unit_table(unsigned int instruction, functional_unit_status_table_t *fu_status_table)
{
  UnitInstruction_t dependenciaQK, dependenciaQJ, typeOp;
  unsigned int funct, rs, rt, opcode, rd, shamt, immediate;

  rs = desconverteRs(instruction);
  rt = desconverteRt(instruction);
  opcode = desconverteOp(instruction);

  if (isR(instruction))
  {
    rd = desconverteRd(instruction);
    shamt = desconverteShamt(instruction);
    funct = desconverteFunct(instruction);
    typeOp = getTypeOp(funct, fu_status_table);
  }
  else
  {
    typeOp = getTypeOp(opcode, fu_status_table);
    rd = rs;
    rs = rt;
    rt = 0;
  }

  //verifica Rk e Rj e passar pra preencher tb
  isR(instruction) ? verify_dependency(fu_status_table, typeOp, rs, rt, opcode, &dependenciaQJ, &dependenciaQK) : verify_dependency(fu_status_table, typeOp, rs, rt, funct, &dependenciaQJ, &dependenciaQK);

  if (isR(instruction))
    setInstFu(fu_status_table, typeOp, funct, rd, rs, rt, dependenciaQJ, dependenciaQK);
  else
    setInstFu(fu_status_table, typeOp, opcode, rd, rs, rt, dependenciaQJ, dependenciaQK);
}

void update_register_result_table(
    unsigned int instruction,
    register_result_status_table_t *rr_status_table,
    functional_unit_status_table_t *fu_status_table,
    bool isRType)
{
  unsigned int opcode, registrador;
  UnitInstruction_t typeOp;

  if (isRType)
  {
    opcode = desconverteFunct(instruction);
    registrador = desconverteRd(instruction);
  }
  else
  {
    opcode = desconverteOp(instruction);
    registrador = desconverteRs(instruction);
  }

  typeOp = getTypeOp(opcode, fu_status_table);

  setRegisterResult(rr_status_table, registrador, typeOp);
}

#endif
