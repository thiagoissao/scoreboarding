//THIS FILE IS FOR TESTING ONLY
//IT IS NOT USED IN THE PROJECT

#include <stdio.h>
#include "functional_unit_status.h"
#include "instruction_status.h"
#include "register_result_status.h"
#include "units.h"

void print_list_functional_unit(functional_unit_status_linked_t *head)
{
  functional_unit_status_linked_t *current = head;

  printf("\n====== functional_unit_status =======\n");
  while (current != NULL)
  {
    printf("%d\n", current->functional_unit_status.time);
    printf("%d\n", current->functional_unit_status.dest_Fi);
    current = current->next;
  }
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
  functional_unit_status_linked_t *head = (functional_unit_status_linked_t *)malloc(sizeof(functional_unit_status_linked_t));

  head->functional_unit_status.busy = false;
  head->functional_unit_status.dest_Fi = 9;
  head->functional_unit_status.fj_Rj = false;
  head->functional_unit_status.fj_Rk = false;
  head->functional_unit_status.fu_Qj = mult1;
  head->functional_unit_status.fu_Qk = mult2;
  head->functional_unit_status.name = mult1;
  head->functional_unit_status.op = 0;
  head->functional_unit_status.s1_Fj = 0;
  head->functional_unit_status.s2_Fk = 8;
  head->functional_unit_status.time = 9;

  functional_unit_status_t fu;

  fu.busy = false;
  fu.dest_Fi = 10;
  fu.fj_Rj = false;
  fu.fj_Rk = false;
  fu.fu_Qj = mult1;
  fu.fu_Qk = mult2;
  fu.name = mult1;
  fu.op = 0;
  fu.s1_Fj = 0;
  fu.s2_Fk = 8;
  fu.time = 10;

  push_functional_unit_status(head, fu);

  fu.busy = false;
  fu.dest_Fi = 11;
  fu.fj_Rj = false;
  fu.fj_Rk = false;
  fu.fu_Qj = mult1;
  fu.fu_Qk = mult2;
  fu.name = add;
  fu.op = 0;
  fu.s1_Fj = 0;
  fu.s2_Fk = 8;
  fu.time = 11;

  push_functional_unit_status(head, fu);

  print_list_functional_unit(head);

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

  free(head);
  free(head2);
  free(head3);
  return 0;
}
