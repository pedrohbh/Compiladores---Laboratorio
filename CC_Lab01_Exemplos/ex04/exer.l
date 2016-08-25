%{
#include <stdio.h>
%}
digito [0-9]
naozero [1-9]
letrahexa [a-fA-F]
numero ((0x|0X)({digito}|{letrahexa}){1,8})
%%
{numero}	{ printf("Encontrado numero: %s\n", yytext); }
%%
int main() { yylex(); return 0; }
int yywrap() { return -1; }
