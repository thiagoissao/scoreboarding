#include <stdio.h>
#include <stdbool.h>
#include "unidades_funcionais/functional_unit_status.h"
#include "unidades_funcionais/instruction_status.h"
#include "unidades_funcionais/register_result_status.h"
#include "tipos_instrucoes/i_types.h"
#include "conversor.h"

void executeScoreboarding();
void writeResult();
void readOperands();
void executeOperands();
void preencheFU();
bool executeIssue();
bool verifyIfAllWasWrited();
UnitInstruction_t verifyDependency();

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
  bool allWasWrited = false;

  while (!allWasWrited)
  {
    printf("\n---------Inicio clock--------\n");
    printf("Busy Add Ocupado: %s\n", fu_status_table->add.busy ? "Sim" : "Não" );

    if (executeIssue(inst_status_table[instAtual].instruction, inst_status_table, fu_status_table, rr_status_table, instAtual))
      instAtual++; // se a atual iniciou pra issue a inst pode ir pra proxima

    readOperands(inst_status_table[0].instruction);
    executeOperands(inst_status_table[0].instruction);
    writeResult(inst_status_table[0].instruction);

    printf("----------Fim clock----------\n");
    allWasWrited = verifyIfAllWasWrited(inst_status_table, 2);
    clock += 1;
  }
}

void preencheFU(unsigned int instruction, functional_unit_status_table_t *fu_status_table)
{
  bool isR;
  UnitInstruction_t dependenciaQK, dependenciaQJ, typeOp;
  unsigned int funct, rs, rt, opcode, rd, shamt, immediate;

  rs = desconverteRs(instruction);
  rt = desconverteRt(instruction);
  opcode = desconverteOp(instruction);
  //immediate = desconverteImmediate(instruction);
  isR = (opcode == R);

  if (isR)
  {
    rd = desconverteRd(instruction);
    shamt = desconverteShamt(instruction);
    funct = desconverteFunct(instruction);
    typeOp = getTypeOp(funct);
  }
  else{
    typeOp = getTypeOp(opcode);
    rd = rs;
    rs = rt;
    rt = 0;
  }
  
  //verifica Rk e Rj e passar pra preencher tb
  dependenciaQK, dependenciaQJ = isR ? verifyDependency(fu_status_table, typeOp, rs, rt, opcode) : verifyDependency(fu_status_table, typeOp, rs, rt, funct);

  if (isR)
    setInstFu(fu_status_table, typeOp, funct, rd, rs, rt, dependenciaQJ, dependenciaQK, 1);
  else
    setInstFu(fu_status_table, typeOp, opcode, rd, rs, rt, dependenciaQJ, dependenciaQK, 1);
  // preenche Bush / op / Fi / Fj / Fk / Rj / Rk / Qj / Qk / time
  
}

void preencheRegStatus(unsigned int instruction, register_result_status_table_t *rr_status_table, bool isR)
{
  unsigned int opcode, registrador;
  UnitInstruction_t typeOp;

  if (isR){
    opcode = desconverteFunct(instruction);
    registrador = desconverteRd(instruction);
  }
  else{
    opcode = desconverteOp(instruction);
    registrador = desconverteRs(instruction);
  }
  
  typeOp = getTypeOp(opcode);

  setRegistrador(rr_status_table, registrador, typeOp);
  printf("Reg t0: %d\nReg s0: %d\n", rr_status_table->t0, rr_status_table->s2);
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
                  functional_unit_status_table_t *fu_status_table, register_result_status_table_t *rr_status_table, unsigned int instAtual)
{
  unsigned int opcode = desconverteOp(instruction);
  unsigned int funct = desconverteFunct(instruction);

  bool isR = (opcode == R);

  // verifica disponibilidade da sessao da operacao na FU
  bool canProceed = isR ? !getBusy(fu_status_table, funct) : !getBusy(fu_status_table, opcode);

  printf("Segue? %s\n", canProceed ? "Sim" : "Não");
  if (canProceed)
  {
    inst_status_table[instAtual].issue = clock;                // atualiza o clock no status na tabela d inst
    preencheFU(instruction, fu_status_table);        // preenche tabela FU
    preencheRegStatus(instruction, rr_status_table, isR); // preenche tab dos Reg
    return true;
  }
  else
    return false;
}

UnitInstruction_t verifyDependency(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp, 
                  unsigned int fjAtual, unsigned int fkAtual, unsigned int opcode)
{
  UnitInstruction_t dependenciaQJ, dependenciaQK;
  
  dependenciaQJ = empty;
  dependenciaQK = empty;

  // fiquei meio incerto se isso realmente da certo, pq ele verifica na ordem da tabela 
  // e nao das instrucoes, sera q tem como criar uma dependecia que não é a dele realmente

  if (fu_status_table->add.busy && typeOp != ADD_FU_DECIMAL){ 
    if (fu_status_table->add.dest_Fi == fjAtual)
      dependenciaQJ = ADD_FU_DECIMAL;

    if (fu_status_table->add.dest_Fi == fkAtual)
      dependenciaQK = ADD_FU_DECIMAL;
  }

  if (fu_status_table->mult1.busy && typeOp != MULT1_FU_DECIMAL){
    if (fu_status_table->mult1.dest_Fi == fjAtual)
      dependenciaQJ = MULT1_FU_DECIMAL;

    if (fu_status_table->mult1.dest_Fi == fkAtual)
      dependenciaQK = MULT1_FU_DECIMAL;
  }

  if (fu_status_table->mult2.busy && typeOp != MULT2_FU_DECIMAL){
    if (fu_status_table->mult2.dest_Fi == fjAtual)
      dependenciaQJ = MULT2_FU_DECIMAL;

    if (fu_status_table->mult2.dest_Fi == fkAtual)
      dependenciaQK = MULT2_FU_DECIMAL;
  }

  if (fu_status_table->divide.busy && typeOp != DIVIDE_FU_DECIMAL){
    if (fu_status_table->divide.dest_Fi == fjAtual)
      dependenciaQJ = DIVIDE_FU_DECIMAL;

    if (fu_status_table->divide.dest_Fi == fkAtual)
      dependenciaQK = DIVIDE_FU_DECIMAL;  
  }

  if (fu_status_table->log.busy && typeOp != LOG_FU_DECIMAL){
    if (fu_status_table->log.dest_Fi == fjAtual)
      dependenciaQJ = LOG_FU_DECIMAL;

    if (fu_status_table->log.dest_Fi == fkAtual)
      dependenciaQK = LOG_FU_DECIMAL;
  }

  printf("\n--> dependencia QK: %d\n--> dependencia QJ: %d\n", dependenciaQK, dependenciaQJ);

  return dependenciaQK, dependenciaQJ;
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