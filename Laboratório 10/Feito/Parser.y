/* Options to bison */
// File name of generated parser.
%output "Parser.c"
// Produces a 'parser.h'
%defines "Parser.h"
// Give proper error messages when a syntax error is found.
%define parse.error verbose
// Enable LAC (lookahead correction) to improve syntax error handling.
%define parse.lac full

%{
#include <stdio.h>
%}

%token INT REAL STRING BOOL PRINT TR FAL
%token PLUS MINUS TIMES OVER
%token ASSIGN LT GT LE GE EQ
%token CHAR SEMI COMMA
%token NUM ID

%%

program: stmt_sequence;

stmt_sequence: stmt_sequence stmt | stmt;

stmt: assign_stmt | print_stmt | decla_stmt;

decla_stmt: INT id_stmt | REAL id_stmt | STRING id_stmt | BOOL id_stmt;

id_stmt: ID COMMA id_stmt | ID SEMI;

assign_stmt: ID ASSIGN expr SEMI;

expr: expr PLUS expr | expr MINUS expr | expr TIMES expr | expr OVER expr | NUM | ID | TR | FAL;

print_stmt: PRINT ID SEMI;



%%
