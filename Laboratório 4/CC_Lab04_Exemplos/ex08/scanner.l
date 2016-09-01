%option outfile="scanner.c"
%option noyywrap
%option nounput
%option noinput

%{
#include "parser.h"
%}

%%

"0"     { return ZERO; }
"1"     { return ONE; }
"if"    { return IF; }
"else"  { return ELSE; }
"other" { return OTHER; }
"("     { return LPAREN; }
")"     { return RPAREN; }
"\n"    { return ENTER; }
" "     ; // skip blanks
.       { return yytext[0]; }
