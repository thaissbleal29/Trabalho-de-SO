#include <stdio.h>
#include "parser.h"

int main(void)  {
        char line[MAX_LINE];
        char *args[MAX_ARGS];

        printf("Meu Shell lindo>");
        fgets(line, sizeof(line), stdin);

        int qtt = parse_command(line, args);
        printf("Número de argumentos: %d\n ", qtt);

        for(int i = 0; args[i] != NULL; i++) {
                printf("args[%d] = %s\n", i, args[i]);
        }
        return 0;
}

