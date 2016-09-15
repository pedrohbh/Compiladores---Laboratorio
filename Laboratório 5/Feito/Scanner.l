%option noyywrap
%option nounput
%option noinput
%{
#include <stdio.h>
#include <stdlib.h>
#include "Token.h"
extern int lval;
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
\n { yylineno++; return ENTER; }
[0-9]+ { lval = atoi(yytext); return NUM; }
[a-zA-Z]+ { return ID; }
%%
