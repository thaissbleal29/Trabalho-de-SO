#ifndef PARSER_H
#define PARSER_H

// Tamanho máximo da linha
#define MAX_LINE 1024
// Número máximo de argumentos
#define MAX_ARGS 100

// Realiza o parser da linha digitada
int parse_command(char *line, char *args[]);

#endif
