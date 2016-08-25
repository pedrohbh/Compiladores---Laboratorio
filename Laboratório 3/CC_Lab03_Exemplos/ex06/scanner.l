%option outfile="scanner.c"
%option noyywrap
%option nounput
%option noinput
%{
#include "parser.h"
%}
%%
[0-9]+  { return NUMBER; }
"+"     { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return OVER; }
">" { return GT; }
"<" { return LT; }
">=" { return GE; }
"<=" { return LE; }
"\n"    { return ENTER; }
"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
" "     ; // skip blanks
.       { return yytext[0]; }
