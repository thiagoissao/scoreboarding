#include <stdio.h>
#include <unistd.h>
#include "conversor.h"

// processo de abrir o arquivo tudo bonitin
// ignorei p ja abrir de um direto e ae ja focarmos logo nas etapas dele
int main(){
    int qtdInstrucao;

    qtdInstrucao = qtdInst("mnemonios.txt");
    printf("%d", qtdInstrucao);

    
    return 0;
}