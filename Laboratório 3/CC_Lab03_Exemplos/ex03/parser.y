
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
void test_date(int, int, int);
%}

%token NUMBER
// Tell bison the lexemes for these token types so we can use
// them in the grammar rules.
%token SLASH "/"
%token ENTER "\n"

%%

dates:
  %empty
| dates date "\n"
;
date:
  NUMBER "/" NUMBER "/" NUMBER { test_date($1, $3, $5); }
;

%%

int main(void) {
  int result = yyparse();
  if (result == 0) printf("Parse successful!\n");
  else printf("Parse failed...\n");
}

void test_date(int d, int m, int y) {
    printf("Testing date: %d/%d/%d\n", d, m, y);
    if (y < 1 || y > 9999) {
        printf("Invalid year: %d!\n", y);
        return;
    }
    if (m < 1 || m > 12) {
        printf("Invalid month: %d!\n", m);
        return;
    }
    if (d < 1 || d > 31) {
        printf("Invalid day: %d!\n", d);
        return;
    }
    printf("Valid date!\n");
}
