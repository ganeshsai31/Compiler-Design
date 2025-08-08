#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    char result[10];
    char arg1[10];
    char op;
    char arg2[10];
} TAC;

int main() {
    int n, i;
    TAC code[MAX];
    char line[50];

    printf("Enter number of TAC statements: ");
    scanf("%d", &n);
    getchar(); 

    for (i = 0; i < n; i++) {
        printf("Enter TAC %d (e.g., t1 = a + b): ", i + 1);
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%s = %s %c %s", code[i].result, code[i].arg1, &code[i].op, code[i].arg2);
    }

    printf("\n--- Assembly-like Code Generated ---\n");
    for (i = 0; i < n; i++) {
        printf("MOV R%d, %s\n", i + 1, code[i].arg1);
        switch (code[i].op) {
            case '+':
                printf("ADD R%d, %s\n", i + 1, code[i].arg2);
                break;
            case '-':
                printf("SUB R%d, %s\n", i + 1, code[i].arg2);
                break;
            case '*':
                printf("MUL R%d, %s\n", i + 1, code[i].arg2);
                break;
            case '/':
                printf("DIV R%d, %s\n", i + 1, code[i].arg2);
                break;
            default:
                printf("// Unsupported operation\n");
        }
        printf("MOV %s, R%d\n", code[i].result, i + 1);
        printf("\n");
    }

    return 0;
}
