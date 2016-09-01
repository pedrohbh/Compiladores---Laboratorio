
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
void yyerror(char const *s);
%}

%token ENTER LPAREN RPAREN ZERO ONE IF ELSE OTHER

%%

stmts:
  %empty
| stmts stmt ENTER
;

stmt:
  ifstmt | OTHER;

ifstmt:
  IF LPAREN expr RPAREN stmt
| IF LPAREN expr RPAREN stmt ELSE stmt
;

expr:
  ZERO | ONE;

%%

int main(void) {
  int result = yyparse();
  if (result == 0) printf("Parse successful!\n");
  else printf("Parse failed...\n");
}
