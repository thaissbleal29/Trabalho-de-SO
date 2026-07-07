#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtins.h"

// ESTRUTURA DOS COMANDOS IMPLEMENTADOS
typedef int (*BuiltinFunc)(char *args[]);
// ESTRUTURA DA TABELA COM OS COMANDOS
typedef struct {
    char *nome;
    BuiltinFunc funcao;
} Builtin;

// OBS: return 1-> volta para o while da main
// COMANDO HELP - LISTAR COMANDOS INTERNOS DISPONÍVEIS AO JARSHELL
int builtin_help(char *args[]) {
    printf("Comandos internos:\n");
    printf("cd <diretorio>\n");
    printf("exit\n");
    printf("pwd\n");
    printf("clear\n");
    printf("help\n");
    return 1;
}
// COMANDO CD - MUDAR O DIRETÓRIO
int builtin_cd(char *args[]) {
    if (args[1] == NULL) { // Se for digitado apenas cd sem um nome de diretório 
        printf("Você não informou um diretório. Use: cd nome_do_diretorio\n");
       return 1;
    }

    if (chdir(args[1]) != 0) { // Se não existir o diretório citado
        perror("cd"); // Imprime uma mensagem de erro do tipo cd
    }

    return 1; 
}
// COMANDO EXIT
int builtin_exit(char *args[]) {
    exit(0); // implementa o exit do prórpio terminal do linux
}
// COMANDO PWD
int builtin_pwd(char *args[]) {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");

    return 1;
}

int builtin_clear(char *args[]) {
    printf("\033[H\033[J");
    return 1;
}

Builtin builtins[] = {
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {"help", builtin_help},
    {"pwd", builtin_pwd},
    {"clear", builtin_clear}
};

int num_builtins = sizeof(builtins) / sizeof(builtins[0]);

int execute_builtin(char *args[]) {
    if (args[0] == NULL)
        return 0;

    for (int i = 0; i < num_builtins; i++) {
        if (strcmp(args[0], builtins[i].nome) == 0) {
            return builtins[i].funcao(args);
        }
    }

    return 0;
}
