%{
#include <stdio.h>
%}
letra [A-Z]
digito [0-9]
numero ([+]55[ ][(]{digito}{2}[)][ ]9{digito}{4}-{digito}{4})
%%
{numero}	{ printf("Encontrado numero: %s\n", yytext); }
%%
int main() { yylex(); return 0; }
int yywrap() { return -1; }
