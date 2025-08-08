#include <stdio.h>
#include <string.h>
#define MAX 10
#define SIZE 100

void eliminateLeftFactoring(char nonTerminal, char productions[][SIZE], int count) {
    char commonPrefix[SIZE];
    int prefixFound = 0;

    int minLen = strlen(productions[0]);
    for (int i = 1; i < count; i++) {
        if ((int)strlen(productions[i]) < minLen)
            minLen = strlen(productions[i]);
    }

    for (int i = 0; i < minLen; i++) {
        char ch = productions[0][i];
        int allMatch = 1;
        for (int j = 1; j < count; j++) {
            if (productions[j][i] != ch) {
                allMatch = 0;
                break;
            }
        }
        if (allMatch) {
            commonPrefix[i] = ch;
            prefixFound = 1;
        } else {
            commonPrefix[i] = '\0';
            break;
        }
    }

    commonPrefix[minLen] = '\0';

    if (!prefixFound || strlen(commonPrefix) == 0) {
        printf("No left factoring needed for %c ? ", nonTerminal);
        for (int i = 0; i < count; i++) {
            printf("%s", productions[i]);
            if (i < count - 1)
                printf(" | ");
        }
        printf("\n");
        return;
    }

    char newNonTerminal = nonTerminal + 39;

    printf("After Left Factoring:\n");
    printf("%c ? %s%c'\n", nonTerminal, commonPrefix, newNonTerminal);

    printf("%c' ? ", newNonTerminal);
    for (int i = 0; i < count; i++) {
        char *suffix = productions[i] + strlen(commonPrefix);
        if (strlen(suffix) == 0)
            printf("e");
        else
            printf("%s", suffix);

        if (i < count - 1)
            printf(" | ");
    }
    printf("\n");
}

int main() {
    char nonTerminal;
    char productions[MAX][SIZE];
    int count;

    printf("Enter Non-Terminal: ");
    scanf(" %c", &nonTerminal);

    printf("Enter number of productions for %c: ", nonTerminal);
    scanf("%d", &count);

    printf("Enter productions (e.g., ab, acd, axy):\n");
    for (int i = 0; i < count; i++) {
        printf("%c ? ", nonTerminal);
        scanf("%s", productions[i]);
    }

    eliminateLeftFactoring(nonTerminal, productions, count);

    return 0;
}
