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

void execute_pthread(
    config_t *configurations,
    int number_instructions1,
    int number_of_configs,
    char *path_destiny1,
    char *path_program1,
    int number_instructions2,
    char *path_destiny2,
    char *path_program2)
{

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
}