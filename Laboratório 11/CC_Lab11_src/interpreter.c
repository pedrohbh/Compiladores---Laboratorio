
#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

struct pilhaExecucao
{
	int valor;
	struct pilhaExecucao *proximoPtr;
};

struct sentinelaPilha
{
	Pilha *primeiroPtr;
	Pilha *ultimoPtr;
};

SentinelaPilha *incializaSentinela( SentinelaPilha *p )
{
	p = (SentinelaPilha *)malloc(sizeof(SentinelaPilha));
	p->primeiroPtr = NULL;
	p->ultimoPtr = NULL;
	return p;
}

void inserePilha( SentinelaPilha *p, int valor )
{
	Pilha *novoNodo = (Pilha *)malloc(sizeof(Pilha));
	if ( novoNodo == NULL )
	{
		puts("Erro ao alocar \"Novo Nodo\" na pilha por falta de memória");
		exit( 1 );
	}
	novoNodo->valor = valor;
	novoNodo->proximoPtr = NULL;

	if ( p->primeiroPtr == NULL )
	{
		p->primeiroPtr = novoNodo;
		p->ultimoPtr = novoNodo;
	}
	else
	{
		p->ultimoPtr->proximoPtr = novoNodo;
		p->ultimoPtr = novoNodo;
	}
}

int desempilha( SentinelaPilha *p )
{
	if ( p->primeiroPtr == NULL )
	{
		printf("A pilha está vazia\n");
		return 0;
	}

	Pilha *tempPtr = p->ultimoPtr;
	if ( p->primeiroPtr == p->ultimoPtr )
	{
		p->primeiroPtr = NULL;
		p->ultimoPtr = NULL;
	}
	else
	{
		Pilha *atualPtr = p->primeiroPtr;
		
		while ( atualPtr->proximoPtr != p->ultimoPtr )
			atualPtr = atualPtr->proximoPtr;
		
		p->ultimoPtr = atualPtr;
		atualPtr->proximoPtr = NULL;
	}

	int valor = tempPtr->valor;
	free( tempPtr );
	return valor;	
}	

void run_ast(AST *ast) 
{
	
    // IMPLEMENT THIS!!
    printf("Root: %p\n", ast);
}

void recRunAst( AST *node, SentinelaPilha *p )
{
	switch( node->kind )
	{
		case ASSIGN_NODE:
			runAssign( node );
			break;
		case NUM_NODE:
			runNum( node, p );
			break;
		case OVER_NODE:
			runOver( node, p );
			break;
		
	}
}

void runAssign( AST *node, SentinelaPilha *p )
{
	recRunAst( node->r );
	store( node->l, desempilha( p ) );
}



void runNum( AST *node, SentinelaPilha *p )
{
	inserePilha( p, node->data );
}

void runOver( AST *node, SentinelaPilha *p )
{
	recRunAst( node->l );
	recRunAst( node->d );
	int r = desempilha( p );
	int d = desempilha( p );
	inserePilha( p, r / d );
}


