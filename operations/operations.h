#include <stdio.h>
#include "../components/register_database.h"
#include "../types/instructions_op.h"
#include "../conversor.h"
#include "../utils/utils.h"
#include "../types/registers.h"

void operation_add(unsigned int instruction, register_database_t *db);
void operation_addi(unsigned int instruction, register_database_t *db);
void operation_and(unsigned int instruction, register_database_t *db);
void operation_andi(unsigned int instruction, register_database_t *db);
void operation_or(unsigned int instruction, register_database_t *db);
void operation_ori(unsigned int instruction, register_database_t *db);
void operation_slt(unsigned int instruction, register_database_t *db);
void operation_sub(unsigned int instruction, register_database_t *db);
void operation_mult(unsigned int instruction, register_database_t *db);
void operation_div(unsigned int instruction, register_database_t *db);
void operation_li(unsigned int instruction, register_database_t *db);
void operation_move(unsigned int instruction, register_database_t *db);

void update_register_database(unsigned int opcode, unsigned int instruction, register_database_t *db)
{
  switch (opcode)
  {
  case ADD_DECIMAL:
    operation_add(instruction, db);
    break;

  case ADDI_DECIMAL:
    operation_addi(instruction, db);
    break;

  case AND_DECIMAL:
    operation_and(instruction, db);
    break;

  case ANDI_DECIMAL:
    operation_andi(instruction, db);
    break;

  case OR_DECIMAL:
    operation_or(instruction, db);
    break;

  case ORI_DECIMAL:
    operation_ori(instruction, db);
    break;

  case SLT_DECIMAL:
    operation_slt(instruction, db);
    break;

  case SUB_DECIMAL:
    operation_sub(instruction, db);
    break;

  case MULT_DECIMAL:
    operation_mult(instruction, db);
    break;

  case DIV_DECIMAL:
    operation_div(instruction, db);
    break;

  case LI_DECIMAL:
    operation_li(instruction, db);
    break;

  case MOVE_DECIMAL:
    operation_move(instruction, db);
    break;

  default:
    break;
  }
}

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
  unsigned int rs = desconverteRs(instruction);
  unsigned int rt = desconverteRt(instruction);
  unsigned int rd = desconverteRd(instruction);

  int slt = getRegisterValueFromDatabase(db, rs) < getRegisterValueFromDatabase(db, rt);
  setValueToRegisterDatabase(db, rd, slt);
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
