#include <stdio.h>

void converte(char *arq, char *newArquivo) {
    FILE *arqBase = fopen(arq, "r");
    FILE *arqDest = fopen(newArquivo, "w");

    char word[5]; // sizeoff dele é 7, num parece ser certo haushas
    
    //while(fgets(word, sizeof(word), arqBase) != NULL ){

    //}
    
    
    fclose(arqBase);
    fclose(arqDest);
}


int qtdInst(char *nameArquivo){
    int quantidade = 0;

    FILE *arquivo;
    arquivo = fopen(nameArquivo, "r");
    if (arquivo == NULL){
        printf("Erro na abertura do arquivo ", nameArquivo);
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