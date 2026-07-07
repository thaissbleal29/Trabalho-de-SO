#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "executor.h"

void exec_command(char *args[]) {
    //caso nao tenha comando
    if (args[0] == NULL) {
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Erro no fork");
        return;
    } 
    else if (pid == 0) {
       int retorno = execvp(args[0], args);
        if (retorno == -1) {
            perror("Erro ao executar comando");
            exit(EXIT_FAILURE);
        }
    } 
    else {
        int status;
        //espera o filho terminar
        if (waitpid(pid, &status, 0) == -1) {
            perror("Erro ao esperar pelo processo filho");
        }
    }
}
