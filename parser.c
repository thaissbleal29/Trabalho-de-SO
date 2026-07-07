#include <string.h>
#include "parser.h"

// REALIZA O PARSER DA LINHA DIGITADA PELO USUÁRIO
// Separa o comando em argumentos e os armazena no vetor args[]
// Retorna a quantidade de argumentos encontrados
int parse_command(char *line, char *args[]) {

    // Contador da quantidade de argumentos encontrados
    int i = 0;

    // Remove o caractere '\n' inserido pelo fgets()
    line[strcspn(line, "\n")] = '\0';

    // Verifica se o usuário apenas pressionou Enter
    if (line[0] == '\0') {
        args[0] = NULL;
        return 0;
    }

    char *token = strtok(line, " \t"); // Obtém o primeiro argumento da linha

    // Percorre todos os argumentos encontrados
    while (token != NULL && i < MAX_ARGS - 1) {

        args[i] = token; // Armazena o argumento no vetor
        i++; // Avança para a próxima posição do vetor
        token = strtok(NULL, " \t"); // Obtém o próximo argumento da linha
    }

    args[i] = NULL; // Marca o final do vetor de argumentos
    return i; // Retorna a quantidade de argumentos encontrados
}
