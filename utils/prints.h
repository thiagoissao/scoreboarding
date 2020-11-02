#ifndef PRINTS_H
#define PRINTS_H

#include <stdbool.h>
#include <stdio.h>
#include "../unidades_funcionais/functional_unit_status.h"
#include "../unidades_funcionais/instruction_status.h"
#include "../conversor.h"
#include "../tipos_instrucoes/instructions_op.h"
#include "../tipos_instrucoes/registers.h"
#include "../tipos_instrucoes/i_types.h"
#include "../utils/validations.h"

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
      printf("%4s $%3s,$%3s,$%3s\t  %1i\t\t %4i\t %12i\t %12i\n",
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
      printf("%4s $%3s,$%3s, %3i\t  %1i\t\t %4i\t %12i\t %12i\n",
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
  //printf("----------------------------------------------------------------------------------------\n");
}

void print_functional_unit(functional_unit_status_table_t *table)
{
  printf("\n2) STATUS DAS UNIDADES FUNCIONAIS\n");
  printf("UF\t|Busy\t| Op\t| Fi\t| Fj\t| Fk\t| Qj\t| Qk\t| Rj\t| Rk\n");
  printf("%i Mult1 | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4i \t| %4i \t| %4s \t| %4s\n",
         table->mult1.time,
         table->mult1.busy ? "Yes" : "No",
         opcodeToString(table->mult1.op),
         registerToString(table->mult1.dest_Fi),
         registerToString(table->mult1.s1_Fj),
         registerToString(table->mult1.s2_Fk),
         table->mult1.fu_Qj,
         table->mult1.fu_Qk,
         table->mult1.fj_Rj ? "Yes" : "No",
         table->mult1.fj_Rk ? "Yes" : "No");
  printf("%i Mult2 | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4i \t| %4i \t| %4s \t| %4s\n",
         table->mult2.time,
         table->mult2.busy ? "Yes" : "No",
         opcodeToString(table->mult2.op),
         registerToString(table->mult2.dest_Fi),
         registerToString(table->mult2.s1_Fj),
         registerToString(table->mult2.s2_Fk),
         table->mult2.fu_Qj,
         table->mult2.fu_Qk,
         table->mult2.fj_Rj ? "Yes" : "No",
         table->mult2.fj_Rk ? "Yes" : "No");
  printf("%i Add   | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4i \t| %4i \t| %4s \t| %4s\n",
         table->add.time,
         table->add.busy ? "Yes" : "No",
         opcodeToString(table->add.op),
         registerToString(table->add.dest_Fi),
         registerToString(table->add.s1_Fj),
         registerToString(table->add.s2_Fk),
         table->add.fu_Qj,
         table->add.fu_Qk,
         table->add.fj_Rj ? "Yes" : "No",
         table->add.fj_Rk ? "Yes" : "No"); 
  printf("%i Div   | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4i \t| %4i \t| %4s \t| %4s\n",
         table->divide.time,
         table->divide.busy ? "Yes" : "No",
         opcodeToString(table->divide.op),
         registerToString(table->divide.dest_Fi),
         registerToString(table->divide.s1_Fj),
         registerToString(table->divide.s2_Fk),
         table->divide.fu_Qj,
         table->divide.fu_Qk,
         table->divide.fj_Rj ? "Yes" : "No",
         table->divide.fj_Rk ? "Yes" : "No");
  printf("%i Log   | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4i \t| %4i \t| %4s \t| %4s\n",
         table->log.time,
         table->log.busy ? "Yes" : "No",
         opcodeToString(table->log.op),
         registerToString(table->log.dest_Fi),
         registerToString(table->log.s1_Fj),
         registerToString(table->log.s2_Fk),
         table->log.fu_Qj,
         table->log.fu_Qk,
         table->log.fj_Rj ? "Yes" : "No",
         table->log.fj_Rk ? "Yes" : "No");
}

#endif
