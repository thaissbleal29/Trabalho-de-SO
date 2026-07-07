#include <string.h>
#include "parser.h"

int parse_command(char *line, char *args[]) {
    int i = 0;

    line[strcspn(line, "\n")] = '\0';

    if (line[0] == '\0') {
        args[0] = NULL;
        return 0;
    }

    char *token = strtok(line, " \t");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        i++;
        token = strtok(NULL, " \t");
    }

    args[i] = NULL;
    return i;
}
