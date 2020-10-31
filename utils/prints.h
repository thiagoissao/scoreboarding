#include <stdbool.h>
#include <stdio.h>
#include "../unidades_funcionais/instruction_status.h"
#include "../conversor.h"
#include "../tipos_instrucoes/instructions_op.h"
#include "../tipos_instrucoes/registers.h"
#include "../tipos_instrucoes/i_types.h"

bool isR(unsigned int instr)
{
  unsigned int opcode = desconverteOp(instr);
  return opcode == R;
}

void print_instructions(instruction_status_t *table, int size)
{
  printf("\n1) STATUS DAS INSTRUÇÕES\n");
  printf("\t\tEmissão | Leitura dos Operandos | Execução | Escrita dos Resultados\n");
  for (int i = 0; i < size; i++)
  {
    printf("%i\t%i\t\t%i\t\t    %i\t\t%i\n", table[i].instruction, table[i].issue, table[i].readOperand, table[i].execComp, table[i].writeResult);
  }
}

void print_instructions_complete(instruction_status_t *table, int size)
{
  printf("\n1) STATUS DAS INSTRUÇÕES\n");
  printf("\t\t      Emissão | Leitura dos Operandos | Execução | Escrita dos Resultados\n");
  for (int i = 0; i < size; i++)
  {
    if (isR(table[i].instruction))
    {
      printf("%s, $%s, $%s, $%s\t  %i\t\t%i\t\t    %i\t\t%i\n",
             opcodeToString(desconverteFunct(table[i].instruction)),
             registerToString(desconverteRd(table[i].instruction)),
             registerToString(desconverteRs(table[i].instruction)),
             registerToString(desconverteRt(table[i].instruction)),
             table[i].issue,
             table[i].readOperand,
             table[i].execComp,
             table[i].writeResult);
    }
    else
    {
      printf("%s, $%s, $%s, %i\t  %i\t\t%i\t\t    %i\t\t%i\n",
             opcodeToString(desconverteOp(table[i].instruction)),
             registerToString(desconverteRs(table[i].instruction)),
             registerToString(desconverteRt(table[i].instruction)),
             desconverteImmediate(table[i].instruction),
             table[i].issue,
             table[i].readOperand,
             table[i].execComp,
             table[i].writeResult);
    }
  }
}
