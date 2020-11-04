#include <stdio.h>
#include "../unidades_funcionais/instruction_status.h"
#include "../unidades_funcionais/functional_unit_status.h"
#include "./prints.h"
#include <stdlib.h>

int main()
{
  int size = 10, i;
  instruction_status_t inst_table[size];

  for (i = 0; i < size / 2; i++)
  {
    inst_table[i].instruction = 18124824; //ADDI $t0, $t1, 2
    inst_table[i].issue = 0;
    inst_table[i].readOperand = 1;
    inst_table[i].execComp = 2;
    inst_table[i].writeResult = 4;
  }
  for (i = 5; i < size; i++)
  {
    inst_table[i].instruction = 554237954; //ADDI $t0, $t1, 2
    inst_table[i].issue = 5;
    inst_table[i].readOperand = 33;
    inst_table[i].execComp = 22;
    inst_table[i].writeResult = 100;
  }

  functional_unit_status_table_t *fu_status_table = (functional_unit_status_table_t *)malloc(sizeof(functional_unit_status_table_t));
  init_functional_unit_status_table(fu_status_table);

  print_instructions_complete(inst_table, size);
  // print_functional_unit(fu_status_table);
  return 0;
}
