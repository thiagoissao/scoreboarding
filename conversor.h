#include <stdio.h>

void converte(char *nomeArquivo) {}

int qtdInst(char *nomeArquivo){
    int quantidade = 0;

    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL){
        printf("Erro na abertura do arquivo ", nomeArquivo);
        return -1;
    }

    char line[50];  // apenas para armazenamento previo
    while(fgets(line, sizeof(line), arquivo) != NULL) {
        //printf(line);
        quantidade++;
    }


    fclose(arquivo);
    return quantidade;
}