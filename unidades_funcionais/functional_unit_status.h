#ifndef FUNCTIONAL_UNIT_STATUS_H
#define FUNCTIONAL_UNIT_STATUS_H

#include <stdio.h>
#include <unistd.h>
#include "./units.h"
#include <stdbool.h>
#include <stdlib.h>

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
  functional_unit_status_t integer;
  functional_unit_status_t mult1;
  functional_unit_status_t mult2;
  functional_unit_status_t add;
  functional_unit_status_t divide;
} functional_unit_status_table_t;

void setInstFu(functional_unit_status_table_t *fu_status_table, unsigned int opcode, 
  unsigned int rd, unsigned int rs, unsigned int rt){
  
  UnitInstruction_t typeOp;

  typeOp = getTypeOp(opcode);

  switch (typeOp)
  {
  case 0: //mult1
    fu_status_table->mult1.busy    = !fu_status_table->mult1.busy;
    fu_status_table->mult1.op      = opcode;
    fu_status_table->mult1.dest_Fi = rd;
    fu_status_table->mult1.s1_Fj   = rd;
    fu_status_table->mult1.s2_Fk   = rt;
    fu_status_table->mult1.fu_Qj   = 1;
    fu_status_table->mult1.fu_Qk   = 1;
    fu_status_table->mult1.fj_Rj   = 1;
    fu_status_table->mult1.fj_Rk   = 1;
    //fu_status_table->mult1.time = 1; n entedi o q mais
    break;

  case 1: //mult2
    fu_status_table->mult2.busy    = !fu_status_table->mult2.busy;
    fu_status_table->mult2.op      = opcode;
    fu_status_table->mult2.dest_Fi = rd;
    fu_status_table->mult2.s1_Fj   = rd;
    fu_status_table->mult2.s2_Fk   = rt;
    fu_status_table->mult2.fu_Qj   = 1;
    fu_status_table->mult2.fu_Qk   = 1;
    fu_status_table->mult2.fj_Rj   = 1;
    fu_status_table->mult2.fj_Rk   = 1;
    break;

  case 2: // add
    fu_status_table->add.busy      = !fu_status_table->add.busy;
    fu_status_table->add.op        = opcode;
    fu_status_table->add.dest_Fi   = rd;
    fu_status_table->add.s1_Fj     = rd;
    fu_status_table->add.s2_Fk     = rt;
    fu_status_table->add.fu_Qj     = 1;
    fu_status_table->add.fu_Qk     = 1;
    fu_status_table->add.fj_Rj     = 1;
    fu_status_table->add.fj_Rk     = 1;
    break;
  
  case 3: //divide
    fu_status_table->divide.busy    = !fu_status_table->divide.busy;
    fu_status_table->divide.op      = opcode;
    fu_status_table->divide.dest_Fi = rd;
    fu_status_table->divide.s1_Fj   = rd;
    fu_status_table->divide.s2_Fk   = rt;
    fu_status_table->divide.fu_Qj   = 1;
    fu_status_table->divide.fu_Qk   = 1;
    fu_status_table->divide.fj_Rj   = 1;
    fu_status_table->divide.fj_Rk   = 1;
    break;

  case 4: //integer
    fu_status_table->integer.busy   = !fu_status_table->integer.busy;
    fu_status_table->integer.op     = opcode;
    fu_status_table->integer.dest_Fi= rd;
    fu_status_table->integer.s1_Fj  = rd;
    fu_status_table->integer.s2_Fk  = rt;
    fu_status_table->integer.fu_Qj  = 1;
    fu_status_table->integer.fu_Qk  = 1;
    fu_status_table->integer.fj_Rj  = 1;
    fu_status_table->integer.fj_Rk  = 1;
    break;

  default: // vazio
    printf("Erro na inserção no FU\n");
  }

  }

bool getBusy(functional_unit_status_table_t *fu_status_table, unsigned int opcode){
  switch (opcode)
  {
  case 32: // add
    return fu_status_table->add.busy;
  case 8: //addi
    return fu_status_table->add.busy;
  case 36: //and
    return fu_status_table->integer.busy;
  case 12: //andi
    return fu_status_table->integer.busy;
  case 37: //or
    return fu_status_table->integer.busy;
  case 13: //ori
    return fu_status_table->integer.busy;
  case 42: //slt
    return fu_status_table->integer.busy;
  case 34: //sub
    return fu_status_table->add.busy;
  case 24: //mult1 se pa
    return fu_status_table->mult1.busy;
  case 25: //mult2 se pa
    return fu_status_table->mult2.busy;
  case 1: //LI -> arrumar
    return fu_status_table->integer.busy;
  case 2: //mov -> arrumar
    return fu_status_table->integer.busy;
  default:
    printf("Erro na leitura do FU correspondente\n");
    return false;
  }
}

void init_funcional_unit_status_table(functional_unit_status_table_t *fu_status_table){
  fu_status_table->add.time      = -1;
  fu_status_table->add.name      = 2;
  fu_status_table->add.busy      = false;
  fu_status_table->add.op        = 0;
  fu_status_table->add.dest_Fi   = 0;
  fu_status_table->add.s1_Fj     = 0;
  fu_status_table->add.s2_Fk     = 0;
  fu_status_table->add.fu_Qj     = 0; // deveria ter um sem nada
  fu_status_table->add.fu_Qk     = 0; // deveria ter um sem nada
  fu_status_table->add.fj_Rj     = false;
  fu_status_table->add.fj_Rk     = false;

  fu_status_table->mult1.time    = -1;
  fu_status_table->mult1.name    = 2;
  fu_status_table->mult1.busy    = false;
  fu_status_table->mult1.op      = 0;
  fu_status_table->mult1.dest_Fi = 0;
  fu_status_table->mult1.s1_Fj   = 0;
  fu_status_table->mult1.s2_Fk   = 0;
  fu_status_table->mult1.fu_Qj   = 0; // deveria ter um sem nada
  fu_status_table->mult1.fu_Qk   = 0; // deveria ter um sem nada
  fu_status_table->mult1.fj_Rj   = false;
  fu_status_table->mult1.fj_Rk   = false;

  fu_status_table->mult2.time    = -1;
  fu_status_table->mult2.name    = 2;
  fu_status_table->mult2.busy    = false;
  fu_status_table->mult2.op      = 0;
  fu_status_table->mult2.dest_Fi = 0;
  fu_status_table->mult2.s1_Fj   = 0;
  fu_status_table->mult2.s2_Fk   = 0;
  fu_status_table->mult2.fu_Qj   = 0; // deveria ter um sem nada
  fu_status_table->mult2.fu_Qk   = 0; // deveria ter um sem nada
  fu_status_table->mult2.fj_Rj   = false;
  fu_status_table->mult2.fj_Rk   = false;

  fu_status_table->divide.time   = -1;
  fu_status_table->divide.name   = 2;
  fu_status_table->divide.busy   = false;
  fu_status_table->divide.op     = 0;
  fu_status_table->divide.dest_Fi= 0;
  fu_status_table->divide.s1_Fj  = 0;
  fu_status_table->divide.s2_Fk  = 0;
  fu_status_table->divide.fu_Qj  = 0; // deveria ter um sem nada
  fu_status_table->divide.fu_Qk  = 0; // deveria ter um sem nada
  fu_status_table->divide.fj_Rj  = false;
  fu_status_table->divide.fj_Rk  = false;

  fu_status_table->integer.time    = -1;
  fu_status_table->integer.name    = 2;
  fu_status_table->integer.busy    = false;
  fu_status_table->integer.op      = 0;
  fu_status_table->integer.dest_Fi = 0;
  fu_status_table->integer.s1_Fj   = 0;
  fu_status_table->integer.s2_Fk   = 0;
  fu_status_table->integer.fu_Qj   = 0; // deveria ter um sem nada
  fu_status_table->integer.fu_Qk   = 0; // deveria ter um sem nada
  fu_status_table->integer.fj_Rj   = false;
  fu_status_table->integer.fj_Rk   = false;
}

#endif
