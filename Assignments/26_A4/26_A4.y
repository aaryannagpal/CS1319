%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "26_A4_translator.h"

    extern int yylex();

    void yyerror(char *s);
    extern char *yytext;
    
%}

%union {
    int intval;
    char *charval;
    symbol *symp;
    data_type *dtype;

    Expression *expr;
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

%token <symp> IDENTIFIER
%token <charval> STRING_LITERAL
%token <charval> CHARACTER_CONSTANT
%token <intval>  INTEGER_CONSTANT

%type <dtype> type_specifier

%type <expr> 
    expression
	primary_expression 
	postfix_expression
	unary_expression
	multiplicative_expression
	additive_expression
	relational_expression
	equality_expression
	logical_and_expression
	logical_or_expression
	conditional_expression
	assignment_expression
	expression_statement

%type <symp> 
    declarator
    direct_declarator
    identifier_opt
    init_declarator
    initializer
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
    type_specifier init_declarator ';'  {   
                                            printf("declaration - current_table is null\n");
                                        }
    ;

init_declarator:
    declarator                      {
                                        if (current_table == global_table){
                                            if($1->type == TYPE_INT || $1->type == TYPE_CHAR || $1->type == TYPE_PTR){
                                                $1->value = 0;
                                                update_symboltable(current_table, $1->name, $1->type, $1->value, $1->size);
                                                printf("init-declarator - value initialized\n");
                                                print_symboltable(current_table);
                                            }
                                        }
                                    }
    | declarator '=' initializer    {printf("init-declarator\n");}
    ;

type_specifier:
    VOID    {
                push(&dTypeStack, voidType);
                printf("type-specifier VOID - type %d and size %d\n", voidType.type, voidType.size);
            }
    | CHAR  {
                push(&dTypeStack, charType);
                printf("type-specifier CHAR - type %d and size %d\n", charType.type, charType.size);
            }
    | INT   {
                push(&dTypeStack, intType);
                printf("type-specifier INT- type %d and size %d\n", intType.type, intType.size);
            }
    ;

declarator:
    pointer_opt direct_declarator   {
                                        $$ = $2;
                                        printf("declarator - %d\n", $$->type);
                                    }
    ;

pointer_opt:
    pointer
    |
    ;

direct_declarator:
    IDENTIFIER                              {   
                                                $$ = (symbol *)malloc(sizeof(symbol));
                                                data_type dType = pop(&dTypeStack);
                                                printf("Checking for: %s\n", $1->name);
                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size);
                                                $$ = $1;
                                                printf("direct-declarator - %s\n", $$->name);
                                            }
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
    assignment_expression   {   
                                $$ = $1->loc;
                                printf("initializer - loc given\n");
                            }
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