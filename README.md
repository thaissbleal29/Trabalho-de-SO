# MeuJarShell

## Integrantes

• André Venâncio Sousa Grangeiro Filho  (564717)

• Lorena de Carvalho Gonçalves (567096)

• Thaís Sousa Barros Leal (565548)

## Descrição do projeto

O MeuJarshell é um intepretador de comandos shell simplificado implementado em C que permite ao usuário executar comandos de um ambiente Linux. No projeto, pudemos aplicar conceitos fundamentais de Sistemas Operacionais, como as chamadas de sistema (syscalls) e o gerenciamento de processos. O shell interpreta comandos inseridos pelo usuário identifica comandos internos e executa programas externos através das syscalls fork(), execvp() e waitpid(). Além disso, o projeto oferece suporte para pipes simples, permitindo que a saída de um comando seja utilizada como entrada de outro, utilizando as syscalls pipe(), dup2() e close().

## Funcionalidades

• Execução de comandos externos

• Comandos internos: (cd, pwd, help, clear, exit)

• Execução de comandos utilizando pipe único

• Parser para separação de comandos e argumentos

• Criação de processos utilizando fork()

• Execução de programas utilizando execvp()

• Sincronização entre processos utilizando waitpid()

## Diagrama de blocos geral

<img width="1301" height="1013" alt="início" src="https://github.com/user-attachments/assets/04f71c93-cec8-4095-b067-349edd82a497" />

## Diagrama: como os arquivos conversam entre si?

<img width="552" height="490" alt="image" src="https://github.com/user-attachments/assets/72c69328-31be-42b9-87f5-cc0289c22c69" />

## Sistema de Arquivos - HFS+/APFS

O sistema de arquivos trabalhado pela equipe no seminário foram os sistemas HFS+, e APFS, ambos próprios do S.O. MAC OS.

Slides da apresentação:

🖇️ https://canva.link/9msjuchhvq31in0
