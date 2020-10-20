#include <stdio.h>
#include <unistd.h>
#include "../tipos_instrucoes/instructions_set.h"

typedef struct functional_unit_status
{
  int time;
  instructions_set name;
  bool busy;
  unsigned int op : 6;
  unsigned int dest_Fi : 5;
  unsigned int s1_Fj : 5;
  unsigned int s2_Fk : 5;
  instructions_set fu_Qj;
  instructions_set fu_Qk;
  bool fj_Rj;
  bool fj_Rk;
} instruction_status_t;
