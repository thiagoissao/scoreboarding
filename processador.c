#include <stdio.h>
#include <stdbool.h>
#include "unidades_funcionais/functional_unit_status.h"
#include "unidades_funcionais/instruction_status.h"
#include "unidades_funcionais/register_result_status.h"
#include "tipos_instrucoes/i_types.h"
#include "conversor.h"
#include "utils/prints.h"
#include "utils/validations.h"
void defineNextStep();
void executeScoreboarding();
void writeResult();
void executeOperands();
void preencheFU();
void verifyDependency();
bool readOperands();
bool executeIssue();
bool verifyIfAllWasWrited();

unsigned int clock;

// EXEMPLO INSTRUCAO //
//  ADD  = R[RD] = R[RS] + R[RT]
//
//  ADDI = R[RS] = [RT]  + Imediate

void executeScoreboarding(
    unsigned int numberOfInstructions,
    functional_unit_status_table_t *fu_status_table,
    instruction_status_t *inst_status_table,
    register_result_status_table_t *rr_status_table)
{
  // inicializa
  clock = 1;
  unsigned int instAtual = 0;
  bool allWasWrited = false, allWasRead;

  while (!allWasWrited)
  {
    printf("\n\n---------------------------------- CICLO %i ------------------------------------------\n", clock);
    print_instructions_complete(inst_status_table, numberOfInstructions);
    printf("\n");
    print_functional_unit(fu_status_table);
    printf("\n");
    print_register_result(rr_status_table);

    if (executeIssue(inst_status_table[instAtual].instruction, inst_status_table, fu_status_table, rr_status_table, instAtual))
    {
      inst_status_table[instAtual].nextStep = false;
      instAtual++; // se a atual iniciou pra issue a inst pode ir pra proxima
    }

    for (int j = 0; j < instAtual; j++)
    {
      if (inst_status_table[j].issue != -1 && inst_status_table[j].readOperand == -1)
        readOperands(inst_status_table, fu_status_table, j);
    }

    executeOperands(inst_status_table[0].instruction);
    writeResult(inst_status_table[0].instruction);

    defineNextStep(inst_status_table, instAtual);
    allWasWrited = verifyIfAllWasWrited(inst_status_table, 2);
    clock += 1;
  }
}

void defineNextStep(instruction_status_t *inst_status_table, unsigned int numberInst)
{
  int i;
  for (i = 0; i < numberInst; i++)
  {
    inst_status_table[i].nextStep = true;
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
    typeOp = getTypeOp(funct);
  }
  else
  {
    typeOp = getTypeOp(opcode);
    rd = rs;
    rs = rt;
    rt = 0;
  }

  //verifica Rk e Rj e passar pra preencher tb
  isR(instruction) ? verifyDependency(fu_status_table, typeOp, rs, rt, opcode, &dependenciaQJ, &dependenciaQK) : verifyDependency(fu_status_table, typeOp, rs, rt, funct, &dependenciaQJ, &dependenciaQK);

  if (isR(instruction))
    setInstFu(fu_status_table, typeOp, funct, rd, rs, rt, dependenciaQJ, dependenciaQK, 1);
  else
    setInstFu(fu_status_table, typeOp, opcode, rd, rs, rt, dependenciaQJ, dependenciaQK, 1);
  // preenche Bush / op / Fi / Fj / Fk / Rj / Rk / Qj / Qk / time
}

void preencheRegStatus(unsigned int instruction, register_result_status_table_t *rr_status_table, bool isRType)
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

  typeOp = getTypeOp(opcode);

  setRegistrador(rr_status_table, registrador, typeOp);
}

bool verifyIfAllWasWrited(instruction_status_t *inst_status_table, unsigned int size)
{
  if (clock == 5)
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
                  functional_unit_status_table_t *fu_status_table, register_result_status_table_t *rr_status_table, unsigned int instAtual)
{
  unsigned int opcode = desconverteOp(instruction);
  unsigned int funct = desconverteFunct(instruction);

  // verifica disponibilidade da sessao da operacao na FU
  bool canProceed = isR(instruction) ? !getBusy(fu_status_table, funct) : !getBusy(fu_status_table, opcode);

  if (canProceed)
  {
    inst_status_table[instAtual].issue = clock;                        // atualiza o clock no status na tabela d inst
    preencheFU(instruction, fu_status_table);                          // preenche tabela FU
    preencheRegStatus(instruction, rr_status_table, isR(instruction)); // preenche tab dos Reg
    return true;
  }
  else
    return false;
}

void verifyDependency(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp,
                      unsigned int fjAtual, unsigned int fkAtual, unsigned int opcode,
                      UnitInstruction_t *dependenciaQJ, UnitInstruction_t *dependenciaQK)
{
  *dependenciaQJ = empty;
  *dependenciaQK = empty;

  if (fu_status_table->add.busy && typeOp != ADD_FU_DECIMAL)
  {
    if (fu_status_table->add.dest_Fi == fjAtual)
      *dependenciaQJ = ADD_FU_DECIMAL;

    if (fu_status_table->add.dest_Fi == fkAtual)
      *dependenciaQK = ADD_FU_DECIMAL;
  }

  if (fu_status_table->mult1.busy && typeOp != MULT1_FU_DECIMAL)
  {
    if (fu_status_table->mult1.dest_Fi == fjAtual)
      *dependenciaQJ = MULT1_FU_DECIMAL;

    if (fu_status_table->mult1.dest_Fi == fkAtual)
      *dependenciaQK = MULT1_FU_DECIMAL;
  }

  if (fu_status_table->mult2.busy && typeOp != MULT2_FU_DECIMAL)
  {
    if (fu_status_table->mult2.dest_Fi == fjAtual)
      *dependenciaQJ = MULT2_FU_DECIMAL;

    if (fu_status_table->mult2.dest_Fi == fkAtual)
      *dependenciaQK = MULT2_FU_DECIMAL;
  }

  if (fu_status_table->divide.busy && typeOp != DIVIDE_FU_DECIMAL)
  {
    if (fu_status_table->divide.dest_Fi == fjAtual)
      *dependenciaQJ = DIVIDE_FU_DECIMAL;

    if (fu_status_table->divide.dest_Fi == fkAtual)
      *dependenciaQK = DIVIDE_FU_DECIMAL;
  }

  if (fu_status_table->log.busy && typeOp != LOG_FU_DECIMAL)
  {
    if (fu_status_table->log.dest_Fi == fjAtual)
      *dependenciaQJ = LOG_FU_DECIMAL;

    if (fu_status_table->log.dest_Fi == fkAtual)
      *dependenciaQK = LOG_FU_DECIMAL;
  }
}

bool readOperands(instruction_status_t *inst_status_table, functional_unit_status_table_t *fu_status_table, unsigned int idInstrucao)
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
    typeOp = getTypeOp(funct);
  }
  else
    typeOp = getTypeOp(opcode);

  bool canProceed = operandsDisponiveis(fu_status_table, typeOp);

  if (!canProceed)
    return false;

  if (inst_status_table[idInstrucao].nextStep)
  {
    inst_status_table[idInstrucao].readOperand = clock;
    inst_status_table[idInstrucao].nextStep = false;
    return true;
  }

  return false;
}

void executeOperands(unsigned int instruction)
{
}

void writeResult(unsigned int instruction)
{
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
            
            Exemplo de WAR: DIVD F0, F2, F4ADDD
                            F10, F0, F8
                            SUB DF8, F8, F14
            
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
