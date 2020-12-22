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
#include "utils/utils.h"
#include "utils/can_proceed_to_issue.h"
#include "utils/verifications.h"
#include "operations/operations.h"

void execute_pipeline();
bool write_result();
bool read_operands();
bool execute_issue();
bool execute_operands();

void execute_pipeline(
    char *path,
    char *archive,
    int config_size,
    config_t *config,
    unsigned int numberOfInstructions)
{

  // Cria na memória um array com o inteiro de cada instrução
  unsigned int instruction_set[numberOfInstructions];

  // Converte o conjunto das instruções para inteiro e armazena no array passado por referência
  converter(archive, instruction_set);

  // Status das unidades funcionais e inicialização
  functional_unit_status_table_t *fu_status_table = (functional_unit_status_table_t *)malloc(sizeof(functional_unit_status_table_t));
  init_functional_unit_status_table(fu_status_table);

  // Status das instruções e inicialização
  instruction_status_t inst_status_table[numberOfInstructions];
  init_instruction_status_table(inst_status_table, instruction_set, numberOfInstructions);

  // Status dos registradores e inicialização
  register_result_status_table_t *rr_status_table = (register_result_status_table_t *)malloc(sizeof(register_result_status_table_t));
  init_register_status_table(rr_status_table);

  // Banco de registradores
  register_database_t *register_database = (register_database_t *)malloc(sizeof(register_database_t));
  init_register_database(register_database);

  // inicializa
  unsigned int clock = 1;
  unsigned int instAtual = 0, j;
  bool nextStep[numberOfInstructions], nextStepRead[numberOfInstructions];
  bool allWasWrited = false, allWasRead;
  FILE *destiny;

  define_next_step(nextStep, numberOfInstructions);
  define_next_step(nextStepRead, numberOfInstructions);

  while (!allWasWrited)
  {
    destiny = fopen(path, "a");
    fprintf(destiny, "\n\n-------------------------------------------------------- ciclo %i -----------------------------------------------------------------\n", clock);
    fclose(destiny);

    if (instAtual < numberOfInstructions && execute_issue(
                                                inst_status_table[instAtual].instruction,
                                                inst_status_table,
                                                fu_status_table,
                                                rr_status_table,
                                                instAtual,
                                                clock))
    {
      nextStep[instAtual] = false;
      instAtual++; // se a atual iniciou pra issue a inst pode ir pra proxima
    }

    if (instAtual > numberOfInstructions)
      instAtual = numberOfInstructions;

    for (j = 0; j < instAtual; j++)
    {
      if (inst_status_table[j].issue != -1 && inst_status_table[j].readOperand == -1)
        read_operands(
            inst_status_table,
            fu_status_table,
            nextStep,
            nextStepRead,
            j,
            clock);
    }

    for (j = 0; j < instAtual; j++)
    {
      if (inst_status_table[j].readOperand != -1 && inst_status_table[j].execComp == -1)
        execute_operands(
            inst_status_table,
            fu_status_table,
            nextStep,
            j,
            config,
            config_size,
            clock);
    }

    for (j = 0; j < instAtual; j++)
    {
      if (inst_status_table[j].execComp != -1 && inst_status_table[j].writeResult == -1)
        write_result(
            register_database,
            inst_status_table,
            fu_status_table,
            rr_status_table,
            nextStepRead, nextStep,
            j,
            clock);
    }

    printa(inst_status_table, numberOfInstructions, fu_status_table, rr_status_table, register_database, path);

    define_next_step(nextStep, instAtual);
    define_next_step(nextStepRead, instAtual);
    allWasWrited = verify_if_all_was_writed(inst_status_table, numberOfInstructions, clock);
    clock += 1;
  }

  free(fu_status_table);
  free(rr_status_table);
  free(register_database);
}

bool execute_issue(unsigned int instruction, instruction_status_t *inst_status_table,
                   functional_unit_status_table_t *fu_status_table, register_result_status_table_t *rr_status_table, unsigned int instAtual, unsigned int clock)
{

  // verifica disponibilidade da sessao da operacao na FU
  bool canProceed = can_proceed_to_issue(instruction, fu_status_table, rr_status_table);

  if (canProceed)
  {
    inst_status_table[instAtual].issue = clock;                                                    // atualiza o clock no status na tabela d inst
    update_register_result_table(instruction, rr_status_table, fu_status_table, isR(instruction)); // preenche tab dos Reg
    update_functional_unit_table(instruction, fu_status_table);                                    // preenche tabela FU
    return true;
  }
  else
    return false;
}

bool read_operands(
    instruction_status_t *inst_status_table,
    functional_unit_status_table_t *fu_status_table,
    bool *nextStep,
    bool *nextStepRead,
    unsigned int idInstrucao,
    unsigned int clock)

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

  if (typeOp == mult1)
  {
    if (fu_status_table->mult1.dest_Fi != desconverteRd(instruction))
      typeOp = mult2;
  }

  bool canProceed = operandsDisponiveis(fu_status_table, typeOp);

  if (!canProceed)
    return false;

  if (nextStep[idInstrucao])
  {
    inst_status_table[idInstrucao].readOperand = clock;
    nextStep[idInstrucao] = false;
    nextStepRead[idInstrucao] = false;
    return true;
  }

  return false;
}

bool execute_operands(
    instruction_status_t *inst_status_table,
    functional_unit_status_table_t *fu_status_table,
    bool *nextStep,
    unsigned int id_instrucao,
    config_t *config,
    int config_size,
    unsigned int clock)
{
  /*3-
    Execution - opera em operandos (EX)
      Ações: 
        (1) A unidade funcional inicia a execução ao receber operandos. 
            Quando o resultado estiver pronto, ele notifica o placar de que concluiu a execução.
  */
  unsigned int instruction = inst_status_table[id_instrucao].instruction;
  UnitInstruction_t typeOp;
  unsigned int funct, opcode;
  bool can_proceed;

  if (!nextStep[id_instrucao])
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

  if (typeOp == mult1)
  {
    if (fu_status_table->mult1.dest_Fi != desconverteRd(instruction))
      typeOp = mult2;
  }

  // seta time
  if (!verifyTimeRealied(typeOp, fu_status_table))
    setTimeToFu(opcode, fu_status_table, config, config_size, typeOp == mult2);
  // execute operacao em alguma hr

  can_proceed = opera_latencia(fu_status_table, typeOp);
  // se for a ultima latencia/time ele retorna 0 (true) se nao, ele diminui e retorna false

  if (can_proceed)
    inst_status_table[id_instrucao].execComp = clock;

  nextStep[id_instrucao] = false;
  return true;
}

bool write_result(
    register_database_t *register_database,
    instruction_status_t *inst_status_table,
    functional_unit_status_table_t *fu_status_table,
    register_result_status_table_t *rr_status_table,
    bool *nextStepRead, bool *nextStep, unsigned int idInstrucao, unsigned int clock)
{
  /*
  Write Resulta - execução final (WB)
      Condição de espera: 
            nenhuma outra instrução / FU vai ler o registrador de destino da instrução
  */
  unsigned int instruction = inst_status_table[idInstrucao].instruction;
  bool canProceed;

  UnitInstruction_t typeOp; // se pa funcao p substituir esse processo ou ja definir o type d cada instrucao no inicio
  unsigned int opcode;

  if (!nextStep[idInstrucao])
    return false;

  opcode = desconverteOp(instruction);

  if (isR(instruction))
  {
    opcode = desconverteFunct(instruction);
    typeOp = getTypeOp(opcode, fu_status_table);
  }
  else
    typeOp = getTypeOp(opcode, fu_status_table);

  if (typeOp == mult1)
  {
    if (fu_status_table->mult1.dest_Fi != desconverteRd(instruction))
      typeOp = mult2;
  }

  canProceed = verify_war(inst_status_table, fu_status_table, typeOp, nextStepRead, idInstrucao);

  if (canProceed)
  {
    // escreve
    inst_status_table[idInstrucao].writeResult = clock;
    update_register_database(opcode, instruction, register_database);
    update_components_after_write_result(instruction, rr_status_table, fu_status_table);
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
