#include <stdio.h>
#include "parser.h"

int main(void)  {
        char line[MAX_LINE]; // Linha digitada pelo usuário
        char *args[MAX_ARGS]; // Vetor que armazenará os argumentos

        printf("Meu Shell lindo>");
        fgets(line, sizeof(line), stdin); // Lê a linha digitada

        int qtt = parse_command(line, args); // Armazena o número de argumentos
        printf("Número de argumentos: %d\n ", qtt);

        for(int i = 0; args[i] != NULL; i++) { // Exibe os argumentos encontrados
                printf("args[%d] = %s\n", i, args[i]);
        }
        return 0;
}

