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
"\n"    { return ENTER; }
" "     ; // skip blanks
.       { return yytext[0]; }
