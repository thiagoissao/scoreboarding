#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "conversor.h"
#include "processador.c"
#include "unidades_funcionais/functional_unit_status.h"
#include "unidades_funcionais/instruction_status.h"
#include "unidades_funcionais/register_result_status.h"

int main()
{
    char *archive = "mnemonios.txt";

    //Quantidade de instruções no programa
    int numberOfInstructions = 4; //PARAMETRIZAR DEPOIS Ex: -m 300000

    // Cria na memória um array com o inteiro de cada instrução
    unsigned int instruction_set[numberOfInstructions];

    // Converte o conjunto das instruções para inteiro e armazena no array passado por referência
    converter(archive, instruction_set);

    // Contador para o ciclo de clock
    unsigned int clock = 0;

    // Status das unidades funcionais
    functional_unit_status_table_t *fu_status_table = (functional_unit_status_table_t *)malloc(sizeof(functional_unit_status_table_t));

    // Status das instruções e inicialização
    instruction_status_t inst_status_table[numberOfInstructions];
    init_instruction_status_table(inst_status_table, instruction_set, numberOfInstructions);
    bool has_completed = false;

    // Status dos registradores
    register_result_status_table_t *rr_status_table = (register_result_status_table_t *)malloc(sizeof(register_result_status_table_t));

    printf("==== Conjunto de instruções ==== \n");
    unsigned int i = 0;
    while (!has_completed)
    {
        execute(
            &clock,
            &has_completed,
            instruction_set[i],
            fu_status_table,
            inst_status_table,
            rr_status_table);
        printf("instruction: %d\n", inst_status_table[i].instruction);
        printf("busy: %d\n", inst_status_table[i].issue);
        if (i < numberOfInstructions)
        {
            i++;
        }
        if (i == numberOfInstructions)
        {
            has_completed = true;
        }
    }

    free(fu_status_table);
    free(rr_status_table);
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
