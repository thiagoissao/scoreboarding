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
  functional_unit_status_t add;
  functional_unit_status_t addi;
  functional_unit_status_t and;
  functional_unit_status_t andi;
  functional_unit_status_t or ;
  functional_unit_status_t ori;
  functional_unit_status_t slt;
  functional_unit_status_t sub;
  functional_unit_status_t mult;
  functional_unit_status_t div;
  functional_unit_status_t li;
  functional_unit_status_t move;
} functional_unit_status_table_t;

void setBusy(functional_unit_status_table_t *fu_status_table, unsigned int opcode){
  switch (opcode)
  {
  case 32: // add
    fu_status_table->add.busy = !fu_status_table->add.busy;
    break;
  case 8: //addi
    fu_status_table->addi.busy = !fu_status_table->addi.busy;
    break;
  case 36: //and
    fu_status_table->and.busy = !fu_status_table->and.busy;
    break;
  case 12: //andi
    fu_status_table->andi.busy = !fu_status_table->andi.busy;
    break;
  case 37: //or
    fu_status_table->or.busy = !fu_status_table->or.busy;
    break;
  case 13: //ori
    fu_status_table->ori.busy = !fu_status_table->ori.busy;
    break;
  case 42: //slt
    fu_status_table->slt.busy = !fu_status_table->slt.busy;
    break;
  case 34: //sub
    fu_status_table->sub.busy = !fu_status_table->sub.busy;
    break;
  case 24: //mult
    fu_status_table->mult.busy = !fu_status_table->mult.busy;
    break;
  case 1: //LI -> arrumar
    fu_status_table->li.busy = !fu_status_table->li.busy;
    break;
  case 2: //mov -> arrumar
    fu_status_table->move.busy = !fu_status_table->move.busy;
    break;
  default:
    printf("Erro mudança no Busy correspondente\n");
  }
}

bool getBusy(functional_unit_status_table_t *fu_status_table, unsigned int opcode){
  switch (opcode)
  {
  case 32: // add
    return fu_status_table->add.busy;
  case 8: //addi
    return fu_status_table->addi.busy;
  case 36: //and
    return fu_status_table->and.busy;
  case 12: //andi
    return fu_status_table->andi.busy;
  case 37: //or
    return fu_status_table->or.busy;
  case 13: //ori
    return fu_status_table->ori.busy;
  case 42: //slt
    return fu_status_table->slt.busy;
  case 34: //sub
    return fu_status_table->sub.busy;
  case 24: //mult
    return fu_status_table->mult.busy;
  case 1: //LI -> arrumar
    return fu_status_table->li.busy;
  case 2: //mov -> arrumar
    return fu_status_table->move.busy;
  default:
    printf("Erro na leitura do FU correspondente\n");
    return false;
  }
}

void init_funcional_unit_status_table(functional_unit_status_table_t *fu_status_table){
  fu_status_table->add.time     = -1;
  fu_status_table->add.name     = 2;
  fu_status_table->add.busy     = false;
  fu_status_table->add.op       = 0;
  fu_status_table->add.dest_Fi  = 0;
  fu_status_table->add.s1_Fj    = 0;
  fu_status_table->add.s2_Fk    = 0;
  fu_status_table->add.fu_Qj    = 0; // deveria ter um sem nada
  fu_status_table->add.fu_Qk    = 0; // deveria ter um sem nada
  fu_status_table->add.fj_Rj    = false;
  fu_status_table->add.fj_Rk    = false;

  fu_status_table->addi.time    = -1;
  fu_status_table->addi.name    = 2;
  fu_status_table->addi.busy    = false;
  fu_status_table->addi.op      = 0;
  fu_status_table->addi.dest_Fi = 0;
  fu_status_table->addi.s1_Fj   = 0;
  fu_status_table->addi.s2_Fk   = 0;
  fu_status_table->addi.fu_Qj   = 0; // deveria ter um sem nada
  fu_status_table->addi.fu_Qk   = 0; // deveria ter um sem nada
  fu_status_table->addi.fj_Rj   = false;
  fu_status_table->addi.fj_Rk   = false;

  fu_status_table->and.time     = -1;
  fu_status_table->and.name     = 2;
  fu_status_table->and.busy     = false;
  fu_status_table->and.op       = 0;
  fu_status_table->and.dest_Fi  = 0;
  fu_status_table->and.s1_Fj    = 0;
  fu_status_table->and.s2_Fk    = 0;
  fu_status_table->and.fu_Qj    = 0; // deveria ter um sem nada
  fu_status_table->and.fu_Qk    = 0; // deveria ter um sem nada
  fu_status_table->and.fj_Rj    = false;
  fu_status_table->and.fj_Rk    = false;

  fu_status_table->andi.time    = -1;
  fu_status_table->andi.name    = 2;
  fu_status_table->andi.busy    = false;
  fu_status_table->andi.op      = 0;
  fu_status_table->andi.dest_Fi = 0;
  fu_status_table->andi.s1_Fj   = 0;
  fu_status_table->andi.s2_Fk   = 0;
  fu_status_table->andi.fu_Qj   = 0; // deveria ter um sem nada
  fu_status_table->andi.fu_Qk   = 0; // deveria ter um sem nada
  fu_status_table->andi.fj_Rj   = false;
  fu_status_table->andi.fj_Rk   = false;

  fu_status_table->or.time      = -1;
  fu_status_table->or.name      = 2;
  fu_status_table->or.busy      = false;
  fu_status_table->or.op        = 0;
  fu_status_table->or.dest_Fi   = 0;
  fu_status_table->or.s1_Fj     = 0;
  fu_status_table->or.s2_Fk     = 0;
  fu_status_table->or.fu_Qj     = 0; // deveria ter um sem nada
  fu_status_table->or.fu_Qk     = 0; // deveria ter um sem nada
  fu_status_table->or.fj_Rj     = false;
  fu_status_table->or.fj_Rk     = false;

  fu_status_table->ori.time     = -1;
  fu_status_table->ori.name     = 2;
  fu_status_table->ori.busy     = false;
  fu_status_table->ori.op       = 0;
  fu_status_table->ori.dest_Fi  = 0;
  fu_status_table->ori.s1_Fj    = 0;
  fu_status_table->ori.s2_Fk    = 0;
  fu_status_table->ori.fu_Qj    = 0; // deveria ter um sem nada
  fu_status_table->ori.fu_Qk    = 0; // deveria ter um sem nada
  fu_status_table->ori.fj_Rj    = false;
  fu_status_table->ori.fj_Rk    = false;

  fu_status_table->slt.time     = -1;
  fu_status_table->slt.name     = 2;
  fu_status_table->slt.busy     = false;
  fu_status_table->slt.op       = 0;
  fu_status_table->slt.dest_Fi  = 0;
  fu_status_table->slt.s1_Fj    = 0;
  fu_status_table->slt.s2_Fk    = 0;
  fu_status_table->slt.fu_Qj    = 0; // deveria ter um sem nada
  fu_status_table->slt.fu_Qk    = 0; // deveria ter um sem nada
  fu_status_table->slt.fj_Rj    = false;
  fu_status_table->slt.fj_Rk    = false;

  fu_status_table->sub.time     = -1;
  fu_status_table->sub.name     = 2;
  fu_status_table->sub.busy     = false;
  fu_status_table->sub.op       = 0;
  fu_status_table->sub.dest_Fi  = 0;
  fu_status_table->sub.s1_Fj    = 0;
  fu_status_table->sub.s2_Fk    = 0;
  fu_status_table->sub.fu_Qj    = 0; // deveria ter um sem nada
  fu_status_table->sub.fu_Qk    = 0; // deveria ter um sem nada
  fu_status_table->sub.fj_Rj    = false;
  fu_status_table->sub.fj_Rk    = false;

  fu_status_table->mult.time    = -1;
  fu_status_table->mult.name    = 2;
  fu_status_table->mult.busy    = false;
  fu_status_table->mult.op      = 0;
  fu_status_table->mult.dest_Fi = 0;
  fu_status_table->mult.s1_Fj   = 0;
  fu_status_table->mult.s2_Fk   = 0;
  fu_status_table->mult.fu_Qj   = 0; // deveria ter um sem nada
  fu_status_table->mult.fu_Qk   = 0; // deveria ter um sem nada
  fu_status_table->mult.fj_Rj   = false;
  fu_status_table->mult.fj_Rk   = false;

  fu_status_table->div.time     = -1;
  fu_status_table->div.name     = 2;
  fu_status_table->div.busy     = false;
  fu_status_table->div.op       = 0;
  fu_status_table->div.dest_Fi  = 0;
  fu_status_table->div.s1_Fj    = 0;
  fu_status_table->div.s2_Fk    = 0;
  fu_status_table->div.fu_Qj    = 0; // deveria ter um sem nada
  fu_status_table->div.fu_Qk    = 0; // deveria ter um sem nada
  fu_status_table->div.fj_Rj    = false;
  fu_status_table->div.fj_Rk    = false;

  fu_status_table->li.time      = -1;
  fu_status_table->li.name      = 2;
  fu_status_table->li.busy      = false;
  fu_status_table->li.op        = 0;
  fu_status_table->li.dest_Fi   = 0;
  fu_status_table->li.s1_Fj     = 0;
  fu_status_table->li.s2_Fk     = 0;
  fu_status_table->li.fu_Qj     = 0; // deveria ter um sem nada
  fu_status_table->li.fu_Qk     = 0; // deveria ter um sem nada
  fu_status_table->li.fj_Rj     = false;
  fu_status_table->li.fj_Rk     = false;

  fu_status_table->move.time     = -1;
  fu_status_table->move.name     = 2;
  fu_status_table->move.busy     = false;
  fu_status_table->move.op       = 0;
  fu_status_table->move.dest_Fi  = 0;
  fu_status_table->move.s1_Fj    = 0;
  fu_status_table->move.s2_Fk    = 0;
  fu_status_table->move.fu_Qj    = 0; // deveria ter um sem nada
  fu_status_table->move.fu_Qk    = 0; // deveria ter um sem nada
  fu_status_table->move.fj_Rj    = false;
  fu_status_table->move.fj_Rk    = false;

}

#endif
