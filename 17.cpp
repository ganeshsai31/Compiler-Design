%{
%}
%%
[0-9]+"."[0-9]+ {printf("%s is a floating point constant\n",yytext);}
[0-9]+ {printf("%s is integer constant\n",yytext);}
.|\n {}
%%
int yywrap( )
{}
int main()
{
  printf("enter code:\n");
  yylex();
  printf("\n");
}
