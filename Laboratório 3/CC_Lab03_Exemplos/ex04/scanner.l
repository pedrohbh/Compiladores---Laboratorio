%option outfile="scanner.c"
%option noyywrap
%option nounput
%option noinput
%{
#include "parser.h"
%}
%%
[0-9]+ { return NUMBER; }
[a-zA-Z]+ { return LETRA; }
"+" { return PLUS; }
"\n" { return ENTER; }
"(" { return LPAREN; }
")" { return RPAREN; }
" " ;
. { return yytext[0]; }
