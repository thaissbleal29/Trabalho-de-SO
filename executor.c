#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "executor.h"

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
