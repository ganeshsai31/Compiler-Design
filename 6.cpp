#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

void eliminateLeftRecursion(char nonTerminal, char productions[][MAX], int count) {
    char alpha[MAX][MAX], beta[MAX][MAX];
    int i, alphaCount = 0, betaCount = 0;

    for (i = 0; i < count; i++) {
        if (productions[i][0] == nonTerminal) {
            strcpy(alpha[alphaCount], productions[i] + 1); 
            alphaCount++;
        } else {
            strcpy(beta[betaCount], productions[i]);
            betaCount++;
        }
    }

    if (alphaCount == 0) {
        printf("No Left Recursion found in %c ? ", nonTerminal);
        for (i = 0; i < count; i++) {
            printf("%s", productions[i]);
            if (i < count - 1)
                printf(" | ");
        }
        printf("\n");
        return;
    }
    char newNonTerminal = nonTerminal + 39;

    printf("After eliminating Left Recursion:\n");
    
    printf("%c ? ", nonTerminal);
    for (i = 0; i < betaCount; i++) {
        printf("%s%c'", beta[i], newNonTerminal);
        if (i < betaCount - 1)
            printf(" | ");
    }
    printf("\n");

    printf("%c' ? ", newNonTerminal);
    for (i = 0; i < alphaCount; i++) {
        printf("%s%c'", alpha[i], newNonTerminal);
        if (i < alphaCount - 1)
            printf(" | ");
    }
    printf(" | e\n");
}

int main() {
    char nonTerminal;
    char productions[MAX][MAX];
    int n, i;

    printf("Enter Non-Terminal: ");
    scanf(" %c", &nonTerminal);

    printf("Enter number of productions for %c: ", nonTerminal);
    scanf("%d", &n);

    printf("Enter productions (no spaces), e.g., Aa or b:\n");
    for (i = 0; i < n; i++) {
        printf("%c ? ", nonTerminal);
        scanf("%s", productions[i]);
    }

    eliminateLeftRecursion(nonTerminal, productions, n);

    return 0;
}
