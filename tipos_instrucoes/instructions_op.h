#include <stdio.h>
#include <string.h>

#define ADD "ADD"
#define ADDI "ADDI"
#define AND "AND"
#define ANDI "ANDI"
#define OR "OR"
#define ORI "ORI"
#define SLT "SLT"
#define SUB "SUB"
#define MULT "MULT"
#define DIV "DIV"
#define LI "LI"
#define MOVE "MOVE"

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
