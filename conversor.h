#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos_instrucoes/i_types.h"
#include "tipos_instrucoes/registers.h"

void converteOp();
void converteRs();
void converteRt();
void converteRd();
void converteShamt();
void converteFunct();
void converteImmediate();
void converteAddress();

void converte(char *arq, unsigned int array[], int tamanho)
{
    FILE *arqBase = fopen(arq, "r");
    int *ponteiro = array;
    unsigned int funct = 50; // 110010 exemplo

    char instruction[32];
    char *separators = " .,;'\n''\t''\r'";
    while (fgets(instruction, sizeof(instruction), arqBase) != NULL)
    {
        unsigned int encodedInstruction = 0;
        char *splitInstruction = strtok(instruction, separators);
        Instruction instructionType = getInstructionType(splitInstruction);
        unsigned int opcode = getOpcodeDecimal(splitInstruction);

        printf("%s é do tipo %s e seu código é %u\n", splitInstruction, instructionType == R ? "R" : "I", opcode);
        splitInstruction = strtok(NULL, separators);

        if (instructionType == R)
        {
            char *rdInstruction = splitInstruction;
            splitInstruction = strtok(NULL, separators);

            char *rsInstruction = splitInstruction;
            splitInstruction = strtok(NULL, separators);

            char *rtInstruction = splitInstruction;
            splitInstruction = strtok(NULL, separators);

            unsigned int rs = getRegisterDecimal(rsInstruction);
            unsigned int rt = getRegisterDecimal(rtInstruction);
            unsigned int rd = getRegisterDecimal(rdInstruction);

            converteOp(&encodedInstruction, 0);
            converteRs(&encodedInstruction, rs);
            converteRt(&encodedInstruction, rt);
            converteRd(&encodedInstruction, rd);
            converteShamt(&encodedInstruction, 0);
            converteFunct(&encodedInstruction, opcode);

            printf("Intruction Code rs: %i | rt: %i | rd: %i | funct: %i \n", rs, rt, rd, opcode);
            printf("Instruction: %i\n", encodedInstruction);
        }
        if (instructionType == I)
        {
            while (splitInstruction != NULL)
            {

                printf("tipo I: %s\n", splitInstruction);

                splitInstruction = strtok(NULL, separators);
            }
        }
        // converteFunct(&instrucao, funct);
    }

    fclose(arqBase);
}

int qtdInst(char *nameArquivo)
{
    int quantidade = 0;

    FILE *arquivo;
    arquivo = fopen(nameArquivo, "r");
    if (arquivo == NULL)
    {
        printf("%s Erro na abertura do arquivo ", nameArquivo);
        return -1;
    }

    char line[50]; // apenas para armazenamento previo
    while (fgets(line, sizeof(line), arquivo) != NULL)
    {
        //printf(line);
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}

void converteOp(unsigned int *inst, int atualizar)
{

    unsigned int real = 0;

    // OR entre a parte binario real e atualizar
    real = real | atualizar;
    // 6 opcode = 6 - 32 bits = 26 para o deslocamento
    real = real << 26;

    *inst = real;
}

void converteRs(unsigned int *inst, int atualizar)
{

    unsigned int real = *inst;

    real = real >> 26;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs = 11 pronto - 32 total = 21
    real = real << 21;

    *inst = real;
}

void converteRt(unsigned int *inst, int atualizar)
{

    unsigned int real = *inst;

    real = real >> 21;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt = 16 pronto - 32 total = 16
    real = real << 16;

    *inst = real;
}

void converteRd(unsigned int *inst, int atualizar)
{

    unsigned int real = *inst;

    real = real >> 16;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt + 5 rd = 21 pronto - 32 total = 11
    real = real << 11;

    *inst = real;
}

void converteShamt(unsigned int *inst, int atualizar)
{

    unsigned int real = *inst;

    real = real >> 11;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt + 5 rd + 5 = 26 pronto - 32 total = 6
    real = real << 6;

    *inst = real;
}

void converteFunct(unsigned int *inst, int atualizar)
{

    unsigned int real = *inst;

    real = real >> 6;
    real = real << 6;
    real = real | atualizar;

    *inst = real;
}

void converteImmediate(unsigned int *inst, int atualizar)
{

    unsigned int real = *inst;

    real = real >> 16;
    real = real << 16;
    real = real | atualizar;

    *inst = real;
}

void converteAddress(unsigned int *inst, int atualizar)
{

    unsigned int real = *inst;

    real = real >> 26;
    real = real << 26;
    real = real | atualizar;

    *inst = real;
}
