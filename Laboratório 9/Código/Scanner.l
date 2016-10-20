%option noyywrap
%option nounput
%option noinput
%{
#include <stdio.h>
#include <stdlib.h>
#include "tables.h"
#include "Parser.h"
extern int yylval;
extern LitTable *tabelaLiterais;
extern SymTable *tabelaSimbolos;
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
"\""[^"\""]*"\"" { yylval = add_literal( tabelaLiterais, yytext); return STRING; }
\n { yylineno++; }
[0-9]+ { yylval = atoi(yytext); return NUM; }
[a-zA-Z]+ { 	if ( lookup_var( tabelaSimbolos , yytext ) == -1 )
						yylval = add_var( tabelaSimbolos, yytext, yylineno );					
					return ID; 
			 }
. { unknownToken(yytext); exit(-1); }
%%

void unknownToken(char* var) {
  printf("SCANNING ERROR (%i): Unknown symbol %s\n", yylineno, yytext);
}
