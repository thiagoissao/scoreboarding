#ifndef VERIFICATIONS_H
#define VERIFICATIONS_H

#include <stdio.h>
#include <stdbool.h>
#include "../components/instruction_status.h"
#include "../components/functional_unit_status.h"
#include "../components/units.h"
#include "../types/instructions_op.h"

bool verify_if_all_was_writed(instruction_status_t *inst_status_table, unsigned int size, int clock)
{
  for (int i = 0; i < size; i++)
  {
    if (inst_status_table[i].writeResult == -1)
    {
      return false;
    }
  }
  return true;
}

void verify_dependency(functional_unit_status_table_t *fu_status_table, UnitInstruction_t typeOp,
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

bool verifyIsRead(instruction_status_t *inst_status_table, UnitInstruction_t typeOp, UnitInstruction_t typeOpComp,
  unsigned int Fi, bool isFj, int instMaxima, bool *nextStepRead)
{
  int i;
  unsigned int comparaF, opcode, funct;
  UnitInstruction_t typeOpInst;
  functional_unit_status_table_t *fu_status_table;

  for (i=0; i<instMaxima;i++){ // percorre todas inst ate achar a q tem bateu as dependencias
    opcode = desconverteOp(inst_status_table[i].instruction);
    
    if(opcode == R) {
      funct = desconverteFunct(inst_status_table[i].instruction);
      typeOpInst = getTypeOp(funct, fu_status_table);
      if(isFj)
        comparaF = desconverteRs(inst_status_table[i].instruction);
      else
        comparaF = desconverteRt(inst_status_table[i].instruction);
    }
    else{ 
      comparaF = desconverteRt(inst_status_table[i].instruction);
      typeOpInst = getTypeOp(opcode, fu_status_table); //nem ta usando o fu na funcao
    }

    // se (Fj ou Fk == Destino Fi) && (mesmo tipo da dependencia) && (diferente de ser ele mesmo)
    if((comparaF == Fi) && (typeOpInst == typeOp) && (typeOpInst != typeOpComp)){

      if (inst_status_table[i].readOperand == -1) // se ainda nao passou pelo read
        return true;  
      
      if (!nextStepRead[i])           // se ele nao passou nesse ciclo no read
        return true;                                       

      
      return false;                 // se n ta top pra seguir
    }
    
  }  
  return false; // creio q n chega aq mas deixei
}

bool verify_raw(instruction_status_t *inst_status_table, functional_unit_status_table_t *fu_status_table, 
    UnitInstruction_t typeOp, bool *nextStepRead, int instAtual)
{
  unsigned int Fi, idComparacao;
  Fi = getReadFi(fu_status_table, typeOp);
  bool aux = false;
  
  
  if (fu_status_table->mult1.busy && typeOp != mult1){
    // se (FJ == FI) && RJ -> se FK ==FI entao o RJ tem q ta YES pra ser um RAW) entao verifica o read p ter as decisoes
    if (fu_status_table->mult1.s1_Fj == Fi && fu_status_table->mult1.fj_Rj){
      aux = verifyIsRead(inst_status_table, mult1, typeOp, Fi, true, instAtual, nextStepRead);
    }
    // se (FK == FI) && RJ -> se FK ==FI entao o RK tem q ta YES pra ser um RAW)
    else if(fu_status_table->mult1.s2_Fk == Fi && fu_status_table->mult1.fj_Rk){
      aux = verifyIsRead(inst_status_table, mult1, typeOp, Fi, false, instAtual, nextStepRead);
    }
    if (aux) 
      return false;
  }
  if (fu_status_table->mult2.busy && typeOp != mult2){
    if (fu_status_table->mult2.s1_Fj == Fi && fu_status_table->mult2.fj_Rj){
      aux = verifyIsRead(inst_status_table, mult2, typeOp, Fi, true, instAtual, nextStepRead);
    }
    else if(fu_status_table->mult2.s2_Fk == Fi && fu_status_table->mult2.fj_Rk){
      aux = verifyIsRead(inst_status_table, mult2, typeOp, Fi, false, instAtual, nextStepRead);
    }
    if (aux) 
      return false;
  }
  if (fu_status_table->add.busy && typeOp != add){
    if (fu_status_table->add.s1_Fj == Fi && fu_status_table->add.fj_Rj){
      aux = verifyIsRead(inst_status_table, add, typeOp, Fi, true, instAtual, nextStepRead);
    }
    else if(fu_status_table->add.s2_Fk == Fi && fu_status_table->add.fj_Rk){
      aux = verifyIsRead(inst_status_table, add, typeOp, Fi, false, instAtual, nextStepRead);
    }
    if (aux) 
      return false;
  }
  if (fu_status_table->divide.busy && typeOp != divide){
    if (fu_status_table->divide.s1_Fj == Fi && fu_status_table->divide.fj_Rj){
      aux = verifyIsRead(inst_status_table, divide, typeOp, Fi, true, instAtual, nextStepRead);
    }
    else if(fu_status_table->divide.s2_Fk == Fi && fu_status_table->divide.fj_Rk){
      aux = verifyIsRead(inst_status_table, divide, typeOp, Fi, true, instAtual, nextStepRead);
    }
    if (aux) 
      return false;
  }
  if (fu_status_table->log.busy && typeOp != log){
    if (fu_status_table->log.s1_Fj == Fi && fu_status_table->log.fj_Rj){
      aux = verifyIsRead(inst_status_table, log, typeOp, Fi, true, instAtual, nextStepRead);
    }
    else if(fu_status_table->log.s2_Fk == Fi && fu_status_table->log.fj_Rk){
      aux = verifyIsRead(inst_status_table, log, typeOp, Fi, true, instAtual, nextStepRead);
    }
    if (aux) 
      return false;
  }
  // SE (ta ocupado  &&  diferente do FU dele  && ( (Destino Fi == Fj && dependencia Rj) OU
  //                                                (Destino Fi == Fk && dependencia Rk)  ))
  //                                              se tem dependencia R siginica que a instrucao
  //                                                       do write ta antes das inst de dependencias
  //  ae se entrar quer dizer que nao pode proceguir pra write

  return true;
}

#endif
