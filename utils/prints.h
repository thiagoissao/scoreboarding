#include <stdio.h>
#include "../unidades_funcionais/instruction_status.h"

void print_instructions(instruction_status_t *table, int numberOfInstructions)
{
  printf("\n1) STATUS DAS INSTRUÇÕES\n");
  printf("\t\tEmissão | Leitura dos Operandos | Execução | Escrita dos Resultados\n");
  for (int i = 0; i < numberOfInstructions; i++)
  {
    printf("%i\t\t\t\n", table[i].instruction);
  }
}
