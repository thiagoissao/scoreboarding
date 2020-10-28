#include <stdio.h>
#include "functional_unit_status.h"
#include "units.h"

void print_list(functional_unit_status_linked_t *head)
{
  functional_unit_status_linked_t *current = head;

  while (current != NULL)
  {
    printf("%d\n", current->functional_unit_status.time);
    printf("%d\n", current->functional_unit_status.dest_Fi);
    current = current->next;
  }
}

int main()
{
  functional_unit_status_linked_t *head = NULL;
  head->functional_unit_status.busy = false;
  head->next = NULL;
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

  // fu.busy = false;
  // fu.dest_Fi = 11;
  // fu.fj_Rj = false;
  // fu.fj_Rk = false;
  // fu.fu_Qj = mult1;
  // fu.fu_Qk = mult2;
  // fu.name = add;
  // fu.op = 0;
  // fu.s1_Fj = 0;
  // fu.s2_Fk = 8;
  // fu.time = 11;

  // push_functional_unit_status(head, fu);

  print_list(head);
  free(head);
  return 0;
}
