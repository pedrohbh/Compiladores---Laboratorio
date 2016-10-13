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
int lval;
int yylex(void);
void yyerror(char const *s);

BT *tree;
%}

%define api.value.type {BT *}

%token IF THEN ELSE END REPEAT UNTIL READ WRITE
%token PLUS MINUS TIMES OVER
%token EQ LT
%token SEMI ASSIGN
%token LP RP NUM ID
%left EQ LT
%left PLUS MINUS
%left TIMES OVER
%%

program: stmt_sequence { tree = $1; };

stmt_sequence: stmt_sequence stmt { $$ = 
 | stmt;

stmt: if_stmt | repeat_stmt | assign_stmt | write_stmt | read_stmt;

if_stmt: IF expr THEN stmt_sequence END | IF expr THEN stmt_sequence ELSE stmt_sequence END;

repeat_stmt: REPEAT stmt_sequence UNTIL expr;

assign_stmt: ID ASSIGN expr SEMI;

read_stmt: READ ID SEMI;

write_stmt: WRITE expr SEMI;

expr: expr PLUS expr { $$ = new_node( PLUS_NODE, $1, $3 ); }
 | expr MINUS expr { $$ = new_node( MINUS_NODE, $1, $3 ); }
 | expr TIMES expr { $$ = new_node( TIMES_NODE, $1, $3 ); }
 | expr OVER expr { $$ = new_node( OVER_NODE, $1, $3 ); }
 | LP expr RP | NUM | ID;

%%
int main(void)
{
  int result = yyparse();
  if (result == 0) printf("Parse successful!\n");
  else printf("Parse failed...\n");
}
