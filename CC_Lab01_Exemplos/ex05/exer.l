%{
#include <stdio.h>
%}
letra [A-Z]
digito [0-9]
placa ({letra}{3}-{digito}{4})
%%
{placa}	{ printf("Encontrado numero: %s\n", yytext); }
%%
int main() { yylex(); return 0; }
int yywrap() { return -1; }
