#include <stdio.h>
#include <stdlib.h>

void converteOp();
void converteRs();
void converteRt();
void converteRd();
void converteShamt();
void converteFunct();
void converteImmediate();
void converteAddress();


void converte(char *arq, unsigned int array[], int tamanho) {

    FILE *arqBase = fopen(arq, "r");
    int *ponteiro = array;
    unsigned int instrucao;
    unsigned int funct = 50; // 110010 exemplo

    char word[32];
    while(fgets(word, sizeof(word), arqBase) != NULL ){
        instrucao = 0;

        converteFunct(&instrucao, funct);
        *ponteiro = instrucao;
        
        ponteiro++;
    }
    
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

void converteOp(unsigned int *inst, int atualizar){

    unsigned int real = 0;

    // OR entre a parte binario real e atualizar
    real = real | atualizar;    
    // 6 opcode = 6 - 32 bits = 26 para o deslocamento
    real = real << 26;          

    *inst = real;
}

void converteRs(unsigned int *inst, int atualizar){

    unsigned int real = *inst;

    real = real >> 26;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs = 11 pronto - 32 total = 21
    real = real << 21;              

    *inst = real;
}

void converteRt(unsigned int *inst, int atualizar){

    unsigned int real = *inst;

    real = real >> 21;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt = 16 pronto - 32 total = 16
    real = real << 16;          
    
    *inst = real;
}

void converteRd(unsigned int *inst, int atualizar){

    unsigned int real = *inst;

    real = real >> 16;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt + 5 rd = 21 pronto - 32 total = 11
    real = real << 11;          
    
    *inst = real;
}

void converteShamt(unsigned int *inst, int atualizar){

    unsigned int real = *inst;

    real = real >> 11;
    real = real << 5;
    real = real | atualizar;
    // 6 do opcode + 5 rs + 5 rt + 5 rd + 5 = 26 pronto - 32 total = 6
    real = real << 6;         
    
    *inst = real;
}

void converteFunct(unsigned int *inst, int atualizar){

    unsigned int real = *inst;

    real = real >> 6;
    real = real << 6;
    real = real | atualizar;
 
    *inst = real;
}

void converteImmediate(unsigned int *inst, int atualizar){

    unsigned int real = *inst;

    real = real >> 16;
    real = real << 16;
    real = real | atualizar;
    
    *inst = real;
}

void converteAddress(unsigned int *inst, int atualizar){

    unsigned int real = *inst;

    real = real >> 26;
    real = real << 26;
    real = real | atualizar;
    
    *inst = real;
}
