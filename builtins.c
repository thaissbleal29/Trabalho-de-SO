#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtins.h"

// ESTRUTURA PARA ARMAZENAR O PONTEIRO PARA A FUNÇÃO DE CADA BUILTIN
typedef int (*BuiltinFunc)(char *args[]);

// ESTRUTURA DA TABELA DE COMANDOS INTERNOS
typedef struct {
    char *nome;              // Nome do comando
    BuiltinFunc funcao;      // Função associada ao comando
} Builtin;

// OBS: return 1 -> informa à main que o comando foi tratado pelo builtin

// COMANDO HELP - LISTA TODOS OS COMANDOS INTERNOS DISPONÍVEIS
int builtin_help(char *args[]) {
    printf("Comandos internos:\n");
    printf("cd <diretorio>: muda o diretório atual\n");
    printf("exit: encerra o shell\n");
    printf("pwd: mostra o diretório atual\n");
    printf("clear: limpa a tela\n");
    printf("help: mostra a ajuda\n");

    return 1;
}

// COMANDO CD - ALTERA O DIRETÓRIO ATUAL DO SHELL
int builtin_cd(char *args[]) {

    // Verifica se o usuário informou um diretório
    if (args[1] == NULL) {
        printf("Você não informou um diretório. Use: cd nome_do_diretorio\n");
        return 1;
    }

    // Tenta alterar o diretório; se falhar, exibe a mensagem de erro
    if (chdir(args[1]) != 0) {
        perror("cd");
    }

    return 1;
}

// COMANDO EXIT - ENCERRA O SHELL
int builtin_exit(char *args[]) {
    exit(0);
}

// COMANDO PWD - EXIBE O DIRETÓRIO ATUAL
int builtin_pwd(char *args[]) {
    char cwd[1024];

    // Obtém o caminho do diretório atual
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");

    return 1;
}

// COMANDO CLEAR - LIMPA A TELA DO TERMINAL
int builtin_clear(char *args[]) {
    printf("\033[H\033[J");
    return 1;
}

// TABELA QUE RELACIONA O NOME DO COMANDO À SUA FUNÇÃO
Builtin builtins[] = {
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {"help", builtin_help},
    {"pwd", builtin_pwd},
    {"clear", builtin_clear}
};

// CALCULA AUTOMATICAMENTE A QUANTIDADE DE BUILTINS DA TABELA
int num_builtins = sizeof(builtins) / sizeof(builtins[0]);

// VERIFICA SE O COMANDO DIGITADO É UM BUILTIN
int execute_builtin(char *args[]) {

    // Não há comando para executar
    if (args[0] == NULL)
        return 0;

    // Percorre toda a tabela de builtins
    for (int i = 0; i < num_builtins; i++) {

        // Compara o comando digitado com o nome armazenado na tabela
        if (strcmp(args[0], builtins[i].nome) == 0) {

            // Executa a função correspondente ao builtin encontrado
            return builtins[i].funcao(args);
        }
    }

    // Retorna 0 indicando que o comando não é um builtin
    return 0;
}
