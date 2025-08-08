#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

char input[MAX];
int tempVarCount = 1;

char* newTemp(char *temp) {
    sprintf(temp, "t%d", tempVarCount++);
    return temp;
}

int precedence(char op) {
    if (op == '^') return 3;
    else if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    return 0;
}

void generateTAC(char expr[]) {
    char operators[] = "+-*/";
    char exprCopy[MAX];
    strcpy(exprCopy, expr);

    int len = strlen(exprCopy);
    char left[MAX], right[MAX], op, temp[MAX];

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (exprCopy[i] != ' ')
            expr[j++] = exprCopy[i];
    }
    expr[j] = '\0';

    char lhs[10], rhs[MAX];
    sscanf(expr, "%[^=]=%s", lhs, rhs);

    while (1) {
        int maxPrec = -1, pos = -1;

        for (int i = 0; rhs[i] != '\0'; i++) {
            if (strchr(operators, rhs[i])) {
                int prec = precedence(rhs[i]);
                if (prec > maxPrec) {
                    maxPrec = prec;
                    pos = i;
                }
            }
        }

        if (pos == -1) break; 

        int l = pos - 1, r = pos + 1;

        while (l >= 0 && isalnum(rhs[l])) l--;
        strncpy(left, rhs + l + 1, pos - l - 1);
        left[pos - l - 1] = '\0';

        while (isalnum(rhs[r])) r++;
        strncpy(right, rhs + pos + 1, r - pos - 1);
        right[r - pos - 1] = '\0';

        newTemp(temp);
        printf("%s = %s %c %s\n", temp, left, rhs[pos], right);

        char newExpr[MAX] = "";
        strncat(newExpr, rhs, l + 1);
        strcat(newExpr, temp);
        strcat(newExpr, rhs + r);
        strcpy(rhs, newExpr);
    }

    printf("%s = %s\n", lhs, rhs);
}

int main() {
    printf("Enter an assignment statement (e.g., a = b + c * d):\n");
    fgets(input, MAX, stdin);

    input[strcspn(input, "\n")] = 0;

    generateTAC(input);

    return 0;
}
