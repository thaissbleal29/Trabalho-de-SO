#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "executor.h"
#include "builtins.h"

int main(void) {
        char line[MAX_LINE]; // Linha digitada pelo usuário

        while(1) { // Loop principal do shell
                char *diretorio_atual = getcwd(NULL, 0); // Obtém o diretório atual
                printf("MeuJarshell:>%s$ ", diretorio_atual); // Exibe o prompt
                free(diretorio_atual); // Libera a memória alocada

                if(fgets(line, sizeof(line), stdin) == NULL) { //Lê a linha digitada 
                        break;
                }

                if(has_pipe(line)) { // Verifica se a linha contém um pipe
                        char *args1[MAX_ARGS]; // Vetor para o primeiro comando
                        char *args2[MAX_ARGS]; // Vetor para o segundo comando

                        pipe_parse_command(line, args1, args2); // Faz o parser da linha com pipe

                        exec_pipe(args1, args2); // Executa os comandos com pipe
                }


                else{
                        char *args[MAX_ARGS]; // Vetor para o comando

                        parse_command(line, args); // Faz o parser da linha
                        if(args[0] == NULL) { // Ignora as linhas vazias
                                continue;
                        }

                        if(execute_builtin(args)) { // Verifica se o comando é um builtin
                                continue;
                        }
                        exec_command(args); // Executa o comando quando ele é externo
                }    
        }
        return 0;
}
