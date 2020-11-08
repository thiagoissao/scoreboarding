#include <stdio.h>
#include "../components/register_database.h"
#include "../types/instructions_op.h"
#include "./operations.h"
#include "../prints/prints.h"

int main()
{
  register_database_t *database = (register_database_t *)malloc(sizeof(register_database_t));

  unsigned int instructions_set[15] = {
      1912602624, //LI $s0, 0
      1916796929, //LI $s2, 1
      1918894083, //LI $s3, 3
      1920991236, //LI $s4, 4
      1895825408, //LI $t0, 0
      1897922561, //LI $t1, 1
      1900019714, //LI $t2, 2
      1902116867, //LI $t3, 3
      18915358,   //MOVE $s4, $t1
      554237954,  //ADDI $t0, $t1, 2
      18106392,   //MULT $t1, $t0, $s4
      43165720,   //MULT $s5, $s4, $s2
      67000346,   //DIV $t3, $ra, $fp
      560594994,  //ADDI $t3, $t2, 50
      41189408    //ADD $s0, $s3, $s4
  };

  operation_li(1912602624, database);
  operation_li(1916796929, database);
  operation_li(1918894083, database);
  operation_li(1920991236, database);
  operation_li(1895825408, database);
  operation_li(1897922561, database);
  operation_li(1900019714, database);
  operation_li(1902116867, database);
  operation_move(18915358, database);  //s4 = 1
  operation_addi(554237954, database); //t0 = 3
  operation_mult(18106392, database);  //t1 = 3
  operation_mult(43165720, database);  //s5 = 1 * 1 = 1
  // operation_div(67000346, database);
  operation_addi(560594994, database); // t3 = 52
  operation_add(41189408, database);   // s0 = 4

  print_register_database(database);
}
