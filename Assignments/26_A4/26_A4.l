%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "26_A4_translator.h"
    #include "26_A4.tab.h"
    #include <string.h>

    extern YYSTYPE yylval;
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

INTEGER_CONSTANT    {ZERO_DIGIT}|{NONZERO_DIGIT}{DIGIT}*

ESCAPE_SEQUENCE     [\'\"?\\abfnrtv]
C_CHAR              (\\{ESCAPE_SEQUENCE})|([^\'\\\n])
CHAR_SEQUENCE       {C_CHAR}

CHARACTER_CONSTANT  ([\'])({CHAR_SEQUENCE})([\'])

CONSTANT            ({INTEGER_CONSTANT})|({CHARACTER_CONSTANT})

S_CHAR              (\\{ESCAPE_SEQUENCE})|([^\"\\\n])
S_CHAR_SEQUENCE     {S_CHAR}*

STRING_LITERAL     ([\"])({S_CHAR_SEQUENCE})([\"])

PUNCTUATOR (\[|\]|\(|\)|\{|\}|&|\*|\+|-|\/|%|!|\?|<|>|=|\,|;|\:)

SINGLE_LINE_COMMENT    (\/\/)([^\n])*
MULTI_LINE_COMMENT     (\/\*)([^\*]|\*[^\/])*(\*\/)

COMMENT             ({MULTI_LINE_COMMENT})|({SINGLE_LINE_COMMENT})

WHITESPACE  [ \s\t\n]

%%
{CHAR}      {return CHAR;}
{ELSE}      {return ELSE;}
{FOR}       {return FOR;}
{IF}        {return IF;}
{INT}       {return INT;}
{RETURN}    {return RETURN;}
{VOID}      {return VOID;}

{IDENTIFIER}            {
                            yylval.symp = symlook(current_table, yytext);
                            return IDENTIFIER;
                        }

{CHARACTER_CONSTANT}    {
                            yylval.charval = yytext;
                            return CHARACTER_CONSTANT;
                        }
{INTEGER_CONSTANT}      {
                            yylval.intval = atoi(yytext);
                            return INTEGER_CONSTANT;
                        }

{STRING_LITERAL}        {
                            yylval.charval = yytext;
                            return STRING_LITERAL;
                        }

"&&"                    {return LOGICALAND;}
"||"                    {return LOGICALOR;}
"<="                    {return LESSTHANEQ;}
">="                    {return GREATERTHANEQ;}
"=="                    {return EQ;}
"!="                    {return NEQ;}
"->"                    {return ARROW;}

{PUNCTUATOR}            {return yytext[0];}


{COMMENT}               /* ignore comments */
{WHITESPACE}            /* ignore whitespace */
.                       {return -1;}
%%

int yywrap() {
    return 1;
}
