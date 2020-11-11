#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "conversor.h"
#include "processador.c"
#include "components/functional_unit_status.h"
#include "components/instruction_status.h"
#include "components/register_result_status.h"
#include "components/register_database.h"
#include "prints/prints.h"
#include "config/config.h"
#include "config/config_converter.h"

// #define PROGRAM "mnemonios.txt"
// #define CONFIG "config.txt"
// #define CICLOS 18

int main(int argc, char *argv[])
{
    int option;
    char *config = NULL;  //"./examples/config.txt"
    char *archive = NULL; //"./examples/mnemoniosMult.txt"
    char *destino = NULL;
    FILE *archive_destiny;
    int number_instructions = 0;

    while ((option = getopt(argc, argv, "n:p:c:o:")) != -1)
    {
        switch (option)
        {
        case 'n':
            number_instructions = atoi(optarg);
            break;

        case 'c':
            config = optarg;
            break;

        case 'p':
            archive = optarg;
            break;

        case 'o':
            destino = optarg;
            archive_destiny = fopen(destino, "w");
            if (archive_destiny == NULL){
                printf("Erro no nome do arquivo destino!\n");
                exit(1);
            }
            fclose(archive_destiny);
            break;

        case '?':
            if (optopt == 'c' || optopt == 'p') // Esqueceu um argumento
                fprintf(stderr, "Opção '-%c' requer caminho para o arquivo.\n", optopt);
            else if (optopt == 'n') // Esqueceu um argumento
                fprintf(stderr, "Opção n requer o número de instruções.\n");
            else if (isprint(optopt))
                fprintf(stderr, "Opção '-%c' desconhecida.\n", optopt);
            else
                fprintf(stderr, "Caractere '\\x%x' de opção desconhecido.\n", optopt);
            exit(1);
        }
    }
    if (number_instructions <= 0 || !config || !archive || !destino){
        printf("Parametrização Incorreta!\n");
        printf("Utilize:\n");
        printf("\t./executavel -n <qtd_de_instrucao> -c <arq_configuracao.txt> -o <arq_destino> -p <arq_instrucoes.txt>\n");
        exit(1);
    }


    // Cria na memória um array para armazenar a configuração do scoreboarding
    int number_of_configs = count_configs(config);
    config_t configurations[number_of_configs];
    config_converter(config, configurations);

    // Cria na memória um array com o inteiro de cada instrução
    unsigned int instruction_set[number_instructions];

    // Converte o conjunto das instruções para inteiro e armazena no array passado por referência
    converter(archive, instruction_set);

    // Status das unidades funcionais e inicialização
    functional_unit_status_table_t *fu_status_table = (functional_unit_status_table_t *)malloc(sizeof(functional_unit_status_table_t));
    init_functional_unit_status_table(fu_status_table);

    // Status das instruções e inicialização
    instruction_status_t inst_status_table[number_instructions];
    init_instruction_status_table(inst_status_table, instruction_set, number_instructions);

    // Status dos registradores e inicialização
    register_result_status_table_t *rr_status_table = (register_result_status_table_t *)malloc(sizeof(register_result_status_table_t));
    init_register_status_table(rr_status_table);

    // Banco de registradores
    register_database_t *register_database = (register_database_t *)malloc(sizeof(register_database_t));

    execute_scoreboarding(
        destino,
        number_of_configs,
        configurations,
        number_instructions,
        fu_status_table,
        inst_status_table,
        rr_status_table,
        register_database);
        
    printf("Simulação concluida!\nArquivo <%s> criado!\n",destino);
    free(fu_status_table);
    free(rr_status_table);
    free(register_database);
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
