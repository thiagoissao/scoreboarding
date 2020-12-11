#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "conversor.h"
#include "processador.c"
#include "components/functional_unit_status.h"
#include "components/instruction_status.h"
#include "components/register_result_status.h"
#include "components/register_database.h"
#include "prints/prints.h"
#include "config/config.h"
#include "config/config_converter.h"

typedef struct
{
    int id, number_of_configs, number_instructions;
    char *path_program, *path_destiny;
    config_t *configurations;
} thread_arg, *ptr_thread_arg;

void *run(void *arg)
{
    ptr_thread_arg targ = (ptr_thread_arg)arg;
    execute_pipeline(
        targ->path_destiny,
        targ->path_program,
        targ->number_of_configs,
        targ->configurations,
        targ->number_instructions);
}

int main(int argc, char *argv[])
{
    int option;
    char *config = NULL;        //"./examples/config.txt"
    char *path_program1 = NULL; //"./examples/mnemoniosMult.txt"
    char *path_program2 = NULL;
    char *path_destiny1 = NULL;
    char *path_destiny2 = NULL;
    FILE *archive_destiny1;
    FILE *archive_destiny2;
    int number_instructions1 = 0;
    int number_instructions2 = 0;

    while ((option = getopt(argc, argv, "n:m:p:r:c:o:q:")) != -1)
    {
        switch (option)
        {
        case 'n':
            number_instructions1 = atoi(optarg);
            break;

        case 'm':
            number_instructions2 = atoi(optarg);
            break;

        case 'c':
            config = optarg;
            break;

        case 'p':
            path_program1 = optarg;
            break;

        case 'r':
            path_program2 = optarg;
            break;

        case 'o':
            path_destiny1 = optarg;
            archive_destiny1 = fopen(path_destiny1, "w");
            if (archive_destiny1 == NULL)
            {
                printf("Erro no nome do arquivo destino!\n");
                exit(1);
            }
            fclose(archive_destiny1);
            break;

        case 'q':
            path_destiny2 = optarg;
            archive_destiny2 = fopen(path_destiny1, "w");
            if (archive_destiny2 == NULL)
            {
                printf("Erro no nome do arquivo destino!\n");
                exit(1);
            }
            fclose(archive_destiny2);
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

    if (number_instructions1 <= 0 ||
        !config ||
        !path_program1 ||
        !path_destiny1 ||
        number_instructions2 <= 0 ||
        !path_program2 ||
        !path_destiny2)
    {
        printf("Parametrização do Programa 1 Incorreta!\n");
        printf("Utilize:\n");
        printf("\t./executavel -n <qtd_de_instrucao> -c <arq_configuracao.txt> -o <arq_path_destiny> -p <arq_instrucoes.txt> -m <qtd_de_instrucao> -q <arq_path_destiny> -r <arq_instrucoes.txt>\n");
        exit(1);
    }

    // Cria na memória um array para armazenar a configuração do scoreboarding
    int number_of_configs = count_configs(config);
    config_t configurations[number_of_configs];
    config_converter(config, configurations);

    pthread_t threads[2];
    thread_arg arguments[2];

    arguments[0].id = 0;
    arguments[0].configurations = configurations;
    arguments[0].number_instructions = number_instructions1;
    arguments[0].number_of_configs = number_of_configs;
    arguments[0].path_destiny = path_destiny1;
    arguments[0].path_program = path_program1;

    arguments[1].id = 1;
    arguments[1].configurations = configurations;
    arguments[1].number_instructions = number_instructions2;
    arguments[1].number_of_configs = number_of_configs;
    arguments[1].path_destiny = path_destiny2;
    arguments[1].path_program = path_program2;

    pthread_create(&(threads[0]), NULL, run, &(arguments[0]));
    pthread_create(&(threads[1]), NULL, run, &(arguments[1]));

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Simulação concluida!\nArquivo <%s> criado!\n", path_destiny1);
    printf("Simulação concluida!\nArquivo <%s> criado!\n", path_destiny2);

    return 0;
}
