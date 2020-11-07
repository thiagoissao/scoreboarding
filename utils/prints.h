#ifndef PRINTS_H
#define PRINTS_H

#include <stdbool.h>
#include <stdio.h>
#include "../components/functional_unit_status.h"
#include "../components/instruction_status.h"
#include "../components/register_result_status.h"
#include "../components/register_database.h"
#include "../conversor.h"
#include "../types/instructions_op.h"
#include "../types/registers.h"
#include "../types/i_types.h"
#include "../utils/validations.h"
#include "../components/units.h"
#include "../config/config.h"

void print_config(config_t *config, int size)
{
       printf("\n-------------- CONFIGURATIONS --------------------\n");
       for (int i = 0; i < size; i++)
       {
              printf("Instrução: %s => %i ciclos\n", opcodeToString(config[i].opcode), config[i].value);
       }
}

void print_instructions(instruction_status_t *table, int size)
{
       int i;
       printf("\n1) STATUS DAS INSTRUÇÕES\n");
       printf("\t\tEmissão | Leitura dos Operandos | Execução | Escrita dos Resultados\n");
       for (i = 0; i < size; i++)
       {
              printf("%i\t%i\t\t%i\t\t    %i\t\t%i\n", table[i].instruction, table[i].issue, table[i].readOperand, table[i].execComp, table[i].writeResult);
       }
}

void print_instructions_complete(instruction_status_t *table, int size)
{
       int i;
       printf("\n1) STATUS DAS INSTRUÇÕES\n");
       printf("\t\t      Emissão | Leitura dos Operandos | Execução | Escrita dos Resultados\n");
       for (i = 0; i < size; i++)
       {
              if (isR(table[i].instruction))
              {
                     printf("%4s $%s, $%s, $%s\t  %1i\t\t %4i\t %12i\t %12i\n",
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
                     printf("%4s $%s, $%s, %3i\t  %1i\t\t %4i\t %12i\t %12i\n",
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
       printf("%i Mult1 | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %s \t| %s \t| %4s \t| %4s\n",
              table->mult1.time,
              table->mult1.busy ? "Yes" : "No",
              opcodeToString(table->mult1.op),
              registerToString(table->mult1.dest_Fi),
              registerToString(table->mult1.s1_Fj),
              registerToString(table->mult1.s2_Fk),
              typeOpToString(table->mult1.fu_Qj),
              typeOpToString(table->mult1.fu_Qk),
              table->mult1.busy ? table->mult1.fj_Rj ? "Yes" : "No" : "",
              table->mult1.busy ? table->mult1.fj_Rk ? "Yes" : "No" : "");
       printf("%i Mult2 | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %s \t| %s \t| %4s \t| %4s\n",
              table->mult2.time,
              table->mult2.busy ? "Yes" : "No",
              opcodeToString(table->mult2.op),
              registerToString(table->mult2.dest_Fi),
              registerToString(table->mult2.s1_Fj),
              registerToString(table->mult2.s2_Fk),
              typeOpToString(table->mult2.fu_Qj),
              typeOpToString(table->mult2.fu_Qk),
              table->mult2.busy ? table->mult2.fj_Rj ? "Yes" : "No" : "",
              table->mult2.busy ? table->mult2.fj_Rk ? "Yes" : "No" : "");
       printf("%i Add   | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %s \t| %s \t| %4s \t| %4s\n",
              table->add.time,
              table->add.busy ? "Yes" : "No",
              opcodeToString(table->add.op),
              registerToString(table->add.dest_Fi),
              registerToString(table->add.s1_Fj),
              registerToString(table->add.s2_Fk),
              typeOpToString(table->add.fu_Qj),
              typeOpToString(table->add.fu_Qk),
              table->add.busy ? table->add.fj_Rj ? "Yes" : "No" : "",
              table->add.busy ? table->add.fj_Rk ? "Yes" : "No" : "");
       printf("%i Div   | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %s \t| %s \t| %4s \t| %4s\n",
              table->divide.time,
              table->divide.busy ? "Yes" : "No",
              opcodeToString(table->divide.op),
              registerToString(table->divide.dest_Fi),
              registerToString(table->divide.s1_Fj),
              registerToString(table->divide.s2_Fk),
              typeOpToString(table->divide.fu_Qj),
              typeOpToString(table->divide.fu_Qk),
              table->divide.busy ? table->divide.fj_Rj ? "Yes" : "No" : "",
              table->divide.busy ? table->divide.fj_Rk ? "Yes" : "No" : "");
       printf("%i Log   | %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %s \t| %s \t| %4s \t| %4s\n",
              table->log.time,
              table->log.busy ? "Yes" : "No",
              opcodeToString(table->log.op),
              registerToString(table->log.dest_Fi),
              registerToString(table->log.s1_Fj),
              registerToString(table->log.s2_Fk),
              typeOpToString(table->log.fu_Qj),
              typeOpToString(table->log.fu_Qk),
              table->log.busy ? table->log.fj_Rj ? "Yes" : "No" : "",
              table->log.busy ? table->log.fj_Rk ? "Yes" : "No" : "");
}

void print_register_result(register_result_status_table_t *table)
{
       char *format = "%s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t\n";
       printf("\n3) STATUS DOS REGISTRADORES\n");
       printf(format,
              zero_reg,
              at_reg,
              v0_reg,
              v1_reg,
              a0_reg,
              a1_reg,
              a2_reg,
              a3_reg,
              t0_reg,
              t1_reg,
              t2_reg,
              t3_reg,
              t4_reg,
              t5_reg,
              t6_reg,
              t7_reg,
              s0_reg,
              s1_reg,
              s2_reg,
              s3_reg,
              s4_reg,
              s5_reg,
              s6_reg,
              s7_reg,
              t8_reg,
              t9_reg,
              k0_reg,
              k1_reg,
              gp_reg,
              sp_reg,
              fp_reg,
              ra_reg);
       printf("\n");
       printf(format,
              typeOpToString(table->zero),
              typeOpToString(table->at),
              typeOpToString(table->v0),
              typeOpToString(table->v1),
              typeOpToString(table->a0),
              typeOpToString(table->a1),
              typeOpToString(table->a2),
              typeOpToString(table->a3),
              typeOpToString(table->t0),
              typeOpToString(table->t1),
              typeOpToString(table->t2),
              typeOpToString(table->t3),
              typeOpToString(table->t4),
              typeOpToString(table->t5),
              typeOpToString(table->t6),
              typeOpToString(table->t7),
              typeOpToString(table->s0),
              typeOpToString(table->s1),
              typeOpToString(table->s2),
              typeOpToString(table->s3),
              typeOpToString(table->s4),
              typeOpToString(table->s5),
              typeOpToString(table->s6),
              typeOpToString(table->s7),
              typeOpToString(table->t8),
              typeOpToString(table->t9),
              typeOpToString(table->k0),
              typeOpToString(table->k1),
              typeOpToString(table->gp),
              typeOpToString(table->sp),
              typeOpToString(table->fp),
              typeOpToString(table->ra));
}

void print_register_database(register_database_t *table)
{
       char *formatRegName = "%s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t| %s\t\n";
       char *format = "%i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t| %i\t\n";
       printf("\n4) BANCO DE REGISTRADORES\n");
       printf(formatRegName,
              zero_reg,
              at_reg,
              v0_reg,
              v1_reg,
              a0_reg,
              a1_reg,
              a2_reg,
              a3_reg,
              t0_reg,
              t1_reg,
              t2_reg,
              t3_reg,
              t4_reg,
              t5_reg,
              t6_reg,
              t7_reg,
              s0_reg,
              s1_reg,
              s2_reg,
              s3_reg,
              s4_reg,
              s5_reg,
              s6_reg,
              s7_reg,
              t8_reg,
              t9_reg,
              k0_reg,
              k1_reg,
              gp_reg,
              sp_reg,
              fp_reg,
              ra_reg);
       printf("\n");
       printf(format,
              table->zero,
              table->at,
              table->v0,
              table->v1,
              table->a0,
              table->a1,
              table->a2,
              table->a3,
              table->t0,
              table->t1,
              table->t2,
              table->t3,
              table->t4,
              table->t5,
              table->t6,
              table->t7,
              table->s0,
              table->s1,
              table->s2,
              table->s3,
              table->s4,
              table->s5,
              table->s6,
              table->s7,
              table->t8,
              table->t9,
              table->k0,
              table->k1,
              table->gp,
              table->sp,
              table->fp,
              table->ra);
}

#endif
