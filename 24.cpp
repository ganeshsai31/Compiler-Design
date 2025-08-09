%{
#include <stdio.h>
#include <string.h>

int valid = 0;
%}

/* Simple email regex:
   username: letters, digits, dot, underscore
   domain: letters, digits, dot, hyphen
   TLD: 2-6 letters
*/
EMAIL   [a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}

%%

^{EMAIL}$   { valid = 1; }

.*          { valid = 0; }

%%

int main()
{
    char input[100];
    printf("Enter an email address: ");
    scanf("%s", input);

    YY_BUFFER_STATE buffer = yy_scan_string(input);
    yylex();
    yy_delete_buffer(buffer);

    if (valid)
        printf("Valid email address.\n");
    else
        printf("Invalid email address.\n");

    return 0;
}

int yywrap() { return 1; }
