%{
#include <stdio.h>
%}
digito [0-9]
naozero [1-9]
letrahexa [a-fA-F]
numero (({naozero}|{letrahexa})({digito}|{letrahexa})*)|0
%%
{numero}	{ printf("Encontrado numero: %s\n", yytext); }
%%
int main() { yylex(); return 0; }
int yywrap() { return -1; }
