#include "executor.h"
#include <stddef.h>
#include <stdio.h>

int main() {
    printf("--- TESTANDO EXECUTOR COMPILADO DIRETO ---\n\n");

    // Teste 1: Executar o comando 'ls -l'
    printf("[Teste 1] Rodando: ls -l\n");
    char *comando1[] = {"ls", "-l", NULL};
    exec_command(comando1);

    printf("\n-----------------------------------------\n");

    // Teste 2: Executar o comando 'uname -a' (mostra info do sistema)
    printf("[Teste 2] Rodando: uname -a\n");
    char *comando2[] = {"uname", "-a", NULL};
    exec_command(comando2);

    printf("\n--- FIM  ---\n");
    return 0;
}
