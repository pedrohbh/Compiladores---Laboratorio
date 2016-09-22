#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Token.h"

TokenType token;
int lval;

TokenType yylex();

// Prótotipos das Funções
int program();
int stmtSequence();
int stmt();
int ifStmt();
int repeatStmt();
int assingStmt();
int readStmt();
int writeStmt();
int expr();
int comparisonOp();
int simpleExpr();
int addOp();
int term();
int mulOp();
int factor();

void error()
{
	printf("Error\n");
	exit( 1 );
}

void match( int expected_token )
{
	if ( token == expected_token )
	{
		token = yylex();
	}
	else
		error();
}

int program()
{
	int temp = stmtSequence();
	return temp;
}

int stmtSequence()
{
	int temp = stmt();
	//while
	return temp;
}

int stmt()
{
	int temp;
	switch( token )
	{
		case IF:
			temp = ifStmt();
			break;
		case REPEAT:
			temp = repeatStmt();
			break;
		case ASSING:
			temp = assingStmt();
			break;
		case READ:
			temp = readStmt();
			break;
		case WRITE:
			temp = writeStmt();
			break;
		default:
			error();
			break;
	}
	return temp;
}

int ifStmt()
{
	int temp;
	match( IF );
	temp = expr();
	match( THEN );
	temp = stmtSequence();
	if ( token == ELSE )
	{
		match(ELSE);
		temp = stmtSequence();
	}
	match(END);
}
	

int main()
{
	int result;
	token = yylex();
	//result = program()
	return 0;
}
