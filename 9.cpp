%{
%}
%%
"<"[^>]*">" {fprintf(yyout,"%s\n",yytext);}
. ;
%%
int yywrap()
{}
int main()
{
  yyin=fopen("html.txt","r");
  yyout=fopen("output.txt","w");
  yylex();
}
