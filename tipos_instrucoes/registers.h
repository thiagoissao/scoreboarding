#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdio.h>
#include <string.h>

#define zero_reg "zero"
#define at_reg "at"
#define v0_reg "v0"
#define v1_reg "v1"
#define a0_reg "a0"
#define a1_reg "a1"
#define a2_reg "a2"
#define a3_reg "a3"
#define t0_reg "t0"
#define t1_reg "t1"
#define t2_reg "t2"
#define t3_reg "t3"
#define t4_reg "t4"
#define t5_reg "t5"
#define t6_reg "t6"
#define t7_reg "t7"
#define s0_reg "s0"
#define s1_reg "s1"
#define s2_reg "s2"
#define s3_reg "s3"
#define s4_reg "s4"
#define s5_reg "s5"
#define s6_reg "s6"
#define s7_reg "s7"
#define t8_reg "t8"
#define t9_reg "t9"
#define k0_reg "k0"
#define k1_reg "k1"
#define gp_reg "gp"
#define sp_reg "sp"
#define fp_reg "fp"
#define ra_reg "ra"

#define zero_dec 0
#define at_dec 1
#define v0_dec 2
#define v1_dec 3
#define a0_dec 4
#define a1_dec 5
#define a2_dec 6
#define a3_dec 7
#define t0_dec 8
#define t1_dec 9
#define t2_dec 10
#define t3_dec 11
#define t4_dec 12
#define t5_dec 13
#define t6_dec 14
#define t7_dec 15
#define s0_dec 16
#define s1_dec 17
#define s2_dec 18
#define s3_dec 19
#define s4_dec 20
#define s5_dec 21
#define s6_dec 22
#define s7_dec 23
#define t8_dec 24
#define t9_dec 25
#define k0_dec 26
#define k1_dec 27
#define gp_dec 28
#define sp_dec 29
#define fp_dec 30
#define ra_dec 31

char *registerToString(unsigned int reg)
{
  switch (reg)
  {
  case zero_dec:
    return zero_reg;
  case at_dec:
    return at_reg;
  case v0_dec:
    return v0_reg;
  case v1_dec:
    return v1_reg;
  case a0_dec:
    return a0_reg;
  case a1_dec:
    return a1_reg;
  case a2_dec:
    return a2_reg;
  case a3_dec:
    return a3_reg;
  case t0_dec:
    return t0_reg;
  case t1_dec:
    return t1_reg;
  case t2_dec:
    return t2_reg;
  case t3_dec:
    return t3_reg;
  case t4_dec:
    return t4_reg;
  case t5_dec:
    return t5_reg;
  case t6_dec:
    return t6_reg;
  case t7_dec:
    return t7_reg;
  case s0_dec:
    return s0_reg;
  case s1_dec:
    return s1_reg;
  case s2_dec:
    return s2_reg;
  case s3_dec:
    return s3_reg;
  case s4_dec:
    return s4_reg;
  case s5_dec:
    return s5_reg;
  case s6_dec:
    return s6_reg;
  case s7_dec:
    return s7_reg;
  case t8_dec:
    return t8_reg;
  case t9_dec:
    return t9_reg;
  case k0_dec:
    return k0_reg;
  case k1_dec:
    return k1_reg;
  case gp_dec:
    return gp_reg;
  case sp_dec:
    return sp_reg;
  case fp_dec:
    return fp_reg;
  case ra_dec:
    return ra_reg;
  default:
    return "";
  }
}

unsigned int getRegisterDecimal(char *reg)
{
  if (strcmp(reg, "$zero") == 0)
    return 0;

  if (strcmp(reg, "$at") == 0)
    return 1;

  if (strcmp(reg, "$v0") == 0)
    return 2;

  if (strcmp(reg, "$v1") == 0)
    return 3;

  if (strcmp(reg, "$a0") == 0)
    return 4;

  if (strcmp(reg, "$a1") == 0)
    return 5;

  if (strcmp(reg, "$a2") == 0)
    return 6;

  if (strcmp(reg, "$a3") == 0)
    return 7;

  if (strcmp(reg, "$t0") == 0)
    return 8;

  if (strcmp(reg, "$t1") == 0)
    return 9;

  if (strcmp(reg, "$t2") == 0)
    return 10;

  if (strcmp(reg, "$t3") == 0)
    return 11;

  if (strcmp(reg, "$t4") == 0)
    return 12;

  if (strcmp(reg, "$t5") == 0)
    return 13;

  if (strcmp(reg, "$t6") == 0)
    return 14;

  if (strcmp(reg, "$t7") == 0)
    return 15;

  if (strcmp(reg, "$s0") == 0)
    return 16;

  if (strcmp(reg, "$s1") == 0)
    return 17;

  if (strcmp(reg, "$s2") == 0)
    return 18;

  if (strcmp(reg, "$s3") == 0)
    return 19;

  if (strcmp(reg, "$s4") == 0)
    return 20;

  if (strcmp(reg, "$s5") == 0)
    return 21;

  if (strcmp(reg, "$s6") == 0)
    return 22;

  if (strcmp(reg, "$s7") == 0)
    return 23;

  if (strcmp(reg, "$t8") == 0)
    return 24;

  if (strcmp(reg, "$t9") == 0)
    return 25;

  if (strcmp(reg, "$k0") == 0)
    return 26;

  if (strcmp(reg, "$k1") == 0)
    return 27;

  if (strcmp(reg, "$gp") == 0)
    return 28;

  if (strcmp(reg, "$sp") == 0)
    return 29;

  if (strcmp(reg, "$fp") == 0)
    return 30;

  if (strcmp(reg, "$ra") == 0)
    return 31;

  printf("Erro na leitura do registrador %s\n", reg);
  return -1;
}
#endif
