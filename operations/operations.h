#include <stdio.h>
#include "../components/register_database.h"
#include "../types/instructions_op.h"
#include "../conversor.h"
#include "../utils/validations.h"
#include "../types/registers.h"

void operation_add(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int rd = desconverteRd(instruction);

  int sum = getRegisterValueFromDatabase(db, rs) + getRegisterValueFromDatabase(db, rt);
  setValueToRegisterDatabase(db, rd, sum);
}

void operation_addi(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int immediate = desconverteImmediate(instruction);

  int sum = getRegisterValueFromDatabase(db, rt) + immediate;
  setValueToRegisterDatabase(db, rs, sum);
}

void operation_and(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int rd = desconverteRd(instruction);

  int and = getRegisterValueFromDatabase(db, rs) & getRegisterValueFromDatabase(db, rt);
  setValueToRegisterDatabase(db, rd, and);
}

void operation_andi(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int immediate = desconverteImmediate(instruction);

  int andi = getRegisterValueFromDatabase(db, rt) & immediate;
  setValueToRegisterDatabase(db, rs, andi);
}

void operation_or(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int rd = desconverteRd(instruction);

  int or = getRegisterValueFromDatabase(db, rs) | getRegisterValueFromDatabase(db, rt);
  setValueToRegisterDatabase(db, rd, or);
}

void operation_ori(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int immediate = desconverteImmediate(instruction);

  int ori = getRegisterValueFromDatabase(db, rt) | immediate;
  setValueToRegisterDatabase(db, rs, ori);
}

void operation_slt(unsigned int instruction, register_database_t *db)
{
  //DO OR NOT DO SLT INSTRUCTION ?
}

void operation_sub(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int rd = desconverteRd(instruction);

  int sub = getRegisterValueFromDatabase(db, rs) - getRegisterValueFromDatabase(db, rt);
  setValueToRegisterDatabase(db, rd, sub);
}

void operation_mult(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int rd = desconverteRd(instruction);

  int mult = getRegisterValueFromDatabase(db, rs) * getRegisterValueFromDatabase(db, rt);
  setValueToRegisterDatabase(db, rd, mult);
}

void operation_div(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int rd = desconverteRd(instruction);

  int denominator = getRegisterValueFromDatabase(db, rt);

  if (denominator != 0)
  {
    int divide = getRegisterValueFromDatabase(db, rs) / denominator;
    setValueToRegisterDatabase(db, rd, divide);
  }

  printf("Divisão por zero na operação %i\n", instruction);
}

void operation_li(unsigned int instruction, register_database_t *db)
{
  unsigned int immediate = desconverteImmediate(instruction);
  unsigned int rs = desconverteRs(instruction);

  setValueToRegisterDatabase(db, rs, immediate);
}

void operation_move(unsigned int instruction, register_database_t *db)
{
  unsigned int rs = desconverteRs(instruction);
  unsigned int rd = desconverteRd(instruction);

  int move = getRegisterValueFromDatabase(db, rs);
  setValueToRegisterDatabase(db, rd, move);
}