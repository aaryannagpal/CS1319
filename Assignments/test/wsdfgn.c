%{
/* nanoC Declarations */
%}
/* Regular Expression Definitions */
CHAR "char"
ELSE "else"
FOR "for"
IF "if"
INT "int"
RETURN "return"
VOID "void"

IDENTIFIER [a-zA-Z]([a-zA-Z]|[0-9])*

INTEGER_CONSTANT [+|-]?[1-9][0-9]*
CHARACTER_CONSTANT ['][^\'\\\n]+[\'\"\?\\\a\b\f\n\r\t\v]*[']
STRING_LITERAL ["][^\"\\\n]|\\[abfnrtv\\\'\"\?]|\\[0-7]{1,3}|\\x[0-9a-fA-F]{1,2}["]

%%
[a-zA-Z]([a-zA-Z]|[0-9])*
            { printf("identifier: %s\n", yytext); }


0           { printf("constant: %s\n", yytext); }
[+-]?[1-9][0-9]*
            { printf("constant: %s\n", yytext); }
'([^'\\]|\\[abfnrtv\\'\?]|\\[0-7]{1,3}|\\x[0-9a-fA-F]{1,2})'
            { printf("constant: %s\n", yytext); }


/* String literals */
"([^"\\\n]|\\[abfnrtv\\'\"\?]|\\[0-7]{1,3}|\\x[0-9a-fA-F]{1,2})*"
            { printf("string-literal: %s\n", yytext); }

[()[\]{}->&*+/-=%!?:;<>,.]
            { printf("punctuator: %s\n", yytext); }

/* Comments */
"/*"        { /* ignore multi-line comment */ }
"*/"        { /* ignore multi-line comment */ }
"//"        { /* ignore single-line comment */ }

/* Whitespace */
[ \t\r\n]   { /* ignore whitespace */ }

%%

int main(int argc, char** argv) {
    yylex();
    return 0;
}