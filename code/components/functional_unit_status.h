#ifndef FUNCTIONAL_UNIT_STATUS_H
#define FUNCTIONAL_UNIT_STATUS_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "./units.h"
#include "../types/registers.h"
#include "../config/config.h"
#include "../types/instructions_op.h"

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
               unsigned int rd, unsigned int rs, unsigned int rt, UnitInstruction_t dependenciaQJ, UnitInstruction_t dependenciaQK)
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
    break;

  default: // vazio
    printf("Erro na inserção no FU\n");
  }
}

void init_functional_unit_status_table(functional_unit_status_table_t *fu_status_table)
{
  fu_status_table->add.name = add;
  fu_status_table->add.time = 0;
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
  fu_status_table->mult1.time = 0;
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
  fu_status_table->mult2.time = 0;
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
  fu_status_table->divide.time = 0;
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
  fu_status_table->log.time = 0;
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

bool operandsDisponiveis(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp)
{
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

UnitInstruction_t getTypeOp(unsigned int opcode, functional_unit_status_table_t *fu_table)
{
  switch (opcode)
  {
  case ADD_DECIMAL: // add
    return add;
  case ADDI_DECIMAL: //addi
    return add;
  case AND_DECIMAL: //and
    return log;
  case ANDI_DECIMAL: //andi
    return log;
  case OR_DECIMAL: //or
    return log;
  case ORI_DECIMAL: //ori
    return log;
  case SLT_DECIMAL: //slt
    return log;
  case SUB_DECIMAL: //sub
    return add;
  case MULT_DECIMAL:
  { 
    return mult1;
  }
  case DIV_DECIMAL:
    return divide;
  case LI_DECIMAL: //LI 
    return log;
  case MOVE_DECIMAL: //mov 
    return log;
  default:
    printf("Erro em Units.h\n");
    return empty;
  }
}

bool getBusy(functional_unit_status_table_t *fu_status_table, unsigned int opcode)
{
  UnitInstruction_t typeOp = getTypeOp(opcode, fu_status_table);

  if (typeOp == mult1){
    if (fu_status_table->mult1.busy){
      return fu_status_table->mult2.busy;
    }
    return fu_status_table->mult1.busy;
  }

  switch (typeOp)
  {
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

void setTimeToFu(unsigned int opcode, functional_unit_status_table_t *fu_status_table, config_t *config, int config_size, bool isMult2)
{
  unsigned int unit = getTypeOp(opcode, fu_status_table); 
  //Procura o tempo no arquivo de configuração
  int time = 1;
  for (int i = 0; i < config_size; i++)
  {
    if (opcode == config[i].opcode)
    {
      time = config[i].value;
    }
  }

  if (isMult2)
    unit = mult2;

  if (unit == mult1)
  {
    fu_status_table->mult1.time = time;
  }
  if (unit == mult2)
  {
    fu_status_table->mult2.time = time;
  }
  if (unit == add)
  {
    fu_status_table->add.time = time;
  }
  if (unit == divide)
  {
    fu_status_table->divide.time = time;
  }
  if (unit == log)
  {
    fu_status_table->log.time = time;
  }
}

unsigned int getReadFi(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp)
{
  switch (typeOp)
  {
  case mult1:
    return fu_status_table->mult1.dest_Fi;

  case mult2:
    return fu_status_table->mult2.dest_Fi;

  case add:
    return fu_status_table->add.dest_Fi;

  case divide:
    return fu_status_table->divide.dest_Fi;

  case log:
    return fu_status_table->log.dest_Fi;

  default:
    printf("Erro em GetReadFi!");
    return 1;
  }
}

bool verifyTimeRealied(UnitInstruction_t typeOp, functional_unit_status_table_t *fu_status_table){
  switch (typeOp)
  {
  case mult1:
    return !(fu_status_table->mult1.time == 0);
  case mult2:
    return !(fu_status_table->mult2.time == 0);
  case add:
    return !(fu_status_table->add.time == 0);
  case divide:
    return !(fu_status_table->divide.time == 0);
  case log:
    return !(fu_status_table->log.time == 0);
  
  default:
    printf("Fu vazio!");
    return false;
  }
}

#endif
