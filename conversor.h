#include <stdio.h>
#include <stdlib.h>


int converteArq(char *arq, char *destino){
//    FILE *arqBase = fopen(arq, "r");
//    FILE *arqDest = fopen(arq, "w");
}

void converte(char *arq, unsigned long int array[], int tamanho) {

    FILE *arqBase = fopen(arq, "r");
    long int *ponteiro = array;

    char word[32];
    while(fgets(word, sizeof(word), arqBase) != NULL ){

        // funcao p prepara a instrucao (word) pra escrever no array (com o ponteiro)
        //*ponteiro = ;
        
        ponteiro++;
    }

    /* leve teste d como funciona no array
      *ponteiro = 1232;
      ponteiro++;
      *ponteiro = 45432;
      ponteiro++;
      *ponteiro = 8768667;
    */
    
    fclose(arqBase);
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