#ifndef VERIFICATIONS_H
#define VERIFICATIONS_H

#include <stdio.h>
#include <stdbool.h>
#include "../components/instruction_status.h"
#include "../components/functional_unit_status.h"
#include "../components/units.h"
#include "../types/instructions_op.h"

bool verify_if_all_was_writed(instruction_status_t *inst_status_table, unsigned int size, int clock)
{
  for (int i = 0; i < size; i++)
  {
    if (inst_status_table[i].writeResult == -1)
    {
      return false;
    }
  }
  return true;
}

void verify_dependency(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp,
                       unsigned int fjAtual, unsigned int fkAtual, unsigned int opcode,
                       UnitInstruction_t *dependenciaQJ, UnitInstruction_t *dependenciaQK)
{
  *dependenciaQJ = empty;
  *dependenciaQK = empty;

  if (fu_status_table->add.busy && typeOp != ADD_FU_DECIMAL)
  {
    if (fu_status_table->add.dest_Fi == fjAtual)
      *dependenciaQJ = ADD_FU_DECIMAL;

    if (fu_status_table->add.dest_Fi == fkAtual)
      *dependenciaQK = ADD_FU_DECIMAL;
  }

  if (fu_status_table->mult1.busy && typeOp != MULT1_FU_DECIMAL)
  {
    if (fu_status_table->mult1.dest_Fi == fjAtual)
      *dependenciaQJ = MULT1_FU_DECIMAL;

    if (fu_status_table->mult1.dest_Fi == fkAtual)
      *dependenciaQK = MULT1_FU_DECIMAL;
  }

  if (fu_status_table->mult2.busy && typeOp != MULT2_FU_DECIMAL)
  {
    if (fu_status_table->mult2.dest_Fi == fjAtual)
      *dependenciaQJ = MULT2_FU_DECIMAL;

    if (fu_status_table->mult2.dest_Fi == fkAtual)
      *dependenciaQK = MULT2_FU_DECIMAL;
  }

  if (fu_status_table->divide.busy && typeOp != DIVIDE_FU_DECIMAL)
  {
    if (fu_status_table->divide.dest_Fi == fjAtual)
      *dependenciaQJ = DIVIDE_FU_DECIMAL;

    if (fu_status_table->divide.dest_Fi == fkAtual)
      *dependenciaQK = DIVIDE_FU_DECIMAL;
  }

  if (fu_status_table->log.busy && typeOp != LOG_FU_DECIMAL)
  {
    if (fu_status_table->log.dest_Fi == fjAtual)
      *dependenciaQJ = LOG_FU_DECIMAL;

    if (fu_status_table->log.dest_Fi == fkAtual)
      *dependenciaQK = LOG_FU_DECIMAL;
  }
}

bool verify_raw(functional_unit_status_table_t *fu_status_table,
                UnitInstruction_t typeOp)
{
  unsigned int Fi, idComparacao;
  Fi = getReadFi(fu_status_table, typeOp);

  // atentar depois ao clock de uma instrucao que teve que esperar um read anteriormente

  if (fu_status_table->mult1.busy && typeOp != mult1 && ((fu_status_table->mult1.s1_Fj == Fi && fu_status_table->mult1.fj_Rj) || (fu_status_table->mult1.s2_Fk == Fi && fu_status_table->mult1.fj_Rk)))
    return false;
  if (fu_status_table->mult2.busy && typeOp != mult2 && ((fu_status_table->mult2.s1_Fj == Fi && fu_status_table->mult2.fj_Rj) || (fu_status_table->mult2.s2_Fk == Fi && fu_status_table->mult2.fj_Rk)))
    return false;
  if (fu_status_table->add.busy && typeOp != add && ((fu_status_table->add.s1_Fj == Fi && fu_status_table->add.fj_Rj) || (fu_status_table->add.s2_Fk == Fi && fu_status_table->add.fj_Rk)))
    return false;
  if (fu_status_table->divide.busy && typeOp != divide && ((fu_status_table->divide.s1_Fj == Fi && fu_status_table->divide.fj_Rj) || (fu_status_table->divide.s2_Fk == Fi && fu_status_table->divide.fj_Rk)))
    return false;
  if (fu_status_table->log.busy && typeOp != log && ((fu_status_table->log.s1_Fj == Fi && fu_status_table->log.fj_Rj) || (fu_status_table->log.s2_Fk == Fi && fu_status_table->log.fj_Rk)))
    return false;
  // SE (ta ocupado  &&  diferente do FU dele  && ( (Destino Fi == Fj && dependencia Rj) OU
  //                                                (Destino Fi == Fk && dependencia Rk)  ))
  //                                              se tem dependencia R siginica que a instrucao
  //                                                       do write ta antes das inst de dependencias
  //  ae se entrar quer dizer que nao pode proceguir pra write

  return true;
}

#endif
