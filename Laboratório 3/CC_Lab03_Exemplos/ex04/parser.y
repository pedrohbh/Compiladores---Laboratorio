/* Options to bison */
// File name of generated parser.
%output "parser.c"
// Produces a 'parser.h'
%defines "parser.h"
// Give proper error messages when a syntax error is found.
%define parse.error verbose
// Enable LAC (lookahead correction) to improve syntax error handling.
%define parse.lac full

%{
#include <stdio.h>
int yylex(void);
void yyerror( char const *s );
void test_date(int, int, int);
%}
%token NUMBER LETRA PLUS ENTER LPAREN RPAREN
%%
line: expr ENTER;
expr: LPAREN expr RPAREN | NUMBER | LETRA;
%%
int main()
{
	int result = yyparse();
	if ( result == 0 )
		printf("Parse succesful!\n");
	else
		printf("Parse failed...\n");
}
