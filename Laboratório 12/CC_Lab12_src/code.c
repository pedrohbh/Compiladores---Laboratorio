#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "code.h"

int registerCounter = 1;


void emit_code(AST *ast) 
{
	
    // IMPLEMENT THIS!!
	 rec_run_ast( ast );
    printf("Root: %p\n", ast);
}

int stringSize( int x )
{
	int size = x / 10 + 2;
	return size;
}

char *alocaString( int tamanho )
{
	char *temp = (char *)malloc(sizeof(char) * stringSize( tamanho ) );
	if ( temp == NULL )
	{
		puts("Erro ao alocar string. Encerrando programa");
		exit( 0 );
	}
	return temp;
}

int newTemp()
{
	return registerCounter++;
}

void emit1( char *opCode, int r1 )
{
	char *R1 = alocaString( r1 );
	sprintf( R1, "r%d", r1 );
	printf("%s %s\n", opCode, R1 );
}

void emit2( char *opCode, int r1, int r2 )
{
	char *R1 = alocaString( r1 );
	char *R2 = alocaString( r2 );
	sprintf( R1, "r%d", r1 );
	sprintf( R2, "r%d", r2 );
	printf("%s %s %s\n", opCode, R1, R2 );
}

void emit3( char *opCode, int r1, int r2, int r3 )
{
	char *R1 = alocaString( r1 );
	char *R2 = alocaString( r2 );
	char *R3 = alocaString( r3 );
	sprintf( R1, "r%d", r1 );
	sprintf( R2, "r%d", r2 );
	sprintf( R3, "r%d", r3 );
	printf("%s %s %s %s\n", opCode, R1, R2, R3 );
}

int rec_run_ast( AST *ast )
{
	int temp;
	//puts("Primeiro");
	switch( get_kind( ast ) )
	{
		case STMT_SEQ_NODE: temp = emit_sequence( ast ); break;//return "stmt_seq";
		case IF_NODE: break;//return "if";
		case REPEAT_NODE: break;//return "repeat";
		case READ_NODE: break;//return "read";
		case WRITE_NODE: temp = emit_write( ast ); break;
		case PLUS_NODE: temp = emit_plus( ast ); break;
		case MINUS_NODE: break;//return "-";
		case TIMES_NODE: break;//return "*";
		case OVER_NODE: break;//return "/";
		case LT_NODE: break;//return "<";
		case EQ_NODE: break;//return "=";
		case ASSIGN_NODE: break;//return ":=";
		case NUM_NODE: temp = emit_num( ast ); break;
		case ID_NODE: break;//return "id";
		default: puts("ERROR!!");
	}
	//puts("Segundo");
	return temp;
}

int emit_sequence( AST *ast )
{
	int i;
	int temp;
	for ( i = 0; i < get_child_count( ast ); i++ )
		temp = rec_run_ast( get_child( ast, i ) );
	return temp;
}
	
int emit_write( AST *ast )
{
	//puts("WRITE");
	int t = rec_run_ast( get_child( ast, 0 ) );
	emit1( "OUT", t );
	return t;
}

int emit_num( AST *ast )
{
	int t = newTemp();
	emit2( "LDC", t, get_data( ast ) );
	return t;
}

int emit_plus( AST *ast )
{
	int l = rec_run_ast( get_child( ast, 0 ) );
	int r = rec_run_ast( get_child( ast, 1 ) );
	int t = newTemp();
	emit3( "ADD", t, l, r );
	return t;
}
