%{
%}
%%
[6-9][0-9]{9} {printf("\n Mobile Number Valid\n");}
.+ {printf("\n Mobile number invalid\n");}
%%
int yywrap(void) {}
int main()
{
  printf("\n Enter mobile number:");
  yylex();
  printf("\n");
  return 0;
}
