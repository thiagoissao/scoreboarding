#include <stdio.h>
#include <string.h>

int getRegisterDecimal(char *opcode)
{
  if (strcmp(opcode, "$zero"))
    return 0;

  if (strcmp(opcode, "$at"))
    return 1;

  if (strcmp(opcode, "$v0"))
    return 2;

  if (strcmp(opcode, "$v1"))
    return 3;

  if (strcmp(opcode, "$a0"))
    return 4;

  if (strcmp(opcode, "$a1"))
    return 5;

  if (strcmp(opcode, "$a2"))
    return 6;

  if (strcmp(opcode, "$a3"))
    return 7;

  if (strcmp(opcode, "$t0"))
    return 8;

  if (strcmp(opcode, "$t1"))
    return 9;

  if (strcmp(opcode, "$t2"))
    return 10;

  if (strcmp(opcode, "$t3"))
    return 11;

  if (strcmp(opcode, "$t4"))
    return 12;

  if (strcmp(opcode, "$t5"))
    return 13;

  if (strcmp(opcode, "$t6"))
    return 14;

  if (strcmp(opcode, "$t7"))
    return 15;

  if (strcmp(opcode, "$s0"))
    return 16;

  if (strcmp(opcode, "$s1"))
    return 17;

  if (strcmp(opcode, "$s2"))
    return 18;

  if (strcmp(opcode, "$s3"))
    return 19;

  if (strcmp(opcode, "$s4"))
    return 20;

  if (strcmp(opcode, "$s5"))
    return 21;

  if (strcmp(opcode, "$s6"))
    return 22;

  if (strcmp(opcode, "$s7"))
    return 23;

  if (strcmp(opcode, "$t8"))
    return 24;

  if (strcmp(opcode, "$t9"))
    return 25;

  if (strcmp(opcode, "$k0"))
    return 26;

  if (strcmp(opcode, "$k1"))
    return 27;

  if (strcmp(opcode, "$gp"))
    return 28;

  if (strcmp(opcode, "$sp"))
    return 29;

  if (strcmp(opcode, "$fp"))
    return 30;

  if (strcmp(opcode, "$ra"))
    return 31;

  return -1;
}
