%{
/* nanoC Declarations */
%}

/* Regular Expression Definitions */
CHAR        "char"
ELSE        "else"
FOR         "for"
IF          "if"
INT         "int"
RETURN      "return"
VOID        "void"

IDENTIFIER  [a-zA-Z_][a-zA-Z_0-9]*

WHITESPACE  [ \s\t\n]

%%
{CHAR}      {printf("<KEYWORD, %s>\n", yytext);}
{ELSE}      {printf("<KEYWORD, %s>\n", yytext);}
{FOR}       {printf("<KEYWORD, %s>\n", yytext);}
{IF}        {printf("<KEYWORD, %s>\n", yytext);}
{INT}       {printf("<KEYWORD, %s>\n", yytext);}
{RETURN}    {printf("<KEYWORD, %s>\n", yytext);}
{VOID}      {printf("<KEYWORD, %s>\n", yytext);}

{IDENTIFIER}    {printf("<IDENTIFIER, %s>\n", yytext);}



{WHITESPACE}    {/* ignore whitespace */}
.               {printf("%s\n", yytext);}

%%

int yywrap() {
    return 1;
}