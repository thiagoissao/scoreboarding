#ifndef REGISTER_DATABASE_H
#define REGISTER_DATABASE_H

#include <stdio.h>
#include "../tipos_instrucoes/registers.h"

#define initialValue 0

typedef struct register_database
{
  int zero;
  int at;
  int v0;
  int v1;
  int a0;
  int a1;
  int a2;
  int a3;
  int t0;
  int t1;
  int t2;
  int t3;
  int t4;
  int t5;
  int t6;
  int t7;
  int s0;
  int s1;
  int s2;
  int s3;
  int s4;
  int s5;
  int s6;
  int s7;
  int t8;
  int t9;
  int k0;
  int k1;
  int gp;
  int sp;
  int fp;
  int ra;
} register_database_t;

void init_register_database(register_database_t *reg_databae)
{
  reg_databae->zero = initialValue;
  reg_databae->at = initialValue;
  reg_databae->v0 = initialValue;
  reg_databae->v1 = initialValue;
  reg_databae->a0 = initialValue;
  reg_databae->a1 = initialValue;
  reg_databae->a2 = initialValue;
  reg_databae->a3 = initialValue;
  reg_databae->t0 = initialValue;
  reg_databae->t1 = initialValue;
  reg_databae->t2 = initialValue;
  reg_databae->t3 = initialValue;
  reg_databae->t4 = initialValue;
  reg_databae->t5 = initialValue;
  reg_databae->t6 = initialValue;
  reg_databae->t7 = initialValue;
  reg_databae->s0 = initialValue;
  reg_databae->s1 = initialValue;
  reg_databae->s2 = initialValue;
  reg_databae->s3 = initialValue;
  reg_databae->s4 = initialValue;
  reg_databae->s5 = initialValue;
  reg_databae->s6 = initialValue;
  reg_databae->s7 = initialValue;
  reg_databae->t8 = initialValue;
  reg_databae->t9 = initialValue;
  reg_databae->k0 = initialValue;
  reg_databae->k1 = initialValue;
  reg_databae->gp = initialValue;
  reg_databae->sp = initialValue;
  reg_databae->fp = initialValue;
  reg_databae->ra = initialValue;
}

void setRegisterDatabase(register_database_t *reg_database, unsigned int register_number, int value)
{
  switch (register_number)
  {
  case zero_dec:
    reg_database->at = value;
    break;
  case at_dec:
    reg_database->at = value;
    break;
  case v0_dec:
    reg_database->v0 = value;
    break;
  case v1_dec:
    reg_database->v1 = value;
    break;
  case a0_dec:
    reg_database->a0 = value;
    break;
  case a1_dec:
    reg_database->a1 = value;
    break;
  case a2_dec:
    reg_database->a2 = value;
    break;
  case a3_dec:
    reg_database->a3 = value;
    break;
  case t0_dec:
    reg_database->t0 = value;
    break;
  case t1_dec:
    reg_database->t1 = value;
    break;
  case t2_dec:
    reg_database->t2 = value;
    break;
  case t3_dec:
    reg_database->t3 = value;
    break;
  case t4_dec:
    reg_database->t4 = value;
    break;
  case t5_dec:
    reg_database->t5 = value;
    break;
  case t6_dec:
    reg_database->t6 = value;
    break;
  case t7_dec:
    reg_database->t7 = value;
    break;
  case s0_dec:
    reg_database->s0 = value;
    break;
  case s1_dec:
    reg_database->s1 = value;
    break;
  case s2_dec:
    reg_database->s2 = value;
    break;
  case s3_dec:
    reg_database->s3 = value;
    break;
  case s4_dec:
    reg_database->s4 = value;
    break;
  case s5_dec:
    reg_database->s5 = value;
    break;
  case s6_dec:
    reg_database->s6 = value;
    break;
  case s7_dec:
    reg_database->s7 = value;
    break;
  case t8_dec:
    reg_database->t8 = value;
    break;
  case t9_dec:
    reg_database->t9 = value;
    break;
  case k0_dec:
    reg_database->k0 = value;
    break;
  case k1_dec:
    reg_database->k1 = value;
    break;
  case gp_dec:
    reg_database->gp = value;
    break;
  case sp_dec:
    reg_database->sp = value;
    break;
  case fp_dec:
    reg_database->fp = value;
    break;
  case ra_dec:
    reg_database->ra = value;
    break;

  default:
    printf("Erro ao inserir na tabela no banco de registradores!");
    break;
  }
}
#endif
