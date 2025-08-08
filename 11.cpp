#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float evaluate(float a, float b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

int precedence(char op) {
    switch(op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

float numStack[100];
char opStack[100];
int numTop = -1, opTop = -1;

void pushNum(float val) {
    numStack[++numTop] = val;
}

float popNum() {
    return numStack[numTop--];
}

void pushOp(char op) {
    opStack[++opTop] = op;
}

char popOp() {
    return opStack[opTop--];
}

void process() {
    float b = popNum();
    float a = popNum();
    char op = popOp();
    float result = evaluate(a, b, op);
    printf("Step: %.2f %c %.2f = %.2f\n", a, op, b, result);
    pushNum(result);
}

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int main() {
    char expr[100];
    printf("Enter a mathematical expression (no spaces): ");
    scanf("%s", expr);

    int i = 0;
    while (expr[i] != '\0') {
        if (isDigit(expr[i])) {
            float num = 0;
            while (isDigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            pushNum(num);
        } else if (expr[i] == '(') {
            pushOp(expr[i]);
            i++;
        } else if (expr[i] == ')') {
            while (opStack[opTop] != '(')
                process();
            popOp(); 
            i++;
        } else {
            while (opTop != -1 && precedence(opStack[opTop]) >= precedence(expr[i]))
                process();
            pushOp(expr[i]);
            i++;
        }
    }

    while (opTop != -1)
        process();

    printf("\nFinal Answer: %.2f\n", numStack[numTop]);

    return 0;
}
