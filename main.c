#include <stdio.h>
#include <unistd.h>
#include "conversor.h"

#include <assert.h>

// processo de abrir o arquivo tudo bonitin
// ignorei p ja abrir de um direto e ae ja focarmos logo nas etapas dele
int main()
{
    char *arq = "mnemonios.txt";

    int numberOfInstructions = qtdInst(arq);
    assert(numberOfInstructions == 4);

    // cria na memoria do tamanho das instruções com a struct
    unsigned int instructionSet[numberOfInstructions];

    // recebe as intruções no numero d 32 bit
    converte(arq, instructionSet, numberOfInstructions);

    printf("\nArray: \n");
    for (int i = 0; i < numberOfInstructions; i++)
    {
        printf("%d\n", instructionSet[i]);
    }

    // maximo 32 bit = 4.294.967.295 'em tese' pq o ultimo bit..
    // 0100000000000000000000000000000 - > 536870912

    // TESTE =)
    unsigned int t2 = 0;

    unsigned int op = 16;    // 010000  010000.11111.01111.01011.01010.110010
    unsigned int rs = 31;    // 11111
    unsigned int rt = 15;    // 01111
    unsigned int rd = 11;    // 01011
    unsigned int shamt = 10; // 01010
    unsigned int funct = 50; // 110010

    converteOp(&t2, op);
    printf("Op: %d\n", t2);

    converteRs(&t2, rs);
    printf("Rs: %d\n", t2);

    converteRt(&t2, rt);
    printf("\nPos RT: %d", t2);

    converteRd(&t2, rd);
    // pos: 01000000011011110101100000000000 = 275732480
    printf("\nPos RD: %d", t2);

    converteShamt(&t2, shamt);
    converteFunct(&t2, funct);

    printf("\nFIM: %d", t2);
    //fim: 01000011111011110101101010110010 = 275733170 = 010000.00011.01111.01011.01010.110010
    //                                         deveria:   010000.11111.01111.01011.01010.110010

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
