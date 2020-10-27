#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "conversor.h"

int main()
{
    char *archive = "mnemonios.txt";

    //Quantidade de instruções no programa
    int numberOfInstructions = getInstructionsQuantity(archive);
    assert(numberOfInstructions == 4);

    // Cria na memória um array com o inteiro de cada instrução
    unsigned int instructionSet[numberOfInstructions];

    // Converte o conjunto das instruções para inteiro e armazena no array passado por referência
    converter(archive, instructionSet);

    // Contador para o ciclo de clock
    long int clock = 0;

    printf("==== Conjunto de instruções: ==== \n");
    for (int i = 0; i < numberOfInstructions; i++)
    {
        unsigned int instruction = instructionSet[i];
        unsigned int opcode = desconverteOp(instruction);
        unsigned int rs = desconverteRs(instruction);
        unsigned int rt = desconverteRt(instruction);

        if (opcode == R)
        {
            unsigned int rd = desconverteRd(instruction);
            unsigned int shamt = desconverteShamt(instruction);
            unsigned int funct = desconverteFunct(instruction);
            //execute(instruction, functional_unit_status, instruction_status, register_result_status)
        }
        else //tipo I
        {
            unsigned int immediate = desconverteImmediate(instruction);
        }
        printf("%i: %d\n", i, instructionSet[i]);
    }
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
