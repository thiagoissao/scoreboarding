#ifndef REGISTER_DATABASE_H
#define REGISTER_DATABASE_H

#include <stdio.h>
#include "../types/registers.h"

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

int getRegisterValueFromDatabase(register_database_t *database, unsigned int register_number)
{
  switch (register_number)
  {
  case zero_dec:
    return database->zero;
  case at_dec:
    return database->at;

  case v0_dec:
    return database->v0;

  case v1_dec:
    return database->v1;

  case a0_dec:
    return database->a0;

  case a1_dec:
    return database->a1;

  case a2_dec:
    return database->a2;

  case a3_dec:
    return database->a3;

  case t0_dec:
    return database->t0;

  case t1_dec:
    return database->t1;

  case t2_dec:
    return database->t2;

  case t3_dec:
    return database->t3;

  case t4_dec:
    return database->t4;

  case t5_dec:
    return database->t5;

  case t6_dec:
    return database->t6;

  case t7_dec:
    return database->t7;

  case s0_dec:
    return database->s0;

  case s1_dec:
    return database->s1;

  case s2_dec:
    return database->s2;

  case s3_dec:
    return database->s3;

  case s4_dec:
    return database->s4;

  case s5_dec:
    return database->s5;

  case s6_dec:
    return database->s6;

  case s7_dec:
    return database->s7;

  case t8_dec:
    return database->t8;

  case t9_dec:
    return database->t9;

  case k0_dec:
    return database->k0;

  case k1_dec:
    return database->k1;

  case gp_dec:
    return database->gp;

  case sp_dec:
    return database->sp;

  case fp_dec:
    return database->fp;

  case ra_dec:
    return database->ra;

  default:
    printf("Erro ao inserir na tabela no banco de registradores!");
    break;
  }
}

void setValueToRegisterDatabase(register_database_t *database, unsigned int register_number, int value)
{
  switch (register_number)
  {
  case zero_dec:
  {
    database->zero = value;
    break;
  }

  case at_dec:
    database->at = value;
    break;

  case v0_dec:
    database->v0 = value;
    break;

  case v1_dec:
    database->v1 = value;
    break;

  case a0_dec:
    database->a0 = value;
    break;

  case a1_dec:
    database->a1 = value;
    break;

  case a2_dec:
    database->a2 = value;
    break;

  case a3_dec:
    database->a3 = value;
    break;

  case t0_dec:
    database->t0 = value;
    break;

  case t1_dec:
    database->t1 = value;
    break;

  case t2_dec:
    database->t2 = value;
    break;

  case t3_dec:
    database->t3 = value;
    break;

  case t4_dec:
    database->t4 = value;
    break;

  case t5_dec:
    database->t5 = value;
    break;

  case t6_dec:
    database->t6 = value;
    break;

  case t7_dec:
    database->t7 = value;
    break;

  case s0_dec:
    database->s0 = value;
    break;

  case s1_dec:
    database->s1 = value;
    break;

  case s2_dec:
    database->s2 = value;
    break;

  case s3_dec:
    database->s3 = value;
    break;

  case s4_dec:
    database->s4 = value;
    break;

  case s5_dec:
    database->s5 = value;
    break;

  case s6_dec:
    database->s6 = value;
    break;

  case s7_dec:
    database->s7 = value;
    break;

  case t8_dec:
    database->t8 = value;
    break;

  case t9_dec:
    database->t9 = value;
    break;

  case k0_dec:
    database->k0 = value;
    break;

  case k1_dec:
    database->k1 = value;
    break;

  case gp_dec:
    database->gp = value;
    break;

  case sp_dec:
    database->sp = value;
    break;

  case fp_dec:
    database->fp = value;
    break;

  case ra_dec:
    database->ra = value;
    break;

  default:
    printf("Erro ao inserir na tabela no banco de registradores!");
    break;
  }
}
#endif
