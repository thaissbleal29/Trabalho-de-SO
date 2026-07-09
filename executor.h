#ifndef EXECUTOR_H
#define EXECUTOR_H

// vetor de argumentos recebido do parser
void exec_command(char *args[]);

// Executa comandos com pipe
void exec_pipe(char *args1[], char *args2[]);

#endif
