#ifndef FUNCTIONAL_UNIT_STATUS_H
#define FUNCTIONAL_UNIT_STATUS_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./units.h"
#include "../tipos_instrucoes/registers.h"

typedef struct functional_unit_status
{
  int time;
  UnitInstruction_t name;
  bool busy;
  unsigned int op : 6;
  unsigned int dest_Fi : 5;
  unsigned int s1_Fj : 5;
  unsigned int s2_Fk : 5;
  UnitInstruction_t fu_Qj;
  UnitInstruction_t fu_Qk;
  bool fj_Rj;
  bool fj_Rk;
} functional_unit_status_t;

typedef struct functional_unit_status_table
{
  functional_unit_status_t log;
  functional_unit_status_t mult1;
  functional_unit_status_t mult2;
  functional_unit_status_t add;
  functional_unit_status_t divide;
} functional_unit_status_table_t;

void setInstFu(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp, unsigned int opcode,
               unsigned int rd, unsigned int rs, unsigned int rt, UnitInstruction_t dependenciaQJ, UnitInstruction_t dependenciaQK,
               int time)
{
  bool noDependenciaRJ, noDependenciaRK;

  noDependenciaRJ = true;
  noDependenciaRK = true;

  if (dependenciaQJ != empty)
    noDependenciaRJ = false;

  if (dependenciaQK != empty)
    noDependenciaRK = false;

  switch (typeOp)
  {
  case mult1:
    fu_status_table->mult1.busy = !fu_status_table->mult1.busy;
    fu_status_table->mult1.op = opcode;
    fu_status_table->mult1.dest_Fi = rd;
    fu_status_table->mult1.s1_Fj = rs;
    fu_status_table->mult1.s2_Fk = rt;
    fu_status_table->mult1.fu_Qj = dependenciaQJ;
    fu_status_table->mult1.fu_Qk = dependenciaQK;
    fu_status_table->mult1.fj_Rj = noDependenciaRJ;
    fu_status_table->mult1.fj_Rk = noDependenciaRK;
    fu_status_table->mult1.time = 1; // precisamos definir o time de cada op e passar p esses geral
    break;

  case mult2:
    fu_status_table->mult2.busy = !fu_status_table->mult2.busy;
    fu_status_table->mult2.op = opcode;
    fu_status_table->mult2.dest_Fi = rd;
    fu_status_table->mult2.s1_Fj = rs;
    fu_status_table->mult2.s2_Fk = rt;
    fu_status_table->mult2.fu_Qj = dependenciaQJ;
    fu_status_table->mult2.fu_Qk = dependenciaQK;
    fu_status_table->mult2.fj_Rj = noDependenciaRJ;
    fu_status_table->mult2.fj_Rk = noDependenciaRK;
    fu_status_table->mult2.time = time;
    break;

  case add:
    fu_status_table->add.busy = !fu_status_table->add.busy;
    fu_status_table->add.op = opcode;
    fu_status_table->add.dest_Fi = rd;
    fu_status_table->add.s1_Fj = rs;
    fu_status_table->add.s2_Fk = rt;
    fu_status_table->add.fu_Qj = dependenciaQJ;
    fu_status_table->add.fu_Qk = dependenciaQK;
    fu_status_table->add.fj_Rj = noDependenciaRJ;
    fu_status_table->add.fj_Rk = noDependenciaRK;
    fu_status_table->add.time = time;
    break;

  case divide:
    fu_status_table->divide.busy = !fu_status_table->divide.busy;
    fu_status_table->divide.op = opcode;
    fu_status_table->divide.dest_Fi = rd;
    fu_status_table->divide.s1_Fj = rs;
    fu_status_table->divide.s2_Fk = rt;
    fu_status_table->divide.fu_Qj = dependenciaQJ;
    fu_status_table->divide.fu_Qk = dependenciaQK;
    fu_status_table->divide.fj_Rj = noDependenciaRJ;
    fu_status_table->divide.fj_Rk = noDependenciaRK;
    fu_status_table->divide.time = time;
    break;

  case log:
    fu_status_table->log.busy = !fu_status_table->log.busy;
    fu_status_table->log.op = opcode;
    fu_status_table->log.dest_Fi = rd;
    fu_status_table->log.s1_Fj = rs;
    fu_status_table->log.s2_Fk = rt;
    fu_status_table->log.fu_Qj = dependenciaQJ;
    fu_status_table->log.fu_Qk = dependenciaQK;
    fu_status_table->log.fj_Rj = noDependenciaRJ;
    fu_status_table->log.fj_Rk = noDependenciaRK;
    fu_status_table->log.time = time;
    break;

  default: // vazio
    printf("Erro na inserção no FU\n");
  }
}

bool getBusy(functional_unit_status_table_t *fu_status_table, unsigned int opcode)
{
  // verificar por aq se pa se ta escrevendo no msm destino rsrs
  UnitInstruction_t typeOp;

  typeOp = getTypeOp(opcode);

  switch (typeOp)
  {
  case 0: //mult1
    return fu_status_table->mult1.busy;

  case 1: //mult2
    return fu_status_table->mult2.busy;

  case 2: // add
    return fu_status_table->add.busy;

  case 3: //divide
    return fu_status_table->divide.busy;

  case 4: //integer
    return fu_status_table->log.busy;

  default: // vazio
    printf("Erro em getBusy da FU\n");
    return false;
  }
}

void init_functional_unit_status_table(functional_unit_status_table_t *fu_status_table)
{
  fu_status_table->add.name = add;
  fu_status_table->add.time = 1;
  fu_status_table->add.busy = false;
  fu_status_table->add.op = 0;
  fu_status_table->add.dest_Fi = zero_dec;
  fu_status_table->add.s1_Fj = zero_dec;
  fu_status_table->add.s2_Fk = zero_dec;
  fu_status_table->add.fu_Qj = empty;
  fu_status_table->add.fu_Qk = empty;
  fu_status_table->add.fj_Rj = true;
  fu_status_table->add.fj_Rk = true;

  fu_status_table->mult1.name = mult1;
  fu_status_table->mult1.time = 1;
  fu_status_table->mult1.busy = false;
  fu_status_table->mult1.op = 0;
  fu_status_table->mult1.dest_Fi = zero_dec;
  fu_status_table->mult1.s1_Fj = zero_dec;
  fu_status_table->mult1.s2_Fk = zero_dec;
  fu_status_table->mult1.fu_Qj = empty;
  fu_status_table->mult1.fu_Qk = empty;
  fu_status_table->mult1.fj_Rj = true;
  fu_status_table->mult1.fj_Rk = true;

  fu_status_table->mult2.name = mult2;
  fu_status_table->mult2.time = 1;
  fu_status_table->mult2.busy = false;
  fu_status_table->mult2.op = 0;
  fu_status_table->mult2.dest_Fi = zero_dec;
  fu_status_table->mult2.s1_Fj = zero_dec;
  fu_status_table->mult2.s2_Fk = zero_dec;
  fu_status_table->mult2.fu_Qj = empty;
  fu_status_table->mult2.fu_Qk = empty;
  fu_status_table->mult2.fj_Rj = true;
  fu_status_table->mult2.fj_Rk = true;

  fu_status_table->divide.name = divide;
  fu_status_table->divide.time = 1;
  fu_status_table->divide.busy = false;
  fu_status_table->divide.op = 0;
  fu_status_table->divide.dest_Fi = zero_dec;
  fu_status_table->divide.s1_Fj = zero_dec;
  fu_status_table->divide.s2_Fk = zero_dec;
  fu_status_table->divide.fu_Qj = empty;
  fu_status_table->divide.fu_Qk = empty;
  fu_status_table->divide.fj_Rj = true;
  fu_status_table->divide.fj_Rk = true;

  fu_status_table->log.name = log;
  fu_status_table->log.time = 1;
  fu_status_table->log.busy = false;
  fu_status_table->log.op = 0;
  fu_status_table->log.dest_Fi = zero_dec;
  fu_status_table->log.s1_Fj = zero_dec;
  fu_status_table->log.s2_Fk = zero_dec;
  fu_status_table->log.fu_Qj = empty;
  fu_status_table->log.fu_Qk = empty;
  fu_status_table->log.fj_Rj = true;
  fu_status_table->log.fj_Rk = true;
}

bool operandsDisponiveis(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp){
  bool dependenciaRJ, dependenciaRK;

  switch (typeOp)
  {
  case mult1:
    dependenciaRJ = fu_status_table->mult1.fj_Rj;
    dependenciaRK = fu_status_table->mult1.fj_Rk;

    if (dependenciaRJ && dependenciaRK)
      return true;
    else
      return false;

  case mult2:
    dependenciaRJ = fu_status_table->mult2.fj_Rj;
    dependenciaRK = fu_status_table->mult2.fj_Rk;

    if (dependenciaRJ && dependenciaRK)
      return true;
    else
      return false;

  case add:
    dependenciaRJ = fu_status_table->add.fj_Rj;
    dependenciaRK = fu_status_table->add.fj_Rk;

    if (dependenciaRJ && dependenciaRK)
      return true;
    else
      return false;

  case divide:
    dependenciaRJ = fu_status_table->divide.fj_Rj;
    dependenciaRK = fu_status_table->divide.fj_Rk;

    if (dependenciaRJ && dependenciaRK)
      return true;
    else
      return false;

  case log:
    dependenciaRJ = fu_status_table->log.fj_Rj;
    dependenciaRK = fu_status_table->log.fj_Rk;

    if (dependenciaRJ && dependenciaRK)
      return true;
    else
      return false;

  default:
    printf("Erro na verificacao da dependencia do operando!");
    break;
  }
}

#endif
