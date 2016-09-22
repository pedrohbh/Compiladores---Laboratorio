grammar Parser;

prog: start+;

start: expr ENTER;

expr: expr '+' expr | expr '-' expr | NUMBER;

NUMBER: ('0'..'9')+;
ENTER: '\n';
BLANCK: ' ' -> skip;
