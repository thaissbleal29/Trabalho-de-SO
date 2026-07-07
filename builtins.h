#ifndef BUILTINS_H
#define BUILTINS_H

// Executa um comando interno (builtin).
// Retorna:
// 1 -> o comando era um builtin e foi executado.
// 0 -> o comando não é um builtin.
int execute_builtin(char *args[]);

#endif
