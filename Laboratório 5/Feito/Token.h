#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
 IF,
 THEN,
 ELSE,
 END, 
 REPEAT,
 UNTIL, 
 READ,
 WRITE,
 PLUS,
 MINUS,
 TIMES,
 OVER,
 EQ,
 LT,
 SEMI,
 ASSIGN,
 LP,
 RP,
 NUM,
 ID,
 ENTER
} TokenType;


#endif // TOKEN_H
