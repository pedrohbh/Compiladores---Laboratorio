
/* Simple integer arithmetic calculator implemented according to the
 * following EBNF grammar:
 *
 * <expr> -> <term> { <addop> <term> }
 * <addop> -> + | -
 * <term> -> <factor> { <mulop> <factor> }
 * <mulop> -> *
 * <factor> -> ( <expr> ) | NUMBER
 *
 * Input: a line of text from stdin.
 * Output: "Error" or the computed result.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"

TokenType token;  // Global token type variable.
int lval; // Global variable for number tokens.

TokenType yylex(); // Flex function.

// Function prototypes for recursive calls.
int expr(void);
int term(void);
int factor(void);

void error(void) {
    printf("Error\n");
    exit(1);
}

void match(int expected_token) {
    if (token == expected_token) {
        token = yylex();
    } else {
        error();
    }
}

int expr(void) {
    int temp = term();
    while (token == PLUS || token == MINUS) {
        switch (token) {
            case PLUS:
                match(PLUS);
                temp += term();
                break;
            case MINUS:
                match(MINUS);
                temp -= term();
                break;
            default:
                break;
        }
    }
    return temp;
}

int term(void) {
    int temp = factor();
    while (token == TIMES) {
        match(TIMES);
        temp *= factor();
    }
    return temp;
}

int factor(void) {
    int temp;
    if (token == LPAREN) {
        match(LPAREN);
        temp = expr();
        match(RPAREN);
    } else if (token == NUMBER) {
        temp = lval;
        token = yylex();
    } else {
        error();
    }
    return temp;
}

int main(void) {
    int result;
    token = yylex(); // Load token with first char for look-ahead.
    result = expr();
    if (token == ENTER) {
        printf("Result = %d\n", result);
    } else {
        error(); // Extraneous chars on line.
    }
    return 0;
}
