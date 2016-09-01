%option outfile="scanner.c"
%option noyywrap
%option nounput
%option noinput

%{
#include <stdlib.h>
#include "parser.h"
%}

%%

[0-9]+  { yylval = atoi( yytext ); return NUMBER; }
0(x|X)[0-9a-fA-F]+ { yylval = strtol( yytext, NULL, 16 ); return NUMBER; }
" "     ; // skip blanks
.|\n    { return yytext[0]; }
