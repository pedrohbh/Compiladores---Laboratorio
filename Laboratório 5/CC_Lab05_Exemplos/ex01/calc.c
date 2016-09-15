
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

char token; // Global token variable.

// Function prototypes for recursive calls.
int expr(void);
int term(void);
int factor(void);

void error(void) {
    printf("Error\n");
    exit(1);
}

void match(char expected_token) {
    if (token == expected_token) {
        token = getchar();
    } else {
        error();
    }
}

int expr(void) {
    int temp = term();
    while (token == '+' || token == '-') {
        switch (token) {
            case '+':
                match('+');
                temp += term();
                break;
            case '-':
                match('-');
                temp -= term();
                break;
        }
    }
    return temp;
}

int term(void) {
    int temp = factor();
    while (token == '*') {
        match('*');
        temp *= factor();
    }
    return temp;
}

int factor(void) {
    int temp;
    if (token == '(') {
        match('(');
        temp = expr();
        match(')');
    } else if (isdigit(token)) {
        ungetc(token, stdin);
        scanf("%d", &temp);
        token = getchar();
    } else {
        error();
    }
    return temp;
}

int main(void) {
    int result;
    token = getchar(); // Load token with first char for look-ahead.
    result = expr();
    if (token == '\n') {
        printf("Result = %d\n", result);
    } else {
        error(); // Extraneous chars on line.
    }
    return 0;
}
