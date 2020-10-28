//THIS FILE IS FOR TESTING ONLY
//IT IS NOT USED IN THE PROJECT

#include <stdio.h>
#include "functional_unit_status.h"
#include "instruction_status.h"
#include "register_result_status.h"
#include "units.h"
#include <stdbool.h>

void print_list_functional_unit(functional_unit_status_table_t *table)
{

  printf("\n====== functional_unit_status =======\n");
  printf("add -> busy: %s\n", table->add.busy ? "true" : "false");
  printf("addi -> busy: %s\n", table->andi.busy ? "true" : "false");
}

void print_list_instruction_status(instruction_status_linked_t *head)
{
  instruction_status_linked_t *current = head;

  printf("\n====== instruction_status =======\n");
  while (current != NULL)
  {
    printf("%d\n", current->instruction_status.issue);
    current = current->next;
  }
}

void print_list_register_result_status(register_result_status_linked_t *head)
{
  register_result_status_linked_t *current = head;

  printf("\n====== register_result_status =======\n");
  while (current != NULL)
  {
    printf("%d\n", current->register_result_status.a0);
    current = current->next;
  }
}

int main()
{
  functional_unit_status_table_t *fu_table = (functional_unit_status_table_t *)malloc(sizeof(functional_unit_status_table_t));

  //atualiza add
  fu_table->add.busy = false;
  fu_table->add.dest_Fi = 9;
  fu_table->add.fj_Rj = false;
  fu_table->add.fj_Rk = false;
  fu_table->add.fu_Qj = mult1;
  fu_table->add.fu_Qk = mult2;
  fu_table->add.name = mult1;
  fu_table->add.op = 0;
  fu_table->add.s1_Fj = 0;
  fu_table->add.s2_Fk = 8;
  fu_table->add.time = 9;

  //atualiza andi
  fu_table->andi.busy = true;
  fu_table->andi.dest_Fi = 10;
  fu_table->andi.fj_Rj = false;
  fu_table->andi.fj_Rk = false;
  fu_table->andi.fu_Qj = mult1;
  fu_table->andi.fu_Qk = mult2;
  fu_table->andi.name = mult1;
  fu_table->andi.op = 0;
  fu_table->andi.s1_Fj = 0;
  fu_table->andi.s2_Fk = 8;
  fu_table->andi.time = 10;

  print_list_functional_unit(fu_table);

  instruction_status_linked_t *head2 = (instruction_status_linked_t *)malloc(sizeof(instruction_status_linked_t));
  head2->instruction_status.issue = 1;

  instruction_status_t instr_s;
  instr_s.issue = 2;

  push_instruction_status(head2, instr_s);

  print_list_instruction_status(head2);

  register_result_status_linked_t *head3 = (register_result_status_linked_t *)malloc(sizeof(register_result_status_linked_t));
  head3->register_result_status.a0 = 0;

  register_result_status_t reg_res;
  reg_res.a0 = 1;

  push_register_result_status(head3, reg_res);

  print_list_register_result_status(head3);

  free(fu_table);
  free(head2);
  free(head3);
  return 0;
}
