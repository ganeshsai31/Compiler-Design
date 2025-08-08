#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_LEN 100

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
           ch == '=' || ch == '<' || ch == '>' || ch == '!';
}

int isKeyword(const char *str) {
    const char *keywords[] = {
        "int", "float", "if", "else", "while", "return", "for", "char", "double", "void"
    };
    for (int i = 0; i < 10; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void lexicalAnalyzer(FILE *fp) {
    char ch, buffer[MAX_LEN];
    int i = 0;

    while ((ch = fgetc(fp)) != EOF) {
    	
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            continue;
        }

        if (ch == '/' && (ch = fgetc(fp)) == '/') {
            while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            continue;
        }

        if (ch == '*' && buffer[i - 1] == '/') {
            while ((ch = fgetc(fp)) != EOF) {
                if (ch == '*' && fgetc(fp) == '/')
                    break;
            }
            i = 0;
            continue;
        }

        i = 0;

        if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                if (i < MAX_LEN - 1)
                    buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, fp); 
            if (isKeyword(buffer))
                printf("[Keyword\t%s]\n", buffer);
            else
                printf("[Identifier\t%s]\n", buffer);
        }

        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                if (i < MAX_LEN - 1)
                    buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, fp);
            printf("[Constant\t%s]\n", buffer);
        }

        else if (isOperator(ch)) {
            char op = ch;
            ch = fgetc(fp);
            if ((op == '=' || op == '!' || op == '<' || op == '>') && ch == '=') {
                printf("[Operator\t%c%c]\n", op, ch);
            } else {
                ungetc(ch, fp);
                printf("[Operator\t%c]\n", op);
            }
        }

        else if (ispunct(ch)) {
            printf("[Symbol\t\t%c]\n", ch);
        }
    }
}

int main() {
    char filename[50];
    FILE *fp;

    printf("Enter the input file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Cannot open file %s\n", filename);
        return 1;
    }

    printf("Lexical Analysis Output:\n");
    lexicalAnalyzer(fp);

    fclose(fp);
    return 0;
}
