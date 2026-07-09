#ifndef PARSER_H
#define PARSER_H

// Tamanho máximo da linha
#define MAX_LINE 1024
// Número máximo de argumentos
#define MAX_ARGS 100

// Realiza o parser da linha digitada
int parse_command(char *line, char *args[]);

// Verifica se a linha contém um pipe
int has_pipe(const char *line);

// Realiza o parser da linha com pipe
int pipe_parse_command(char *line, char *args1[], char *args2[]);

#endif
