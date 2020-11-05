#ifndef CONFIG_CONVERTER_H
#define CONFIG_CONVERTER_H

#include <stdio.h>

int count_configs(char *path)
{
  int count = 0;
  char line[32];
  FILE *archive = fopen(path, "r");

  while (fgets(line, sizeof(line), archive) != NULL)
  {
    count = count + 1;
  }

  fclose(archive);
  return count;
}

#endif
