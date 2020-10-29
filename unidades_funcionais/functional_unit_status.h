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
      fu_status_table->mult1.s1_Fj   = rs;
      fu_status_table->mult1.s2_Fk   = rt;
      fu_status_table->mult1.fu_Qj   = 1;
      fu_status_table->mult1.fu_Qk   = 1;
      fu_status_table->mult1.fj_Rj   = 1;
      fu_status_table->mult1.fj_Rk   = 1;
      fu_status_table->mult1.name    = mult1;
      //fu_status_table->mult1.time = 1; n entedi o q mais
      break;

    case 1: //mult2
      fu_status_table->mult2.busy    = !fu_status_table->mult2.busy;
      fu_status_table->mult2.op      = opcode;
      fu_status_table->mult2.dest_Fi = rd;
      fu_status_table->mult2.s1_Fj   = rs;
      fu_status_table->mult2.s2_Fk   = rt;
      fu_status_table->mult2.fu_Qj   = 1;
      fu_status_table->mult2.fu_Qk   = 1;
      fu_status_table->mult2.fj_Rj   = 1;
      fu_status_table->mult2.fj_Rk   = 1;
      fu_status_table->mult2.name    = mult2;
      break;

    case 2: // add
      fu_status_table->add.busy      = !fu_status_table->add.busy;
      fu_status_table->add.op        = opcode;
      fu_status_table->add.dest_Fi   = rd;
      fu_status_table->add.s1_Fj     = rs;
      fu_status_table->add.s2_Fk     = rt;
      fu_status_table->add.fu_Qj     = 1;
      fu_status_table->add.fu_Qk     = 1;
      fu_status_table->add.fj_Rj     = 1;
      fu_status_table->add.fj_Rk     = 1;
      fu_status_table->add.name      = add;
      break;
    
    case 3: //divide
      fu_status_table->divide.busy    = !fu_status_table->divide.busy;
      fu_status_table->divide.op      = opcode;
      fu_status_table->divide.dest_Fi = rd;
      fu_status_table->divide.s1_Fj   = rs;
      fu_status_table->divide.s2_Fk   = rt;
      fu_status_table->divide.fu_Qj   = 1;
      fu_status_table->divide.fu_Qk   = 1;
      fu_status_table->divide.fj_Rj   = 1;
      fu_status_table->divide.fj_Rk   = 1;
      fu_status_table->divide.name    = divide;
      break;

    case 4: //integer
      fu_status_table->integer.busy   = !fu_status_table->integer.busy;
      fu_status_table->integer.op     = opcode;
      fu_status_table->integer.dest_Fi= rd;
      fu_status_table->integer.s1_Fj  = rs;
      fu_status_table->integer.s2_Fk  = rt;
      fu_status_table->integer.fu_Qj  = 1;
      fu_status_table->integer.fu_Qk  = 1;
      fu_status_table->integer.fj_Rj  = 1;
      fu_status_table->integer.fj_Rk  = 1;
      fu_status_table->integer.name   = integer;
      break;

    default: // vazio
      printf("Erro na inserção no FU\n");
    }

}

bool getBusy(functional_unit_status_table_t *fu_status_table, unsigned int opcode){

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
      return fu_status_table->integer.busy;
    
    default: // vazio
      printf("Erro em getBusy da FU\n");
      return false;
    }
}

void init_funcional_unit_status_table(functional_unit_status_table_t *fu_status_table){
  fu_status_table->add.time      = -1;
  fu_status_table->add.name      = add;
  fu_status_table->add.busy      = false;
  fu_status_table->add.op        = 0;
  fu_status_table->add.dest_Fi   = 0;
  fu_status_table->add.s1_Fj     = 0;
  fu_status_table->add.s2_Fk     = 0;
  fu_status_table->add.fu_Qj     = empty;
  fu_status_table->add.fu_Qk     = empty;
  fu_status_table->add.fj_Rj     = true;
  fu_status_table->add.fj_Rk     = true;

  fu_status_table->mult1.time    = -1;
  fu_status_table->mult1.name    = mult1;
  fu_status_table->mult1.busy    = false;
  fu_status_table->mult1.op      = 0;
  fu_status_table->mult1.dest_Fi = 0;
  fu_status_table->mult1.s1_Fj   = 0;
  fu_status_table->mult1.s2_Fk   = 0;
  fu_status_table->mult1.fu_Qj   = empty; 
  fu_status_table->mult1.fu_Qk   = empty; 
  fu_status_table->mult1.fj_Rj   = true;
  fu_status_table->mult1.fj_Rk   = true;

  fu_status_table->mult2.time    = -1;
  fu_status_table->mult2.name    = mult2;
  fu_status_table->mult2.busy    = false;
  fu_status_table->mult2.op      = 0;
  fu_status_table->mult2.dest_Fi = 0;
  fu_status_table->mult2.s1_Fj   = 0;
  fu_status_table->mult2.s2_Fk   = 0;
  fu_status_table->mult2.fu_Qj   = empty; 
  fu_status_table->mult2.fu_Qk   = empty; 
  fu_status_table->mult2.fj_Rj   = true;
  fu_status_table->mult2.fj_Rk   = true;

  fu_status_table->divide.time   = -1;
  fu_status_table->divide.name   = divide;
  fu_status_table->divide.busy   = false;
  fu_status_table->divide.op     = 0;
  fu_status_table->divide.dest_Fi= 0;
  fu_status_table->divide.s1_Fj  = 0;
  fu_status_table->divide.s2_Fk  = 0;
  fu_status_table->divide.fu_Qj  = empty; 
  fu_status_table->divide.fu_Qk  = empty; 
  fu_status_table->divide.fj_Rj  = true;
  fu_status_table->divide.fj_Rk  = true;

  fu_status_table->integer.time    = -1;
  fu_status_table->integer.name    = integer;
  fu_status_table->integer.busy    = false;
  fu_status_table->integer.op      = 0;
  fu_status_table->integer.dest_Fi = 0;
  fu_status_table->integer.s1_Fj   = 0;
  fu_status_table->integer.s2_Fk   = 0;
  fu_status_table->integer.fu_Qj   = empty;
  fu_status_table->integer.fu_Qk   = empty; 
  fu_status_table->integer.fj_Rj   = true;
  fu_status_table->integer.fj_Rk   = true;
}

#endif
