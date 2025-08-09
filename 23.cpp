%{
%}
%% 
[A-Z]+ {printf("\n CAPITAL WORD");}
[A-Za-z]+ {printf("\n not CAPITAL");}
%% 
int yywrap()
{} 
int main() 
{
printf("enter the input"); 
yylex();
}
