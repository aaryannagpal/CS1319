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

DIGIT       [0-9]
NON_DIGIT   [a-zA-Z_]

IDENTIFIER  ({NON_DIGIT})({DIGIT}|{NON_DIGIT})*

SIGN                [+-]
NONZERO_DIGIT       [1-9]
ZERO_DIGIT          [0]

INTEGER_CONSTANT    ({ZERO_DIGIT})|({SIGN}?{NONZERO_DIGIT}{DIGIT}*)

ESCAPE_SEQUENCE     [\'\"?\\abfnrtv]
C_CHAR              ({ESCAPE_SEQUENCE})|([^\'\\\n])
CHAR_SEQUENCE       {C_CHAR}+

CHARACTER_CONSTANT  ([\'])({CHAR_SEQUENCE})([\'])

CONSTANT            ({INTEGER_CONSTANT})|({CHARACTER_CONSTANT})

S_CHAR              ({ESCAPE_SEQUENCE})|([^\"\\\n])
S_CHAR_SEQUENCE     {S_CHAR}*

STRING_LITERAL     ([\"])({S_CHAR_SEQUENCE})([\"])

PUNCTUATOR (\[|\]|\(|\)|\{|\}|&|\*|\+|-|\/|%|!|\?|<|>|<=|>=|==|!=|&&|\|\||=|->|\,|;|\:)

SINGLE_LINE_COMMENT    (\/\/)([^\n])*
MULTI_LINE_COMMENT     (\/\*)([^\*]|\*[^\/])*(\*\/)

COMMENT             ({MULTI_LINE_COMMENT})|({SINGLE_LINE_COMMENT})

WHITESPACE  [ \s\t\n]

%%
{CHAR}      {printf("<KEYWORD, %s>\n", yytext);}
{ELSE}      {printf("<KEYWORD, %s>\n", yytext);}
{FOR}       {printf("<KEYWORD, %s>\n", yytext);}
{IF}        {printf("<KEYWORD, %s>\n", yytext);}
{INT}       {printf("<KEYWORD, %s>\n", yytext);}
{RETURN}    {printf("<KEYWORD, %s>\n", yytext);}
{VOID}      {printf("<KEYWORD, %s>\n", yytext);}

{IDENTIFIER}            {printf("<IDENTIFIER, %s>\n", yytext);}

{CONSTANT}              {printf("<CONSTANT, %s>\n", yytext);}

{STRING_LITERAL}        {printf("<STRING LITERAL, %s>\n", yytext);}
{PUNCTUATOR}            {printf("<PUNCTUATOR, %s>\n", yytext);}
{COMMENT}               /* ignore comments */
{WHITESPACE}            /* ignore whitespace */
.                       { printf("<INVALID TOKEN, %s>\n", yytext); return -1;}
%%

int yywrap() {
    return 1;
}
