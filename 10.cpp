#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *input;
int i = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error() {
    printf("Syntax Error at position %d: Unexpected character '%c'\n", i + 1, input[i]);
}

void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        error();
    }
}

void E() {
    T();
    Eprime();
}

void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    }
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
    }
}

void F() {
    if (input[i] == '(') {
        match('(');
        E();
        if (input[i] == ')')
            match(')');
        else
            error();
    } else if (isalpha(input[i])) {
        match(input[i]);
    } else {
        error();
    }
}

int main() {
    char expr[100];
    printf("Enter the input expression: ");
    scanf("%s", expr);

    input = expr;
    i = 0;

    E();

    if (input[i] == '\0') {
        printf("Input string '%s' is successfully parsed.\n", expr);
    } else {
        error();
    }

    return 0;
}
