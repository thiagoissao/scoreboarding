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
#define LW "lw"

int getInstructionDecimal(char *opcode)
{
    if (strcmp(opcode, ADD) == 0)
        return 32;
    if (strcmp(opcode, ADDI) == 0)
        return 8;
    if (strcmp(opcode, AND) == 0)
        return 36;
    if (strcmp(opcode, ANDI) == 0)
        return 12;
    if (strcmp(opcode, OR) == 0)
        return 37;
    if (strcmp(opcode, ORI) == 0)
        return 13;
    if (strcmp(opcode, SLT) == 0)
        return 42;
    if (strcmp(opcode, SUB) == 0)
        return 34;
    if (strcmp(opcode, MULT) == 0)
        return 24;
    if (strcmp(opcode, DIV) == 0)
        return 26;
    if (strcmp(opcode, LW) == 0)
        return 35;
    return -1;
}
