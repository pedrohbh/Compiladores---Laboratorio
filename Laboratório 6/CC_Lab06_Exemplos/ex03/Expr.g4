grammar Expr; // Grammar for simple arithmetic expressions.

/** The start rule; begin parsing here. */
prog: stat+ ;

stat: expr NEWLINE ;

expr: expr ('+'|'-') expr
    | INT
    ;

INT :   [0-9]+ ;         // match integers
NEWLINE:'\r'? '\n' ;     // return newlines to parser (is end-statement signal)
WS  :   [ \t]+ -> skip ; // toss out whitespace
