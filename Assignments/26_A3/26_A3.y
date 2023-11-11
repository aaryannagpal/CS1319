%{
    #include <stdio.h>
    #include <stdlib.h>
    extern int yylex();
    void yyerror(char *s);
    extern char *yytext;

%}

%union {
    int val;
    char *name;
};

/*start symbol*/
%start translation_unit

/*terminals*/

%token CHAR // char
%token ELSE // else
%token FOR // for
%token IF // if
%token INT // int
%token RETURN // return
%token VOID // void

%token ARROW // ->
%token LESSTHANEQ // <=
%token GREATERTHANEQ // >=
%token EQ // ==
%token NEQ // !=
%token LOGICALAND // &&
%token LOGICALOR // ||

%token <name> IDENTIFIER
%token <name> STRING_LITERAL
%token <name> CHARACTER_CONSTANT
%token <val>  INTEGER_CONSTANT
%%
/*expressions*/

primary_expression:
    IDENTIFIER              {printf("primary-expression\n");}
    | INTEGER_CONSTANT      {printf("primary-expression\n");}
    | CHARACTER_CONSTANT    {printf("primary-expression\n");}
    | STRING_LITERAL        {printf("primary-expression\n");}
    | '(' expression ')'    {printf("primary-expression\n");}
    ;

postfix_expression:
    primary_expression                                          {printf("postfix-expression\n");}
    | postfix_expression '[' expression ']'                     {printf("postfix-expression\n");}
    | postfix_expression '(' argument_expression_list_opt ')'   {printf("postfix-expression\n");}
    | postfix_expression ARROW IDENTIFIER                       {printf("postfix-expression\n");}
    ;

argument_expression_list_opt:
    argument_expression_list
    |
    ;

argument_expression_list:
    assignment_expression                                   {printf("argument-expression-list\n");}
    | argument_expression_list ',' assignment_expression    {printf("argument-expression-list\n");}
    ;

unary_expression:
    postfix_expression                  {printf("unary-expression\n");}
    | unary_operator unary_expression   {printf("unary-expression\n");}
    ;

unary_operator:
    '&'     {printf("unary-operator\n");}
    | '*'   {printf("unary-operator\n");}
    | '+'   {printf("unary-operator\n");}
    | '-'   {printf("unary-operator\n");}
    | '!'   {printf("unary-operator\n");}
    ;

multiplicative_expression:
    unary_expression                                    {printf("multiplicative-expression\n");}
    | multiplicative_expression '*' unary_expression    {printf("multiplicative-expression\n");}
    | multiplicative_expression '/' unary_expression    {printf("multiplicative-expression\n");}
    | multiplicative_expression '%' unary_expression    {printf("multiplicative-expression\n");}
    ;

additive_expression:
    multiplicative_expression                           {printf("additive-expression\n");}
    | additive_expression '+' multiplicative_expression {printf("additive-expression\n");}
    | additive_expression '-' multiplicative_expression {printf("additive-expression\n");}
    ;

relational_expression:
    additive_expression                                         {printf("relational-expression\n");}
    | relational_expression '<' additive_expression             {printf("relational-expression\n");}
    | relational_expression '>' additive_expression             {printf("relational-expression\n");}
    | relational_expression LESSTHANEQ additive_expression      {printf("relational-expression\n");}
    | relational_expression GREATERTHANEQ additive_expression   {printf("relational-expression\n");}
    ;

equality_expression:
    relational_expression                           {printf("equality-expression\n");}
    | equality_expression EQ relational_expression  {printf("equality-expression\n");}
    | equality_expression NEQ relational_expression {printf("equality-expression\n");}
    ;

logical_and_expression:
    equality_expression                                     {printf("logical-AND-expression\n");}
    | logical_and_expression LOGICALAND equality_expression {printf("logical-AND-expression\n");}
    ;

logical_or_expression:
    logical_and_expression                                      {printf("logical-OR-expression\n");}
    | logical_or_expression LOGICALOR logical_and_expression    {printf("logical-OR-expression\n");}
    ;

conditional_expression:
    logical_or_expression                                               {printf("conditional-expression\n");}
    | logical_or_expression '?' expression ':' conditional_expression   {printf("conditional-expression\n");}
    ;

assignment_expression:
    conditional_expression                          {printf("assignment-expression\n");}
    | unary_expression '=' assignment_expression    {printf("assignment-expression\n");}
    ;

expression:
    assignment_expression   {printf("expression\n");}
    ;

/*declarations*/

declaration:
    type_specifier init_declarator ';' {printf("declaration\n");}
    ;

init_declarator:
    declarator                      {printf("init-declarator\n");}
    | declarator '=' initializer    {printf("init-declarator\n");}
    ;

type_specifier:
    VOID    {printf("type-specifier\n");}
    | CHAR  {printf("type-specifier\n");}
    | INT   {printf("type-specifier\n");}
    ;

declarator:
    pointer_opt direct_declarator   {printf("declarator\n");}
    ;

pointer_opt:
    pointer
    |
    ;

direct_declarator:
    IDENTIFIER                              {printf("direct-declarator\n");}
    | IDENTIFIER '['INTEGER_CONSTANT']'     {printf("direct-declarator\n");}
    | IDENTIFIER '('parameter_list_opt')'   {printf("direct-declarator\n");}
    ;

parameter_list_opt:
    parameter_list
    |
    ;

pointer:
    '*' {printf("pointer\n");}
    ;

parameter_list:
    parameter_declaration                       {printf("parameter-list\n");}
    | parameter_list ',' parameter_declaration  {printf("parameter-list\n");}
    ;

parameter_declaration:
    type_specifier pointer_opt identifier_opt   {printf("parameter-declaration\n");}
    ;

identifier_opt:
    IDENTIFIER
    |
    ;

initializer:
    assignment_expression   {printf("initializer\n");}
    ;

/*statements*/

statement:
    compound_statement      {printf("statement\n");}
    | expression_statement  {printf("statement\n");}
    | selection_statement   {printf("statement\n");}
    | iteration_statement   {printf("statement\n");}
    | jump_statement        {printf("statement\n");}
    ;

compound_statement:
    '{'block_item_list_opt'}'   {printf("compound-statement\n");}
    ;

block_item_list_opt:
    block_item_list
    |
    ;

block_item_list:
    block_item                      {printf("block-item-list\n");}
    | block_item_list block_item    {printf("block-item-list\n");}
    ;

block_item:
    declaration {printf("block-item\n");}
    | statement {printf("block-item\n");}
    ;

expression_statement:
    expression_opt ';'  {printf("expression-statement\n");}
    ;

expression_opt:
    expression
    |
    ;

selection_statement:
    IF '(' expression ')' statement                     {printf("selection-statement\n");}
    | IF '(' expression ')' statement ELSE statement    {printf("selection-statement\n");}
    ;

iteration_statement:
    FOR '(' expression_opt ';' expression_opt ';' expression_opt ')' statement  {printf("iteration-statement\n");}
    ;

jump_statement:
    RETURN expression_opt ';'   {printf("jump-statement\n");}
    ;
    
translation_unit:
    external_declaration                        {printf("translation-unit\n");}
    | translation_unit external_declaration     {printf("translation-unit\n");}
    ;

external_declaration:
    declaration             {printf("external-declaration\n");}
    | function_definition   {printf("external-declaration\n");}
    ;

function_definition:
    type_specifier declarator compound_statement    {printf("function-definition\n");}
    ;
%%


void yyerror(char *s) {
    printf("Error: %s on '%s'", s, yytext);
}