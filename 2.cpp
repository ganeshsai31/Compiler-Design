#include <stdio.h>
#include <string.h>
#define MAX_LEN 1000

// Function to trim leading whitespace
void trimLeading(char *str) {
    int index = 0;
    while (str[index] == ' ' || str[index] == '\t')
        index++;
    if (index > 0)
        memmove(str, str + index, strlen(str) - index + 1);
}

// Function to check if a line is a comment
int isCommentLine(const char *line) {
    // Single-line comment
    if (strncmp(line, "//", 2) == 0)
        return 1;

    // Multi-line comment start
    if (strncmp(line, "/*", 2) == 0)
        return 2;

    return 0; 
	// Not a comment
}

int main() {
    FILE *fp;
    char line[MAX_LEN];
    int inMultilineComment = 0;

    char filename[100];
    printf("Enter input filename: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Unable to open file: %s\n", filename);
        return 1;
    }

    printf("Analyzing file for comments...\n\n");

    int lineNumber = 0;
    while (fgets(line, MAX_LEN, fp)) {
        lineNumber++;
        trimLeading(line);

        if (inMultilineComment) {
            printf("Line %d is part of a multi-line comment: %s", lineNumber, line);
            if (strstr(line, "*/") != NULL)
                inMultilineComment = 0;
            continue;
        }

        int commentType = isCommentLine(line);
        if (commentType == 1) {
            printf("Line %d is a single-line comment: %s", lineNumber, line);
        } else if (commentType == 2) {
            printf("Line %d starts a multi-line comment: %s", lineNumber, line);
            if (strstr(line, "*/") == NULL)
                inMultilineComment = 1;
        } else {
            printf("Line %d is not a comment.\n", lineNumber);
        }
    }

    fclose(fp);
    return 0;
}
