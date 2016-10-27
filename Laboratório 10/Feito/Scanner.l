%option outfile="Scanner.c"
%option noyywrap
%option nounput
%option noinput

%{
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"

void unknownToken(char* var);
%}

%%

"int" { return INT; }
"real" { return REAL; }
"string" { return STRING; }
"bool" { return BOOL; }
"print" { return PRINT; }
"true" { return TR; }
"false" { return FAL; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return OVER; }
":=" { return ASSIGN; }
"<" { return LT; }
">" { return GT; }
"<=" { return LE; }
">=" { return GE; }
"==" { return EQ; }
"\"[^\"]*\"" { return CHAR; }
" " { }
";" { return SEMI; }
"," { return COMMA; }
\n { yylineno++; }
[0-9]+ { return NUM; }
[a-zA-Z]+ { return ID; }
[.] { unknownToken( yytext ); exit( 1 ); }

%%

void unknownToken(char* var) {
  printf("SCANNING ERROR (%i): Unknown symbol %s\n", yylineno, yytext);
}
