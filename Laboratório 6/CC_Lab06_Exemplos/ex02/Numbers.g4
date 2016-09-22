lexer grammar Numbers; // For building a scanner only make sure to declare a lexer grammar.

// Grammar to distinguish numbers and non-numbers.

NUMBER : '0'|'1'..'9'('0'..'9')*;
NON_WS : ~(' '|'\t'|'\r'|'\n')+;
WS     : [ \t\r\n]+ -> skip ;  // At least one whitespace char; don't make token
