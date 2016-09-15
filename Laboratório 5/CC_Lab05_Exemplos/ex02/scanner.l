%option outfile="scanner.c"
%option noyywrap
%option nounput
%option noinput

%{
#include "token.h"
extern int lval;
%}

%%

[0-9]+  { lval = atoi(yytext); return NUMBER; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return TIMES; }
"("     { return LPAREN; }
")"     { return RPAREN; }
"\n"    { return ENTER; }
" "     ; // skip blanks
.       { return yytext[0]; }
