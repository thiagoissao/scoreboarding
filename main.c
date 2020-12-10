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
    char *config = NULL;       //"./examples/config.txt"
    char *path_program = NULL; //"./examples/mnemoniosMult.txt"
    char *path_destiny = NULL;
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
            path_program = optarg;
            break;

        case 'o':
            path_destiny = optarg;
            archive_destiny = fopen(path_destiny, "w");
            if (archive_destiny == NULL)
            {
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
    if (number_instructions <= 0 || !config || !path_program || !path_destiny)
    {
        printf("Parametrização Incorreta!\n");
        printf("Utilize:\n");
        printf("\t./executavel -n <qtd_de_instrucao> -c <arq_configuracao.txt> -o <arq_path_destiny> -p <arq_instrucoes.txt>\n");
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
    arguments[0].number_instructions = number_instructions;
    arguments[0].number_of_configs = number_of_configs;
    arguments[0].path_destiny = path_destiny;
    arguments[0].path_program = path_program;

    arguments[1].id = 1;
    arguments[1].configurations = configurations;
    arguments[1].number_instructions = number_instructions;
    arguments[1].number_of_configs = number_of_configs;
    arguments[1].path_destiny = path_destiny;
    arguments[1].path_program = path_program;

    pthread_create(&(threads[0]), NULL, run, &(arguments[0]));
    pthread_create(&(threads[1]), NULL, run, &(arguments[1]));

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Simulação concluida!\nArquivo <%s> criado!\n", path_destiny);

    return 0;
}
