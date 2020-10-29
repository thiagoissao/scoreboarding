#include <stdio.h>
#include <stdbool.h>
#include "unidades_funcionais/functional_unit_status.h"
#include "unidades_funcionais/instruction_status.h"
#include "unidades_funcionais/register_result_status.h"
#include "tipos_instrucoes/i_types.h"
#include "conversor.h"

unsigned int clock;


void preencheFU(unsigned int instruction, functional_unit_status_table_t *fu_status_table){
  bool isR;
  unsigned int funct, rs, rt, opcode, rd, shamt, immediate;
  
  rs        = desconverteRs(instruction);
  rt        = desconverteRt(instruction);
  opcode    = desconverteOp(instruction);
  immediate = desconverteImmediate(instruction);
  isR       = (opcode == R);

  if (isR){
    rd    = desconverteRd(instruction);
    shamt = desconverteShamt(instruction);
    funct = desconverteFunct(instruction);
  }

  //verifica Rk e Rj e passar pra preencher tb
  setInstFu(fu_status_table, opcode, rd, rs, rt);
  // preencher Bush / op / Fi / Fj / Fk / Qj / Qk / Rj / Rk
}

void preencheRegStatus(unsigned int instruction, register_result_status_table_t *rr_status_table){

}

bool verifyIfAllWasWrited(instruction_status_t *inst_status_table, unsigned int size)
{
  if (clock == 3) 
    return true;
  else
    return false;

  //for (int i = 0; i < size; i++)
  //{
  //  if (inst_status_table->writeResult == -1)
  //  {
  //    return false;
  //  }
  //}
  return true;
}

bool executeIssue(unsigned int instruction, instruction_status_t *inst_status_table, 
              functional_unit_status_table_t *fu_status_table, register_result_status_table_t *rr_status_table)
{
  unsigned int opcode = desconverteOp(instruction);
  unsigned int funct  = desconverteFunct(instruction);

  bool isR = (opcode == R);

  // verifica disponibilidade da sessao da operacao na FU
  bool canProceed = isR ? !getBusy(fu_status_table, funct) : !getBusy(fu_status_table, opcode);
  
  printf("Segue? %d\n", canProceed);
  if (canProceed){ 
    inst_status_table->issue = clock; // atualiza o clock no status na tabela d inst
    preencheFU(instruction, fu_status_table); // preenche tabela FU
    preencheRegStatus(instruction, rr_status_table); // preenche tab dos Reg
    printf("na fu: %d\n", fu_status_table->add.op);
    return true;
  }
  else 
    return false;
}

void readOperands(unsigned int instruction)
{
}

void executeOperands(unsigned int instruction)
{
}

void writeResult(unsigned int instruction)
{
}

void executeScoreboarding(
    unsigned int numberOfInstructions,
    functional_unit_status_table_t *fu_status_table,
    instruction_status_t *inst_status_table,
    register_result_status_table_t *rr_status_table)
{
  // inicializa
  clock = 1;
  unsigned int instAtual = 0;
  bool allWasWrited = false;


  while (!allWasWrited)
  {
    printf("\nInicio clock\n");
    printf("Busy add: %d\n", fu_status_table->add.busy);
    
    if (executeIssue(inst_status_table[instAtual].instruction, inst_status_table, fu_status_table, rr_status_table))
      instAtual++;    // se a atual iniciou pra issue a inst pode ir pra proxima

    printf("Busy add: %d\n", fu_status_table->add.busy);

    readOperands(inst_status_table[0].instruction);
    executeOperands(inst_status_table[0].instruction);
    writeResult(inst_status_table[0].instruction);

    printf("Fim clock\n");
    allWasWrited = verifyIfAllWasWrited(inst_status_table, 2);
    clock += 1;
  }

  // unsigned int opcode = desconverteOp(instruction);
  // unsigned int rs = desconverteRs(instruction);
  // unsigned int rt = desconverteRt(instruction);

  // if (opcode == R)
  // {
  //   unsigned int rd = desconverteRd(instruction);
  //   unsigned int shamt = desconverteShamt(instruction);
  //   unsigned int funct = desconverteFunct(instruction);
  // }
  // else //tipo I
  // {
  //   unsigned int immediate = desconverteImmediate(instruction);
  // }
}
