%{
#include <stdio.h>
%}
%x comment

%%
"{" BEGIN(comment);
<comment>\n { yylineno++; }
<comment>[^}]* { }
<comment>"}" BEGIN(INITIAL);
"if" { printf("%d: %s -> IF\n", yylineno, yytext ); }
"then" { printf("%d: %s -> THEN\n", yylineno, yytext ); }
"else" { printf("%d: %s -> ELSE\n", yylineno, yytext ); }
"end" { printf("%d: %s -> END\n", yylineno, yytext ); }
"repeat" { printf("%d: %s -> REPEAT\n", yylineno, yytext ); }
"until" { printf("%d: %s -> UNTIL\n", yylineno, yytext ); }
"read" { printf("%d: %s -> READ\n", yylineno, yytext ); }
"write" { printf("%d: %s -> WRITE\n", yylineno, yytext ); }
"+" { printf("%d: %s -> PLUS\n", yylineno, yytext ); }
"-" { printf("%d: %s -> MINUS\n", yylineno, yytext ); }
"*" { printf("%d: %s -> TIMES\n", yylineno, yytext ); }
"/" { printf("%d: %s -> OVER\n", yylineno, yytext ); }
"=" { printf("%d: %s -> EQ\n", yylineno, yytext ); }
"<" { printf("%d: %s -> LT\n", yylineno, yytext ); }
";" { printf("%d: %s -> SEMI\n", yylineno, yytext ); }
":=" { printf("%d: %s -> ASSIGN\n", yylineno, yytext ); }
"(" { printf("%d: %s -> LP\n", yylineno, yytext ); }
")" { printf("%d: %s -> RP\n", yylineno, yytext ); }
" " { }
\n { yylineno++; }
[0-9]+ { printf("%d: %s -> NUM\n", yylineno, yytext ); }
[a-zA-Z]+ { printf("%d: %s -> ID\n", yylineno, yytext ); }
%%
int main()
{
	yylex();
	return 0;
}
	
