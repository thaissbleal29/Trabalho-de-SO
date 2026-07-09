#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "executor.h"
#include "builtins.h"

int main(void) {
        char line[MAX_LINE]; // Linha digitada pelo usuário
        char *args[MAX_ARGS]; // Vetor que armazena os argumentos

        while(1) { // Loop principal do shell
                char *diretorio_atual = getcwd(NULL, 0); // Obtém o diretório atual
                printf("MeuJarshell:>%s$ ", diretorio_atual); // Exibe o prompt
                free(diretorio_atual); // Libera a memória alocada

                if(fgets(line, sizeof(line), stdin) == NULL) { //Lê a linha digitada 
                        break;
                }

                parse_command(line, args); // Faz o parser da linha
                if(args[0] == NULL) { // Ignora as linhas vazias
                        continue;
                }

                if(execute_builtin(args)) { // Verifica se o comando é um builtin
                        continue;
                }
                exec_command(args); // Executa o comando quando ele é externo
        }
        return 0;
}
