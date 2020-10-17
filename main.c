#include <stdio.h>
#include <unistd.h>
#include "conversor.h"

#include <assert.h>     // p teste

// processo de abrir o arquivo tudo bonitin
// ignorei p ja abrir de um direto e ae ja focarmos logo nas etapas dele
int main(){
    char *arq = "mnemonios.txt";
    char *destino = "destino.txt";
    
    int qtdInstrucao;

    qtdInstrucao = qtdInst(arq);
    assert(qtdInstrucao == 3);

    //converte(arq, destino);

    return 0;
}