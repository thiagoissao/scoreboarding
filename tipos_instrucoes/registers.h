#include <stdio.h>
#include <string.h>

unsigned int getRegisterDecimal(char *reg)
{
  if (strcmp(reg, "F0") == 0)
    return 0;

  if (strcmp(reg, "F2") == 0)
    return 2;

  if (strcmp(reg, "F3") == 0)
    return 3;

  if (strcmp(reg, "F4") == 0)
    return 4;

  if (strcmp(reg, "F5") == 0)
    return 5;

  if (strcmp(reg, "F6") == 0)
    return 6;

  if (strcmp(reg, "F7") == 0)
    return 7;

  if (strcmp(reg, "F8") == 0)
    return 8;

  if (strcmp(reg, "F9") == 0)
    return 9;

  if (strcmp(reg, "F10") == 0)
    return 10;

  printf("Erro na leitura do registrador %s\n", reg);
  return 0;
}
