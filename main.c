#include <stdio.h>
#include "parser.h"
#include "executor.h"
#include "builtins.h"

int main(void) {
        char line[MAX_LINE];
        char *args[MAX_ARGS];

        while(1) {
                printf("MeuJarshell:>");
                if(fgets(line, sizeof(line), stdin) == NULL) {
                        break;
                }

                parse_command(line, args);
                if(args[0] == NULL) {
                        continue;
                }

                if(execute_builtin(args)) {
                        continue;
                }
                exec_command(args);
        }
        return 0;
}
