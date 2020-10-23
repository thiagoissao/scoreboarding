#include <stdio.h>

int logicas(char op[])
{
    switch (op)
    {
    case 'ADD':
        return 32;
    case 'ADDI':
        return 8;
    case 'AND':
        return 36;
    case 'ANDI':
        return 12;
    case 'OR':
        return 37;
    case 'ORI':
        return 13;
    case 'SLT':
        return 42;
    case 'SUB':
        return 34;
    case 'MULT':
        return 24;
    case 'DIV':
        return 26;
    case 'LW':
        return 35;
    default:
        return -1;
    }
}
