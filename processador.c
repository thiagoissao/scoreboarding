#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "components/functional_unit_status.h"
#include "components/instruction_status.h"
#include "components/register_result_status.h"
#include "components/register_database.h"
#include "config/config.h"
#include "types/i_types.h"
#include "conversor.h"
#include "prints/prints.h"
#include "utils/validations.h"
#include "utils/can_proceed_to_issue.h"
#include "utils/verifications.h"

void defineNextStep();
void executeScoreboarding();
void preencheFU();
bool writeResult();
bool readOperands();
bool executeIssue();
bool operaLatencia();
bool executeOperands();

unsigned int clock;

// EXEMPLO INSTRUCAO //
//  ADD  = R[RD] = R[RS] + R[RT]
//
//  ADDI = R[RS] = [RT]  + Imediate

void executeScoreboarding(
    int config_size,
    config_t *config,
    unsigned int numberOfInstructions,
    functional_unit_status_table_t *fu_status_table,
    instruction_status_t *inst_status_table,
    register_result_status_table_t *rr_status_table,
    register_database_t *register_database)
{
  // inicializa
  clock = 1;
  unsigned int instAtual = 0, j;
  bool nextStep[numberOfInstructions], allWasWrited = false, allWasRead;

  defineNextStep(nextStep, numberOfInstructions);

  while (!allWasWrited)
  {
    printf("\n\n-------------------------------------------------------- CICLO %i -----------------------------------------------------------------\n", clock);

    if (executeIssue(inst_status_table[instAtual].instruction, inst_status_table, fu_status_table, rr_status_table, instAtual))
    {
      nextStep[instAtual] = false;
      instAtual++; // se a atual iniciou pra issue a inst pode ir pra proxima
    }

    for (j = 0; j < instAtual; j++)
    {
      if (inst_status_table[j].issue != -1 && inst_status_table[j].readOperand == -1)
        readOperands(inst_status_table, fu_status_table, nextStep, j);
    }

    for (j = 0; j < instAtual; j++)
    {
      if (inst_status_table[j].readOperand != -1 && inst_status_table[j].execComp == -1)
        executeOperands(inst_status_table, fu_status_table, nextStep, j, config, config_size);
    }

    for (j = 0; j < instAtual; j++)
    {
      if (inst_status_table[j].execComp != -1 && inst_status_table[j].writeResult == -1)
        writeResult(inst_status_table, fu_status_table, nextStep, j);
    }

    print_instructions_complete(inst_status_table, numberOfInstructions);
    printf("\n");
    print_functional_unit(fu_status_table);
    printf("\n");
    print_register_result(rr_status_table);
    printf("\n");
    print_register_database(register_database);

    defineNextStep(nextStep, instAtual);
    allWasWrited = verify_if_all_was_writed(inst_status_table, 2, clock);
    clock += 1;
  }
}

void defineNextStep(bool *nextStep, unsigned int numberInst)
{
  int i;
  for (i = 0; i < numberInst; i++)
  {
    nextStep[i] = true;
  }
}

void preencheFU(unsigned int instruction, functional_unit_status_table_t *fu_status_table)
{
  UnitInstruction_t dependenciaQK, dependenciaQJ, typeOp;
  unsigned int funct, rs, rt, opcode, rd, shamt, immediate;

  rs = desconverteRs(instruction);
  rt = desconverteRt(instruction);
  opcode = desconverteOp(instruction);
  //immediate = desconverteImmediate(instruction);

  if (isR(instruction))
  {
    rd = desconverteRd(instruction);
    shamt = desconverteShamt(instruction);
    funct = desconverteFunct(instruction);
    typeOp = getTypeOp(funct, fu_status_table);
  }
  else
  {
    typeOp = getTypeOp(opcode, fu_status_table);
    rd = rs;
    rs = rt;
    rt = 0;
  }

  //verifica Rk e Rj e passar pra preencher tb
  isR(instruction) ? verify_dependency(fu_status_table, typeOp, rs, rt, opcode, &dependenciaQJ, &dependenciaQK) : verify_dependency(fu_status_table, typeOp, rs, rt, funct, &dependenciaQJ, &dependenciaQK);

  if (isR(instruction))
    setInstFu(fu_status_table, typeOp, funct, rd, rs, rt, dependenciaQJ, dependenciaQK);
  else
    setInstFu(fu_status_table, typeOp, opcode, rd, rs, rt, dependenciaQJ, dependenciaQK); //time?
  // preenche Bush / op / Fi / Fj / Fk / Rj / Rk / Qj / Qk / time
}

void preencheRegStatus(
    unsigned int instruction,
    register_result_status_table_t *rr_status_table,
    functional_unit_status_table_t *fu_status_table,
    bool isRType)
{
  unsigned int opcode, registrador;
  UnitInstruction_t typeOp;

  if (isRType)
  {
    opcode = desconverteFunct(instruction);
    registrador = desconverteRd(instruction);
  }
  else
  {
    opcode = desconverteOp(instruction);
    registrador = desconverteRs(instruction);
  }

  typeOp = getTypeOp(opcode, fu_status_table);

  setRegisterResult(rr_status_table, registrador, typeOp);
}

bool executeIssue(unsigned int instruction, instruction_status_t *inst_status_table,
                  functional_unit_status_table_t *fu_status_table, register_result_status_table_t *rr_status_table, unsigned int instAtual)
{

  // verifica disponibilidade da sessao da operacao na FU
  bool canProceed = can_proceed_to_issue(instruction, fu_status_table, rr_status_table);

  if (canProceed)
  {
    inst_status_table[instAtual].issue = clock;                                         // atualiza o clock no status na tabela d inst
    preencheFU(instruction, fu_status_table);                                           // preenche tabela FU
    preencheRegStatus(instruction, rr_status_table, fu_status_table, isR(instruction)); // preenche tab dos Reg
    return true;
  }
  else
    return false;
}

bool readOperands(instruction_status_t *inst_status_table, functional_unit_status_table_t *fu_status_table,
                  bool *nextStep, unsigned int idInstrucao)
{
  /*
  espere até que não haja riscos de dados, então leia os operandos
      Condições de espera: 
        (1) todos os operandos de origem estão disponíveis
      
      Ações: 
        (1) a unidade de função lê operandos de registro e inicia a execução do próximo ciclo
  */
  unsigned int instruction = inst_status_table[idInstrucao].instruction;
  UnitInstruction_t typeOp;
  unsigned int funct, opcode;

  opcode = desconverteOp(instruction);

  if (isR(instruction))
  {
    funct = desconverteFunct(instruction);
    typeOp = getTypeOp(funct, fu_status_table);
  }
  else
    typeOp = getTypeOp(opcode, fu_status_table);

  bool canProceed = operandsDisponiveis(fu_status_table, typeOp);

  if (!canProceed)
    return false;

  if (nextStep[idInstrucao])
  {
    inst_status_table[idInstrucao].readOperand = clock;
    nextStep[idInstrucao] = false;
    return true;
  }

  return false;
}

bool executeOperands(instruction_status_t *inst_status_table, functional_unit_status_table_t *fu_status_table,
                     bool *nextStep, unsigned int idInstrucao, config_t *config, int config_size)
{
  /*3-
    Execution - opera em operandos (EX)
      Ações: 
        (1) A unidade funcional inicia a execução ao receber operandos. 
            Quando o resultado estiver pronto, ele notifica o placar de que concluiu a execução.
  */
  unsigned int instruction = inst_status_table[idInstrucao].instruction;
  UnitInstruction_t typeOp;
  unsigned int funct, opcode;
  bool canProceed;

  if (!nextStep[idInstrucao])
    return false;

  opcode = desconverteOp(instruction);

  if (isR(instruction))
  {
    funct = desconverteFunct(instruction);
    typeOp = getTypeOp(funct, fu_status_table);
    opcode = funct;
  }
  else
    typeOp = getTypeOp(opcode, fu_status_table);

  // seta time
  if (!verifyTimeRealied(typeOp, fu_status_table))
    setTimeToFu(opcode, fu_status_table, config, config_size);
  // execute operacao em alguma hr

  canProceed = operaLatencia(fu_status_table, typeOp);
  // se for a ultima latencia/time ele retorna 0 (true) se nao, ele diminui e retorna false

  if (canProceed)
    inst_status_table[idInstrucao].execComp = clock;

  nextStep[idInstrucao] = false;
  return true;
}

bool operaLatencia(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp)
{
  switch (typeOp)
  {
  case mult1:
    fu_status_table->mult1.time -= 1;
    return fu_status_table->mult1.time == 0;

  case mult2:
    fu_status_table->mult2.time -= 1;
    return fu_status_table->mult2.time == 0;

  case add:
    fu_status_table->add.time -= 1;
    return fu_status_table->add.time == 0;

  case divide:
    fu_status_table->divide.time -= 1;
    return fu_status_table->divide.time == 0;

  case log:
    fu_status_table->log.time -= 1;
    return fu_status_table->log.time == 0;

  default:
    printf("Erro ao operar latencia!");
    return false;
  }
}

bool writeResult(instruction_status_t *inst_status_table, functional_unit_status_table_t *fu_status_table,
                 bool *nextStep, unsigned int idInstrucao)
{
  /*
  Write Resulta - execução final (WB)
      Condição de espera: 
            nenhuma outra instrução / FU vai ler o registrador de destino da instrução
  */
  unsigned int instruction = inst_status_table[idInstrucao].instruction;
  bool canProceed;

  UnitInstruction_t typeOp; // se pa funcao p substituir esse processo ou ja definir o type d cada instrucao no inicio
  unsigned int funct, opcode;

  if (!nextStep[idInstrucao])
    return false;

  opcode = desconverteOp(instruction);

  if (isR(instruction))
  {
    funct = desconverteFunct(instruction);
    typeOp = getTypeOp(funct, fu_status_table);
  }
  else
    typeOp = getTypeOp(opcode, fu_status_table);

  canProceed = verify_raw(fu_status_table, typeOp);

  if (canProceed)
  {
    printf("\nPrestes a terminar -> %d\n", clock);

    // escreve
    inst_status_table[idInstrucao].writeResult = clock;
    // atualizar o registrador -> setar o dele
    // atualizar as tabela -> setar o dele
    return true;
  }

  return false;
}

/*
    Help do scoreboarding
    ------------------------------------------------------------------
    1-
    Issue - instruções de decodificação e verificação de riscos estruturais
      Condições de espera:
        (1) o FU necessário estar livre; 
        (2) nenhuma outra instrução escreve para o mesmo destino de registro (para evitar WAW)

      Ações: 
        (1) a instrução segue para a FU; 
        (2) o placar atualiza sua estrutura de dados interna. Se uma instrução for interrompida neste estágio, nenhuma outra instrução poderá prosseguir.
    ------------------------------------------------------------------
    2-
    Read Operands - espere até que não haja riscos de dados, então leia os operandos
      Condições de espera: 
        (1) todos os operandos de origem estão disponíveis
      
      Ações: 
        (1) a unidade de função lê operandos de registro e inicia a execução do próximo ciclo
    ------------------------------------------------------------------
    3-
    Execution - opera em operandos (EX)
      Ações: 
        (1) A unidade funcional inicia a execução ao receber operandos. 
            Quando o resultado estiver pronto, ele notifica o placar de que concluiu a execução.
    ------------------------------------------------------------------
    4-
    Write Resulta - execução final (WB)
      Condição de espera: 
            nenhuma outra instrução / FU vai ler o registrador de destino da instrução
      Ações: 
            Escreva o registro e atualize o placar
            
            Exemplo de WAR: DIVD F0, F2, F4
                            ADDD F10, F0, F8
                            SUBD F8, F8, F14
            
            O placar CDC 6600 paralisaria o SUBD até que o ADDD leia operandos
    ------------------------------------------------------------------

     unsigned int opcode = desconverteOp(instruction);
     unsigned int rs = desconverteRs(instruction);
     unsigned int rt = desconverteRt(instruction);

     if (opcode == R)
     {
       unsigned int rd = desconverteRd(instruction);
       unsigned int shamt = desconverteShamt(instruction);
       unsigned int funct = desconverteFunct(instruction);
     }
     else //tipo I
     {
      unsigned int immediate = desconverteImmediate(instruction);
   }

  */
