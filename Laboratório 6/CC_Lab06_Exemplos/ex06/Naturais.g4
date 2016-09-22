lexer grammar Naturais;

NUMBER: '0'|'1'..'9'('0'..'9')*;
WS     : [ \t\r\n]+ -> skip ;  // At least one whitespace char; don't make token
