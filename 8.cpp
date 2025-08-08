#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

struct Symbol {
    char name[50];
    char type[20];
    int size;
    int lineNo;
};

struct SymbolTable {
    struct Symbol symbols[MAX];
    int count;
} table;

void insertSymbol() {
    if (table.count >= MAX) {
        printf("Symbol table full!\n");
        return;
    }

    char name[50], type[20];
    int size, lineNo;

    printf("Enter symbol name: ");
    scanf("%s", name);

    for (int i = 0; i < table.count; i++) {
        if (strcmp(table.symbols[i].name, name) == 0) {
            printf("Symbol already exists!\n");
            return;
        }
    }

    printf("Enter type: ");
    scanf("%s", type);
    printf("Enter size: ");
    scanf("%d", &size);
    printf("Enter line number: ");
    scanf("%d", &lineNo);

    strcpy(table.symbols[table.count].name, name);
    strcpy(table.symbols[table.count].type, type);
    table.symbols[table.count].size = size;
    table.symbols[table.count].lineNo = lineNo;
    table.count++;

    printf("Symbol inserted successfully.\n");
}

void displaySymbols() {
    if (table.count == 0) {
        printf("Symbol table is empty.\n");
        return;
    }

    printf("\n%-15s %-10s %-10s %-10s\n", "Name", "Type", "Size", "Line No");
    printf("---------------------------------------------\n");

    for (int i = 0; i < table.count; i++) {
        printf("%-15s %-10s %-10d %-10d\n",
               table.symbols[i].name,
               table.symbols[i].type,
               table.symbols[i].size,
               table.symbols[i].lineNo);
    }
}

void searchSymbol() {
    char name[50];
    printf("Enter symbol name to search: ");
    scanf("%s", name);

    for (int i = 0; i < table.count; i++) {
        if (strcmp(table.symbols[i].name, name) == 0) {
            printf("Symbol found:\n");
            printf("Name: %s, Type: %s, Size: %d, Line No: %d\n",
                   table.symbols[i].name,
                   table.symbols[i].type,
                   table.symbols[i].size,
                   table.symbols[i].lineNo);
            return;
        }
    }

    printf("Symbol not found.\n");
}

void deleteSymbol() {
    char name[50];
    printf("Enter symbol name to delete: ");
    scanf("%s", name);

    for (int i = 0; i < table.count; i++) {
        if (strcmp(table.symbols[i].name, name) == 0) {
            for (int j = i; j < table.count - 1; j++) {
                table.symbols[j] = table.symbols[j + 1];
            }
            table.count--;
            printf("Symbol deleted successfully.\n");
            return;
        }
    }

    printf("Symbol not found.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n=== SYMBOL TABLE OPERATIONS ===\n");
        printf("1. Insert Symbol\n");
        printf("2. Display Symbol Table\n");
        printf("3. Search Symbol\n");
        printf("4. Delete Symbol\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertSymbol();
                break;
            case 2:
                displaySymbols();
                break;
            case 3:
                searchSymbol();
                break;
            case 4:
                deleteSymbol();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
