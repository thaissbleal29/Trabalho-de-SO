#include <stdio.h>
#include "parser.h"
#include "executor.h"
#include "builtins.h"

int main(void) {
        char line[MAX_LINE]; // Linha digitada pelo usuário
        char *args[MAX_ARGS]; // Vetor que armazena os argumentos

        while(1) { // Loop principal do shell
                printf("MeuJarshell:>"); 
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
