%{
#include <ctype.h>
#include <stdio.h>
int yylex(void);
void yyerror(char const *s);
%}
%token DIGIT PLUS ENTER
%%
line: expr ENTER;
expr: expr PLUS expr | DIGIT;
%%
int yylex(void) {
  int c = getchar();
  if (isdigit(c)) { return DIGIT; }
  else if (c == '+') { return PLUS; }
  else if (c == '\n') { return ENTER; }
  return c; // Not a digit or plus or enter.
}
int main(void) {
  int result = yyparse();
  if (result == 0) printf("Parse successful!\n");
  else printf("Parse failed...\n");
}
