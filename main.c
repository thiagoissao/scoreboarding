#include <stdio.h>
#include <unistd.h>
#include "conversor.h"

#include <assert.h>     // p teste

typedef struct instruction{
    unsigned int opcode:5;
    unsigned int destino:3;
    unsigned int arg1:3;
    unsigned int arg2:3;
}instruction_t;


// processo de abrir o arquivo tudo bonitin
// ignorei p ja abrir de um direto e ae ja focarmos logo nas etapas dele
int main(){
    char *arq = "mnemonios.txt";
 
    int qtdInstrucao;

    qtdInstrucao = qtdInst(arq);
    assert(qtdInstrucao == 3);

    // cria na memoria do tamanho das instruções com a struct
    instruction_t instrucao[qtdInstrucao];

    instrucao[1].opcode = 0x12;     //  1 e 2  ->   0001.0010  -> 18 
    instrucao[2].opcode = 0x05;     //  1 e 2  ->   0000.0101  -> 5
    printf("%d %d\n%d %d\n", instrucao[1].opcode, instrucao[1].destino, instrucao[2].opcode, instrucao[2].arg1);
    
    //converte(arq, destino);

    return 0;
}




/*
* - main.c  => Controla o scoreboarding, aqui são utilizadas todas as structs, conversões, etc.
* - conversor.h => ler o arquivo de instrucoes e salvar na memória, porém o papel de salvar na memória deve ser atribuida a main.c. Então a ideia para o conversor.h é receber valores e devolver esses valores prontos.
* - Cada "tabela" do scoreboarding deve ser separado em arquivos diferentes para facilitar a leitura posteriormente, organizar cada "tabela" em structs e construir funcões auxiliares para cada tipo de processamento. Lembrando que quem deve utilizar essas structs e funcões auxiliares é a main.c
* - Existe um arquivo chamado processador.c. Seu papel é organizar essas "tabelas" de forma que eles trabalhem em sintonia. Acho que uma forma legal de arquiteturar esse arquivo é criar métodos para a main.c, pois dessa forma toda a lógica de execucão fica por conta da main. Por exemplo, a instrucão atual é um ADD, então o processador.c deve possuir uma funcão de ADD.
*    Sugestão de uso: 
*      ENQUANTO existir instrucões FACA
*         INTRUCAO_ATUAL = INSTRUCOES[i]
*         SE INSTRUCAO_ATUAL === ADD ENTAO
*            processador.add(INSTRUCAO_ATUAL)
*         SE INSTRUCAO_ATUAL === MUL ENTAO
*            processador.mul(INSTRUCAO_ATUAL)
*          ....
*/