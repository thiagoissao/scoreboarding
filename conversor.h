#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types/i_types.h"
#include "types/registers.h"

void converteOp();
void converteRs();
void converteRt();
void converteRd();
void converteShamt();
void converteFunct();
void converteAddress();
void converteImmediate();
int desconverteOp();
int desconverteRs();
int desconverteRt();
int desconverteRd();
int desconverteShamt();
int desconverteFunct();
int desconverteAddress();
int desconverteImmediate();

void converter(char *archive, unsigned int *instructionsSet)
{
    FILE *archiveFile = fopen(archive, "r");

    int count;
    count = 0;
    char instruction[32];
    char *separators = " .,;'\n''\t''\r'";
    while (fgets(instruction, sizeof(instruction), archiveFile) != NULL)
    {
        unsigned int encodedInstruction;
        encodedInstruction = 0;
        char *splitInstruction = strtok(instruction, separators);
        Instruction instructionType = getInstructionType(splitInstruction);
        unsigned int opcode = getOpcodeDecimal(splitInstruction);

        //printf("%s é do tipo %s e seu código é %u\n", splitInstruction, instructionType == R ? "R" : "I", opcode);
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

            //printf("Instruction: %i\n\n", encodedInstruction);
        }
        if (instructionType == I)
        {
            char *rsInstruction = splitInstruction;
            splitInstruction = strtok(NULL, separators);

            char *rtInstruction = splitInstruction;
            splitInstruction = strtok(NULL, separators);

            char *immediateInstruction = splitInstruction;
            splitInstruction = strtok(NULL, separators);

            unsigned int rs = getRegisterDecimal(rsInstruction);
            unsigned int rt = getRegisterDecimal(rtInstruction);
            unsigned int immediate = atoi(immediateInstruction);

            converteOp(&encodedInstruction, opcode);
            converteRs(&encodedInstruction, rs);
            converteRt(&encodedInstruction, rt);
            converteImmediate(&encodedInstruction, immediate);

            //printf("Instruction: %i\n\n", encodedInstruction);
        }
        instructionsSet[count] = encodedInstruction;
        count++;
    }

    fclose(archiveFile);
}

int getInstructionsQuantity(char *nameArquivo)
{
    int quantidade;
    quantidade = 0;

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
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}

void converteOp(unsigned int *inst, int atualizar)
{
    unsigned int real;
    real = 0;

    // OR entre a parte binario real e atualizar
    real = real | atualizar;
    // 6 opcode = 6 - 32 bits = 26 para o deslocamento
    real = real << 26;

    *inst = real;
}

void converteRs(unsigned int *inst, int atualizar)
{
    unsigned int real;
    real = *inst;

    real = real >> 26;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs = 11 pronto - 32 total = 21
    real = real << 21;

    *inst = real;
}

void converteRt(unsigned int *inst, int atualizar)
{
    unsigned int real;
    real = *inst;

    real = real >> 21;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt = 16 pronto - 32 total = 16
    real = real << 16;

    *inst = real;
}

void converteRd(unsigned int *inst, int atualizar)
{
    unsigned int real;
    real = *inst;

    real = real >> 16;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt + 5 rd = 21 pronto - 32 total = 11
    real = real << 11;

    *inst = real;
}

void converteShamt(unsigned int *inst, int atualizar)
{
    unsigned int real;
    real = *inst;

    real = real >> 11;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt + 5 rd + 5 = 26 pronto - 32 total = 6
    real = real << 6;

    *inst = real;
}

void converteFunct(unsigned int *inst, int atualizar)
{
    unsigned int real;
    real = *inst;

    real = real >> 6;
    real = real << 6;
    real = real | atualizar;

    *inst = real;
}

void converteAddress(unsigned int *inst, int atualizar)
{
    unsigned int real;
    real = *inst;

    real = real >> 26;
    real = real << 26;
    real = real | atualizar;

    *inst = real;
}

void converteImmediate(unsigned int *inst, int atualizar)
{
    unsigned int real;
    real = *inst;

    real = real >> 16;
    real = real << 16;
    real = real | atualizar;

    *inst = real;
}

int desconverteOp(unsigned int inst)
{
    return inst >> 26;
}

int desconverteRs(unsigned int inst)
{
    int real;

    inst = inst << 6;
    real = inst >> 27;

    return real;
}

int desconverteRt(unsigned int inst)
{
    int real;

    inst = inst << 11;
    real = inst >> 27;

    return real;
}

int desconverteRd(unsigned int inst)
{
    int real;

    inst = inst << 16;
    real = inst >> 27;

    return real;
}

int desconverteShamt(unsigned int inst)
{
    int real;

    inst = inst << 21;
    real = inst >> 27;

    return real;
}

int desconverteFunct(unsigned int inst)
{
    int real;

    inst = inst << 26;
    real = inst >> 26;

    return real;
}

int desconverteAddress(unsigned int inst)
{
    int real;

    inst = inst << 6;
    real = inst >> 6;

    return real;
}

int desconverteImmediate(unsigned int inst)
{
    int real;

    inst = inst << 16;
    real = inst >> 16;

    return real;
}

#endif
