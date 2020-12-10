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
    if (number_instructions <= 0 || !config || !archive || !destino)
    {
        printf("Parametrização Incorreta!\n");
        printf("Utilize:\n");
        printf("\t./executavel -n <qtd_de_instrucao> -c <arq_configuracao.txt> -o <arq_destino> -p <arq_instrucoes.txt>\n");
        exit(1);
    }

    // Cria na memória um array para armazenar a configuração do scoreboarding
    int number_of_configs = count_configs(config);
    config_t configurations[number_of_configs];
    config_converter(config, configurations);

    execute_pipeline(
        destino,
        archive,
        number_of_configs,
        configurations,
        number_instructions);

    printf("Simulação concluida!\nArquivo <%s> criado!\n", destino);

    return 0;
}
