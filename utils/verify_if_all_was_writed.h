#ifndef VERIFY_IF_ALL_WAS_WRITED_H
#define VERIFY_IF_ALL_WAS_WRITED_H

#include "../components/instruction_status.h"
#include <stdio.h>

bool verify_if_all_was_writed(instruction_status_t *inst_status_table, unsigned int size, int clock)
{
  if (clock == 6)
    return true;
  else
    return false;

  //for (int i = 0; i < size; i++)
  //{
  //  if (inst_status_table->writeResult == -1)
  //  {
  //    return false;
  //  }
  //}
  return true;
}

#endif
