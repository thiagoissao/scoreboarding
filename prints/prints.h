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
#include "../utils/utils.h"
#include "../components/units.h"
#include "../config/config.h"

void print_config(config_t *config, int size, char *path)
{
       FILE *archive = fopen(path, "a");
       if (archive == NULL){
              printf("Erro ao escrever no artigo!\n");
              exit(1);
       }
       fprintf(archive, "\n-------------- configurations --------------------\n");
       for (int i = 0; i < size; i++)
       {
              fprintf(archive, "Instrução: %s => %i ciclos\n", opcodeToString(config[i].opcode), config[i].value);
       }
       fprintf(archive, "\n");
       fclose(archive);
}

void print_instruction_set(unsigned int *instructions, int size, char *path)
{
       FILE *archive = fopen(path, "a");
       if (archive == NULL){
              printf("Erro ao escrever no artigo!\n");
              exit(1);
       }

       fprintf(archive,"\n----------------------- conjunto de instrucoes--------------------------\n");
       for (int i = 0; i < size; i++)
       {
              fprintf(archive,"%i: %i\n", i, instructions[i]);
       }
       fprintf(archive, "\n");
       fclose(archive);
}

void print_instructions(instruction_status_t *table, int size, char *path)
{
       FILE *archive = fopen(path, "a");
       if (archive == NULL){
              printf("Erro ao escrever no artigo!\n");
              exit(1);
       }
       int i;
       fprintf(archive, "\n1) status das instrucoes\n");
       fprintf(archive, "\t\temissao | leitura dos operandos | execução | escrita dos resultados\n");
       for (i = 0; i < size; i++)
       {
              fprintf(archive, "%i\t%i\t\t%i\t\t    %i\t\t%i\n", table[i].instruction, table[i].issue, table[i].readOperand, table[i].execComp, table[i].writeResult);
       }
       fprintf(archive, "\n");
       fclose(archive);
}

void print_instructions_complete(instruction_status_t *table, int size, char *path)
{
       FILE *archive = fopen(path, "a");
       if (archive == NULL){
              printf("Erro ao escrever no artigo!\n");
              exit(1);
       }
       int i;
       unsigned int opcode;
       fprintf(archive, "\n1) status das instrucoes\n");
       fprintf(archive, "\t\t      emissao | leitura dos operandos | execucao | escrita dos resultados\n");
       for (i = 0; i < size; i++)
       {
              opcode = desconverteOp(table[i].instruction);

              if (isR(table[i].instruction)){
                     opcode = desconverteFunct(table[i].instruction);
                     if (opcode == MOVE_DECIMAL)
                     {
                            fprintf(archive,"%4s $%s, $%s\t\t  %1i\t\t %4i\t %12i\t %12i\n",
                                   opcodeToString(desconverteFunct(table[i].instruction)),
                                   registerToString(desconverteRs(table[i].instruction)),
                                   registerToString(desconverteRd(table[i].instruction)),
                                   table[i].issue,
                                   table[i].readOperand,
                                   table[i].execComp,
                                   table[i].writeResult);
                     }
                     else{
                            fprintf(archive, "%4s $%s, $%s, $%s\t  %1i\t\t %4i\t %12i\t %12i\n",
                                   opcodeToString(desconverteFunct(table[i].instruction)),
                                   registerToString(desconverteRd(table[i].instruction)),
                                   registerToString(desconverteRs(table[i].instruction)),
                                   registerToString(desconverteRt(table[i].instruction)),
                                   table[i].issue,
                                   table[i].readOperand,
                                   table[i].execComp,
                                   table[i].writeResult);
                     }
              }

              else if (opcode == LI_DECIMAL)
              {
                     fprintf(archive, "%4s $%s, %3i\t\t  %1i\t\t %4i\t %12i\t %12i\n",
                            opcodeToString(desconverteOp(table[i].instruction)),
                            registerToString(desconverteRs(table[i].instruction)),
                            desconverteImmediate(table[i].instruction),
                            table[i].issue,
                            table[i].readOperand,
                            table[i].execComp,
                            table[i].writeResult);
              }
              else
              {
                     fprintf(archive, "%4s $%s, $%s, %3i\t  %1i\t\t %4i\t %12i\t %12i\n",
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
       fprintf(archive, "\n");
       fclose(archive);
}

void print_functional_unit(functional_unit_status_table_t *table, char *path)
{
       FILE *archive = fopen(path, "a");
       if (archive == NULL){
              printf("Erro ao escrever no artigo!\n");
              exit(1);
       }
       fprintf(archive, "\n2) status das unidades funcionais\n");
       fprintf(archive, "uf\t| busy\t| op\t| fi\t| fj\t| fk\t| qj\t| qk\t| rj\t| rk\n");
       fprintf(archive, "%-2i mult1 | %4s\t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s\n",
              table->mult1.time,
              table->mult1.busy ? "sim" : "nao",
              opcodeToString(table->mult1.op),
              registerToString(table->mult1.dest_Fi),
              registerToString(table->mult1.s1_Fj),
              registerToString(table->mult1.s2_Fk),
              typeOpToString(table->mult1.fu_Qj),
              typeOpToString(table->mult1.fu_Qk),
              table->mult1.busy ? table->mult1.fj_Rj ? "sim" : "nao" : "",
              table->mult1.busy ? table->mult1.fj_Rk ? "sim" : "nao" : "");
       fprintf(archive, "%-2i mult2 | %4s\t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s\n",
              table->mult2.time,
              table->mult2.busy ? "sim" : "nao",
              opcodeToString(table->mult2.op),
              registerToString(table->mult2.dest_Fi),
              registerToString(table->mult2.s1_Fj),
              registerToString(table->mult2.s2_Fk),
              typeOpToString(table->mult2.fu_Qj),
              typeOpToString(table->mult2.fu_Qk),
              table->mult2.busy ? table->mult2.fj_Rj ? "sim" : "nao" : "",
              table->mult2.busy ? table->mult2.fj_Rk ? "sim" : "nao" : "");
       fprintf(archive, "%-2i add   | %4s\t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s\n",
              table->add.time,
              table->add.busy ? "sim" : "nao",
              opcodeToString(table->add.op),
              registerToString(table->add.dest_Fi),
              registerToString(table->add.s1_Fj),
              registerToString(table->add.s2_Fk),
              typeOpToString(table->add.fu_Qj),
              typeOpToString(table->add.fu_Qk),
              table->add.busy ? table->add.fj_Rj ? "sim" : "nao" : "",
              table->add.busy ? table->add.fj_Rk ? "sim" : "nao" : "");
       fprintf(archive, "%-2i div   | %4s\t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s\n",
              table->divide.time,
              table->divide.busy ? "sim" : "nao",
              opcodeToString(table->divide.op),
              registerToString(table->divide.dest_Fi),
              registerToString(table->divide.s1_Fj),
              registerToString(table->divide.s2_Fk),
              typeOpToString(table->divide.fu_Qj),
              typeOpToString(table->divide.fu_Qk),
              table->divide.busy ? table->divide.fj_Rj ? "sim" : "nao" : "",
              table->divide.busy ? table->divide.fj_Rk ? "sim" : "nao" : "");
       fprintf(archive, "%-2i log   | %4s\t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s \t| %4s\n",
              table->log.time,
              table->log.busy ? "sim" : "nao",
              opcodeToString(table->log.op),
              registerToString(table->log.dest_Fi),
              registerToString(table->log.s1_Fj),
              registerToString(table->log.s2_Fk),
              typeOpToString(table->log.fu_Qj),
              typeOpToString(table->log.fu_Qk),
              table->log.busy ? table->log.fj_Rj ? "sim" : "nao" : "",
              table->log.busy ? table->log.fj_Rk ? "sim" : "nao" : "");
       fprintf(archive, "\n");
       fclose(archive);
}

void print_register_result(register_result_status_table_t *table, char *path)
{
       FILE *archive = fopen(path, "a");
       if (archive == NULL){
              printf("Erro ao escrever no artigo!\n");
              exit(1);
       }
       char *format = "%3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t\n";
       fprintf(archive, "\n3) status dos registradores\n");
       fprintf(archive, format,
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
       fprintf(archive, "\n");
       fprintf(archive, format,
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
       fprintf(archive, "\n");
       fclose(archive);
}

void print_register_database(register_database_t *table, char *path)
{
       FILE *archive = fopen(path, "a");
       if (archive == NULL){
              printf("Erro ao escrever no artigo!\n");
              exit(1);
       }
       char *formatRegName = "%3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t| %3s\t\n";
       char *format = "%3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t| %3i\t\n";
       fprintf(archive, "\n4) banco de registradores\n");
       fprintf(archive, formatRegName,
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
       fprintf(archive, "\n");
       fprintf(archive, format,
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
       fprintf(archive, "\n");
       fclose(archive);
}

#endif
