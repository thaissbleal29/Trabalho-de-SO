#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "executor.h"
#include "builtins.h"

// EXECUTA COMANDOS EXTERNOS UTILIZANDO FORK, EXECVP E WAITPID
void exec_command(char *args[]) {

    // Verifica se existe algum comando para executar
    if (args[0] == NULL) {
        return;
    }

    // Cria um novo processo (filho)
    pid_t pid = fork();

    // Verifica se ocorreu erro na criação do processo
    if (pid < 0) {
        perror("Erro no fork");
        return;
    }

    // PROCESSO FILHO
    else if (pid == 0) {

        // Substitui o processo filho pelo programa solicitado
        int retorno = execvp(args[0], args);

        // Caso o execvp falhe, exibe a mensagem de erro e encerra o processo filho
        if (retorno == -1) {
            perror("Erro ao executar comando");
            exit(EXIT_FAILURE);
        }
    }

    // PROCESSO PAI
    else {

        int status;

        // Aguarda o término do processo filho
        if (waitpid(pid, &status, 0) == -1) {
            perror("Erro ao esperar pelo processo filho");
        }
    }
}

// EXECUTA COMANDOS COM PIPE
void exec_pipe(char *args1[], char *args2[]) {
    if (args1[0] == NULL || args2[0] == NULL) {
        fprintf(stderr, "Erro: Comando inválido para pipe.\n");
        return;
    }

    int pipefd[2]; // Array para armazenar os descritores do pipe


    // Cria o pipe
    if (pipe(pipefd) == -1) {
        perror("Erro ao criar pipe");
        return;
    }

    // Cria o primeiro processo (comando antes do pipe)
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Erro no fork do primeiro comando");
        return;
    }

    if (pid1 == 0) { // Processo filho 1
        close(pipefd[0]); // Fecha a extremidade de leitura do pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redireciona a saída do comando para o pipe
        close(pipefd[1]); // Fecha a extremidade de escrita do pipe

        // Se for builtin
        if (execute_builtin(args1)) {
            exit(EXIT_SUCCESS); // Encerra o filho
        }

        // Executa o primeiro comando
        execvp(args1[0], args1);
        perror("Erro ao executar o primeiro comando");
        exit(EXIT_FAILURE);
    }

    // Cria o segundo processo (comando depois do pipe)
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Erro no fork do segundo comando");
        return;
    }

    if (pid2 == 0) { // Processo filho 2
        close(pipefd[1]); // Fecha a extremidade de escrita do pipe
        dup2(pipefd[0], STDIN_FILENO); // Redireciona a entrada do comando para o pipe
        close(pipefd[0]); // Fecha a extremidade de leitura do pipe

        // Se for builtin
        if (execute_builtin(args2)) {
            exit(EXIT_SUCCESS);
        }
        
        // Executa o segundo comando
        execvp(args2[0], args2);
        perror("Erro ao executar o segundo comando");
        exit(EXIT_FAILURE);
    }

    // Processo pai fecha ambos os lados do pipe e espera pelos filhos
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0); // Espera pelo primeiro filho
    waitpid(pid2, NULL, 0); // Espera pelo segundo filho
}
