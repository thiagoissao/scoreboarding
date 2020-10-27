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

unsigned int getOpcodeDecimal(char *opcode)
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
    if (strcmp(opcode, LI) == 0)
        return 0; //ajustar
    if (strcmp(opcode, MOVE) == 0)
        return 0; //ajustar
    return -1;
}
