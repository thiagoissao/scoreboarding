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

#define zero_reg "zero"
#define at_reg "at"
#define v0_reg "v0"
#define v1_reg "v1"
#define a0_reg "a0"
#define a1_reg "a1"
#define a2_reg "a2"
#define a3_reg "a3"
#define t0_reg "t0"
#define t1_reg "t1"
#define t2_reg "t2"
#define t3_reg "t3"
#define t4_reg "t4"
#define t5_reg "t5"
#define t6_reg "t6"
#define t7_reg "t7"
#define s0_reg "s0"
#define s1_reg "s1"
#define s2_reg "s2"
#define s3_reg "s3"
#define s4_reg "s4"
#define s5_reg "s5"
#define s6_reg "s6"
#define s7_reg "s7"
#define t8_reg "t8"
#define t9_reg "t9"
#define k0_reg "k0"
#define k1_reg "k1"
#define gp_reg "gp"
#define sp_reg "sp"
#define fp_reg "fp"
#define ra_reg "ra"

#define zero_dec 0
#define at_dec 1
#define v0_dec 2
#define v1_dec 3
#define a0_dec 4
#define a1_dec 5
#define a2_dec 6
#define a3_dec 7
#define t0_dec 8
#define t1_dec 9
#define t2_dec 10
#define t3_dec 11
#define t4_dec 12
#define t5_dec 13
#define t6_dec 14
#define t7_dec 15
#define s0_dec 16
#define s1_dec 17
#define s2_dec 18
#define s3_dec 19
#define s4_dec 20
#define s5_dec 21
#define s6_dec 22
#define s7_dec 23
#define t8_dec 24
#define t9_dec 25
#define k0_dec 26
#define k1_dec 27
#define gp_dec 28
#define sp_dec 29
#define fp_dec 30
#define ra_dec 31

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
