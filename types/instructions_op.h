#ifndef INSTRUCTIONS_OP_H
#define INSTRUCTIONS_OP_H

#include <stdio.h>
#include <string.h>

#define ADD "add"
#define ADDI "addi"
#define AND "and"
#define ANDI "andi"
#define OR "or"
#define ORI "ori"
#define SLT "slt"
#define SUB "sub"
#define MULT "mult"
#define DIV "div"
#define LI "li"
#define MOVE "move"

#define EMPTY_FU_DECIMAL -1
#define MULT1_FU_DECIMAL 0
#define MULT2_FU_DECIMAL 1
#define ADD_FU_DECIMAL 2
#define DIVIDE_FU_DECIMAL 3
#define LOG_FU_DECIMAL 4

#define ADD_DECIMAL 32
#define ADDI_DECIMAL 8
#define AND_DECIMAL 36
#define ANDI_DECIMAL 12
#define OR_DECIMAL 37
#define ORI_DECIMAL 13
#define SLT_DECIMAL 42
#define SUB_DECIMAL 34
#define MULT_DECIMAL 24
#define DIV_DECIMAL 26
#define LI_DECIMAL 28   //EXPLICAR NO RELATÓRIO
#define MOVE_DECIMAL 30 //EXPLICAR NO RELATÓRIO

char *opcodeToString(unsigned int opcode)
{
    if (opcode == ADD_DECIMAL)
        return ADD;
    if (opcode == ADDI_DECIMAL)
        return ADDI;
    if (opcode == AND_DECIMAL)
        return AND;
    if (opcode == ANDI_DECIMAL)
        return ANDI;
    if (opcode == OR_DECIMAL)
        return OR;
    if (opcode == ORI_DECIMAL)
        return ORI;
    if (opcode == SLT_DECIMAL)
        return SLT;
    if (opcode == SUB_DECIMAL)
        return SUB;
    if (opcode == MULT_DECIMAL)
        return MULT;
    if (opcode == DIV_DECIMAL)
        return DIV;
    if (opcode == LI_DECIMAL)
        return LI;
    if (opcode == MOVE_DECIMAL)
        return MOVE;
    return "";
}

unsigned int getOpcodeDecimal(char *opcode)
{
    if (strcmp(opcode, ADD) == 0)
        return ADD_DECIMAL;
    if (strcmp(opcode, ADDI) == 0)
        return ADDI_DECIMAL;
    if (strcmp(opcode, AND) == 0)
        return AND_DECIMAL;
    if (strcmp(opcode, ANDI) == 0)
        return ANDI_DECIMAL;
    if (strcmp(opcode, OR) == 0)
        return OR_DECIMAL;
    if (strcmp(opcode, ORI) == 0)
        return ORI_DECIMAL;
    if (strcmp(opcode, SLT) == 0)
        return SLT_DECIMAL;
    if (strcmp(opcode, SUB) == 0)
        return SUB_DECIMAL;
    if (strcmp(opcode, MULT) == 0)
        return MULT_DECIMAL;
    if (strcmp(opcode, DIV) == 0)
        return DIV_DECIMAL;
    if (strcmp(opcode, LI) == 0)
        return LI_DECIMAL;
    if (strcmp(opcode, MOVE) == 0)
        return MOVE_DECIMAL;
    return -1;
}

#endif
