#include <stdio.h>

int logicas(char op[]){
    switch (op)
    {
    case 'ADD':
        return 10;// o numero dele e tal sla
    case 'SUB':
        return 5;
    //...
    default:
        return -1;
    }
}