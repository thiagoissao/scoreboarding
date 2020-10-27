#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "conversor.h"
#include "processador.c"
#include "unidades_funcionais/functional_unit_status.h"
#include "unidades_funcionais/instruction_status.h"
#include "unidades_funcionais/register_result_status.h"

int main()
{
    char *archive = "mnemonios.txt";

    //Quantidade de instruções no programa
    int numberOfInstructions = 10; //PARAMETRIZAR DEPOIS Ex: -m 300000

    // Cria na memória um array com o inteiro de cada instrução
    unsigned int instructionSet[numberOfInstructions];

    // Converte o conjunto das instruções para inteiro e armazena no array passado por referência
    converter(archive, instructionSet);

    // Contador para o ciclo de clock
    long int clock = 0;

    // Status das instruções
    instruction_status_t instruction_status;

    // Status das unidades funcionais
    functional_unit_status_t functional_unit_status;

    // Status dos registradores
    register_result_status_t register_result_status;

    printf("==== Conjunto de instruções: ==== \n");
    for (int i = 0; i < numberOfInstructions; i++)
    {
        execute(
            instructionSet[i],
            functional_unit_status,
            instruction_status,
            register_result_status);
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
