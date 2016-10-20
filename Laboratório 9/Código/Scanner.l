%option noyywrap
%option nounput
%option noinput
%{
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
extern int lval;
void unknownToken(char* var);
%}
%x comment

%%
"{" BEGIN(comment);
<comment>\n { yylineno++; }
<comment>[^}]* { }
<comment>"}" BEGIN(INITIAL);
"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
"end" { return END; }
"repeat" { return REPEAT; }
"until" { return UNTIL; }
"read" { return READ; }
"write" { return WRITE; }
"puts" { return PUTS; }
"int" { return INT; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return OVER; }
"=" { return EQ; }
"<" { return LT; }
";" { return SEMI; }
":=" { return ASSIGN; }
"(" { return LP; }
")" { return RP; }
" " { }
"\""[^"\""]*"\"" { return STRING; }
\n { yylineno++; }
[0-9]+ { lval = atoi(yytext); return NUM; }
[a-zA-Z]+ { return ID; }
. { unknownToken(yytext); exit(-1); }
%%

void unknownToken(char* var) {
  printf("SCANNING ERROR (%i): Unknown symbol %s\n", yylineno, yytext);
}
