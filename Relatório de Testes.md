# MeuJarshell — Relatório de Testes

## 1. Ambiente de Teste

- **Sistema Operacional:** Fedora 44, KDE Plasma Edition
- **Compilador:** GCC 16.1.1 (Red Hat)

## 2. Metodologia

Os testes foram feitos manualmente, digitando comandos diretamente no shell e observando a saída obtida. A abordagem principal foi de teste funcional (caixa-preta): os casos foram definidos a partir do comportamento observável na interface de linha de comando.

Entretanto, para realizar esses testes, o código foi estudado e entendido minuciosamente, tanto a fim de procurar possíveis casos que levariam a falhas quanto para explicar os erros que foram encontrados.

## 3. Casos de Teste

### 3.1 Comando inválido

Esse é o caso básico: ao receber um input inválido, o shell responde com a mensagem `Erro ao executar comando: No such file or directory`, sem travar ou quebrar o fluxo de execução.

A resposta "Erro ao executar comando" faz parte diretamente do nosso código, enquanto a parte "No such file or directory" vem da função `execvp()` ao não achar o tal comando inválido representado por um diretório no PATH do computador.

### 3.2 Entrada extremamente longa

Ao fornecer uma mensagem com uma grande quantidade de caracteres na entrada do shell o resultado foi uma sequência de erros:

```shell
Erro ao executar comando: File name too long
MeuJarshell:>Erro ao executar comando: File name too long
MeuJarshell:>Erro ao executar comando: File name too long
MeuJarshell:>Erro ao executar comando: File name too long
Erro ao executar comando: No such file or directory
```

O erro `File name too long` acontece porque a entrada fornecida foi um grande bloco de caracteres sem espaços entre eles. Então, o código em `parser.c` criou um único token args[0] que, seguindo a lógica do código, foi passado para a função `execvp()` em `executor.c`. Ao tentar procurar um arquivo com o nome correspondente a esse token, a função retorna o erro `File name too long` porque o token tem mais caracteres do que o nome de um arquivo é autorizado a ter.

Já os prompts repetidos (`MeuJarshell:>MeuJarshell:>MeuJarshell:>`) têm a ver com o tamanho do buffer de leitura. Quando a mensagem ultrapassa o limite da função `fgets()` , ela processa a quantidade máxima de caracteres que conseguir enquanto o restante da mensagem fica esperando o próximo loop da função `main` para, então, ser processado. No caso desse teste, o tamanho da entrada foi suficiente para gerar em 4 loops o erro "File name too long" e, depois, chegar no erro "No such file or directory", pois a quantidade final restante de caracteres não ultrapassava o limite do nome de arquivo, mas ainda não significava nada.

### 3.3 Excesso de argumentos

Comandos com argumentos além do necessário são aceitos sem nenhum aviso. Por exemplo, `cd` aceita múltiplos argumentos e simplesmente ignora os extras:

```
MeuJarshell:>ls
packettracer-fedora  pasta  QHydro  rock-scissors-and-stuff  teste  Trabalho-de-SO
MeuJarshell:>cd pasta mais argumentos desnessecarios
MeuJarshell:>ls
estou_dentro_da_pasta.txt
```

O comando `cd` funcionou corretamente (mudou para a pasta certa). Isso acontece porque a função `builtin_cd()` em `builtins.c` só verifica `args[1]` (o primeiro argumento após o nome do comando) para decidir para qual diretório mudar, e chama `chdir(args[1])` diretamente. Os argumentos extras (`args[2]`, `args[3]`, ...) nem chegam a ser lidos pela função.

### 3.4 Ctrl+C encerra o shell

Ao pressionar Ctrl+C durante a execução do shell, o processo é encerrado por completo e o terminal volta para o shell padrão do sistema, em vez de apenas interromper o comando em execução (que é o comportamento do bash, por exemplo):

```bash
MeuJarshell:>^C
andreV@Ahn-dre:~/Documents/GitHub/Trabalho-de-SO$ 
```

Isso acontece porque o sinal gerado pelo comando Ctrl+C não é tratado no código do projeto e, portanto, esse sinal encerra o processo do próprio MeuJarshell, como faria, comumente, com qualquer processo que estivesse rodando no terminal.

### 3.5 Não há suporte a argumentos entre aspas

Ao tentar rodar um comando Python via terminal, o shell não interpreta corretamente strings entre aspas, quebrando o argumento no meio:

```shell
MeuJarshell:>python3 -c "print('Hello World')"
  File "<string>", line 1
    "print('Hello
    ^
SyntaxError: unterminated string literal (detected at line 1)
```

Erro que se dá devido ao fato de que a função `parse_command()` em `parser.c` usa `strtok(line, " \t")` para separar os argumentos, que quebra a linha em qualquer espaço ou tab encontrado, mas sem verificar o caso de aspas. Como o `strtok` não reconhece `"` ou `'` como caracteres especiais, o comando `python3 -c "print('Hello World')"` acaba sendo dividido em argumentos que não fazem sentido (`"print('Hello`, `World')"`), quebrando a string que deveria ser um único argumento para o Python.

### 3.6 Execução de processos filhos (aplicação gráfica)

Foi testado rodar o Firefox a partir do shell. De modo geral, o comportamento foi bom: consegui interagir com a aplicação sem problemas e digitar comandos inválidos no shell não levou a nenhum tipo de falha.

```
MeuJarshell:>firefox
restorecon: SELinux: Could not get canonical path for /home/andreV/.config/mozilla/firefox/*/gmp-widevinecdm/* restorecon: No such file or directory.
teste
teste
alo alo
ls
vou fechar o firefox
MeuJarshell:>Erro ao executar comando: No such file or directory
MeuJarshell:>Erro ao executar comando: No such file or directory
MeuJarshell:>Erro ao executar comando: No such file or directory
MeuJarshell:>builtins.c  executor.h     main_teste_exec    parser.h
builtins.h  main        main_teste_exec.c  README.md
executor.c  main.c      parser.c           test_parser.c
MeuJarshell:>Erro ao executar comando: No such file or directory
```

Isso confirma que o Firefox foi executado como processo filho: a função `exec_command()` em `executor.c` usa `fork()` para criar um novo processo, que substitui sua própria imagem pelo programa solicitado via `execvp()`. O processo pai (o shell) chama `waitpid()` logo em seguida, ficando bloqueado até o processo filho terminar — é justamente por isso que os comandos digitados enquanto o Firefox estava aberto só foram processados depois que ele foi fechado: o shell literalmente não voltava a ler o `stdin` enquanto estava esperando o filho.

Curiosamente, o fato de os comandos serem processados após o encerramento da aplicação, como, por exemplo, o comando `ls` sendo devidamente finalizado, é um comportamento comum, visto que também ocorre no terminal padrão do Fedora.

## 4. Conclusão

O MeuJarshell consegue executar comandos básicos corretamente, incluindo aplicações gráficas rodando como processos filhos, e trata comandos inválidos de forma adequada, sem travar. Os pontos observados nos testes (histórico de comandos, tratamento de sinais, parsing de aspas, validação de argumentos) representam funcionalidades que shells mais completos implementam, mas que não são triviais de adicionar — cada uma exige mecanismos específicos (buffers dinâmicos, parsers mais elaborados). Esses pontos servem como um bom roteiro de evolução para versões futuras do projeto.
