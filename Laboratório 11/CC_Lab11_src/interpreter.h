#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"

typedef struct pilhaExecucao Pilha;

typedef struct sentinelaPilha SentinelaPilha;

SentinelaPilha *incializaSentinela( SentinelaPilha *p );

void run_ast(AST *ast);

#endif
