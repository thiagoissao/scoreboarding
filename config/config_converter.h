#ifndef CONFIG_CONVERTER_H
#define CONFIG_CONVERTER_H

#include <stdio.h>
#include <string.h>
#include "config.h"

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

void config_converter(char *path, config_t *config)
{
  FILE *archive = fopen(path, "r");
  char line[32];
  char *separators = "=' ''\t'";
  int count = 0;

  while (fgets(line, sizeof(line), archive) != NULL)
  {
    char *name = strtok(line, separators);
    char *charValue = strtok(NULL, separators);
    int value = strtol(charValue, NULL, 10);
    config[count].name = name;
    config[count].value = value;
    count++;
  }

  fclose(archive);
}
#endif
