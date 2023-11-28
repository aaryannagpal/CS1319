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
    Statement *stm;
    char unary_op;
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

%type <stm>
    statement
    compound_statement
    selection_statement
    iteration_statement
    jump_statement
    block_item
    block_item_list
    block_item_list_opt

%type <unary_op> unary_operator
%%

/*table*/
create_table:   {
                    current_table = create_symboltable();
                    printf("create_table - table created\n");
                }
                ;

change_table:   {
                    
                    current_table = table_pointer;
                    emit(FUNC, table_name, NULL, NULL);
                    printf("change_table - table changed\n");
                }

/*expressions*/

primary_expression:
    IDENTIFIER              {   
                                $$ = (Expression *)malloc(sizeof(Expression));
                                $$->loc = $1;
                                $$->isBoolean = false;
                                printf("primary-expression - identifer found\n");
                            }
    | INTEGER_CONSTANT      {
                                $$ = (Expression *)malloc(sizeof(Expression));
                                $$->loc = gentemp();
                                // printf("%d\n", $1);
                                char *value = (char *)malloc(sizeof(char) * 10);
                                sprintf(value, "%d", $1);
                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, value, size_of_int, NONE);
                                $$->isBoolean = false;
                                // printf("%s\n", value);
                                // print_symboltable(current_table);
                                emit(ASSIGN, $$->loc->name, value, NULL);
                                printf("primary-expression - interger const QUAD emitted\n");
                                // print_quad_array(QuadArray);
                            }
    | CHARACTER_CONSTANT    {
                                $$ = (Expression *)malloc(sizeof(Expression));
                                $$->loc = gentemp();

                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup($1);

                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_CHAR, value, size_of_char, NONE);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                                printf("primary-expression - char detected\n");
                            }
    | STRING_LITERAL        {
                                $$ = (Expression *)malloc(sizeof(Expression));
                                $$->loc = gentemp();

                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup($1);

                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_CHAR, value, size_of_char, NONE);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                                printf("primary-expression - string detected\n");

                            }
    | '(' expression ')'    {
                                $$ = $2;
                                printf("primary-expression - (id)\n");    
                            }
    ;

postfix_expression:
    primary_expression                                          {
                                                                    $$ = $1;
                                                                    printf("postfix-expression - normal\n");
                                                                }
    | postfix_expression '[' expression ']'                     {
                                                                    
                                                                    printf("postfix-expression - array\n");
                                                                }
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
    postfix_expression                  {
                                            $$ = $1;    
                                            printf("unary-expression - normal\n");
                                        }
    | unary_operator unary_expression   {
                                            $$ = (Expression *)malloc(sizeof(Expression));
                                            switch($1){
                                                case '&':
                                                    $$->loc = gentemp();
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_PTR, NULL, size_of_pointer, NONE);
                                                    emit(ADDR, $$->loc->name, $2->loc->name, NULL);
                                                    break;
                                                
                                                case '*':
                                                    $$->isPointer = true;
                                                    $$->loc = gentemp();
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $2->loc->type, NULL, $2->loc->size, NONE);
                                                    emit(PTR_ASSIGN, $$->loc->name, $2->loc->name, NULL);
                                                    break;

                                                case '+':
                                                    $$ = $2;
                                                    break;

                                                case '-':
                                                    $$->loc = gentemp();
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $2->loc->type, NULL, $2->loc->size, NONE);
                                                    emit(UMINUS, $$->loc->name, $2->loc->name, NULL);
                                                    break;

                                                case '!':
                                                    if ($2->isBoolean){
                                                        $$->isBoolean = true;
                                                        copyArray($2->trueList, $$->falseList, MAXLIST);
                                                        copyArray($2->falseList, $$->trueList, MAXLIST);
                                                        $$->loc = $2->loc;
                                                    }    
                                                    else{
                                                        yyerror("Value not Boolean");
                                                    }
                                                    break;
                                            }
                                            printf("unary-expression - unary\n");
                                        }
    ;

unary_operator:
    '&'     {
                $$ = '&'; 
                printf("unary-operator - &\n");
            }
    | '*'   {
                $$ = '*'; 
                printf("unary-operator - *\n");
            }
    | '+'   {
                $$ = '+'; 
                printf("unary-operator - +\n");
            }
    | '-'   {
                $$ = '-'; 
                printf("unary-operator - -\n");
            }
    | '!'   {
                $$ = '!'; 
                printf("unary-operator - !\n");
            }
    ;

multiplicative_expression:
    unary_expression                                    {
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            if ($1->isArray){
                                                                printf("multiplicative-expression - array\n");
                                                            }
                                                            else if ($1->isPointer){
                                                                $$->loc = $1->loc;
                                                                printf("multiplicative-expression - pointer\n");
                                                            }
                                                            else{
                                                                $$ = $1;
                                                                
                                                                printf("multiplicative-expression - normal\n");
                                                            }
                                                        }
    | multiplicative_expression '*' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, NONE);                                                            
                                                            emit(MULT, $$->loc->name, $1->loc->name, $3->loc->name);

                                                            printf("multiplicative-expression - Multiply\n");
                                                        }
    | multiplicative_expression '/' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, NONE);                                                            
                                                            emit(DIV, $$->loc->name, $1->loc->name, $3->loc->name);

                                                            printf("multiplicative-expression - Divide\n");
                                                        }
    | multiplicative_expression '%' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, NONE);                                                            
                                                            emit(MOD, $$->loc->name, $1->loc->name, $3->loc->name);

                                                            printf("multiplicative-expression - Modulo\n");
                                                        }
    ;

additive_expression:
    multiplicative_expression                           {
                                                            $$ = $1;
                                                            printf("additive-expression - normal\n");
                                                        }
    | additive_expression '+' multiplicative_expression {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                               yyerror("Type mismatch");
                                                            }
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, NONE);
                                                            emit(PLUS, $$->loc->name, $1->loc->name, $3->loc->name);

                                                            printf("additive-expression - addition\n");
                                                        }
    | additive_expression '-' multiplicative_expression {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                               yyerror("Type mismatch");
                                                            }
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, NONE);
                                                            emit(MINUS, $$->loc->name, $1->loc->name, $3->loc->name);

                                                            printf("additive-expression - minus\n");
                                                        }
    ;

relational_expression:
    additive_expression                                         {
                                                                    $$ = $1;
                                                                    printf("relational-expression - normal\n");
                                                                }
    | relational_expression '<' additive_expression             {printf("relational-expression\n");}
    | relational_expression '>' additive_expression             {printf("relational-expression\n");}
    | relational_expression LESSTHANEQ additive_expression      {printf("relational-expression\n");}
    | relational_expression GREATERTHANEQ additive_expression   {printf("relational-expression\n");}
    ;

equality_expression:
    relational_expression                           {
                                                        $$ = $1;
                                                        printf("equality-expression - normal\n");
                                                    }
    | equality_expression EQ relational_expression  {printf("equality-expression\n");}
    | equality_expression NEQ relational_expression {printf("equality-expression\n");}
    ;

logical_and_expression:
    equality_expression                                     {
                                                                $$ = $1;
                                                                printf("logical-AND-expression - normal\n");
                                                            }
    | logical_and_expression LOGICALAND equality_expression {printf("logical-AND-expression\n");}
    ;

logical_or_expression:
    logical_and_expression                                      {
                                                                    $$ = $1;
                                                                    printf("logical-OR-expression - normal\n");
                                                                }
    | logical_or_expression LOGICALOR logical_and_expression    {printf("logical-OR-expression\n");}
    ;

conditional_expression:
    logical_or_expression                                               {
                                                                            $$ = $1;
                                                                            printf("conditional-expression - normal\n");
                                                                        }
    | logical_or_expression '?' expression ':' conditional_expression   {printf("conditional-expression\n");}
    ;

assignment_expression:
    conditional_expression                          {
                                                        $$ = $1;
                                                        printf("assignment-expression - normal\n");
                                                    }
    | unary_expression '=' assignment_expression    {
                                                        if($1->isArray){
                                                            printf("assignment-expression - array \n");

                                                        }
                                                        else if($1->isPointer){
                                                            emit(PTR_ASSIGN, $1->loc->name, $3->loc->name, NULL);
                                                            printf("assignment-expression - pointer \n");
                                                        }
                                                        else{
                                                            emit(ASSIGN, $1->loc->name, $3->loc->name, NULL);
                                                            printf("assignment-expression - unary \n");
                                                        }
                                                        $$ = $3;
                                                    }
    ;

expression:
    assignment_expression   {
                                $$ = $1;
                                printf("expression - normal\n");
                            }
    ;

/*declarations*/

declaration:
    type_specifier init_declarator ';'  {   
                                            table_pointer = NULL;
                                            printf("declaration - table pointer null\n");
                                        }
    ;

init_declarator:
    declarator                      {
                                        if (current_table == global_table){
                                            printf("%p\n", current_table);
                                            if($1->type == TYPE_INT || $1->type == TYPE_CHAR || $1->type == TYPE_PTR){
                                                update_symboltable(current_table, $1->name, $1->type, 0, $1->size, NONE);
                                                printf("init-declarator - value initialized\n");
                                            }
                                        }
                                        else{
                                            printf("init-declarator - value not initialized\n");
                                        }
                                    }
    | declarator '=' initializer    {
                                        if ($3->value != NULL){
                                            $1->value = $3->value;
                                        }
                                        emit(ASSIGN, $1->name, $3->name, NULL);
                                        printf("init-declarator - value given to variable\n");
                                    }
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
    pointer direct_declarator       {
                                        if ($2->nested_table != NULL){
                                            printf("Implement for function\n");
                                        }
                                        else{
                                            $$ = $2;
                                            $$->type = $$->type - TYPE_PTR;
                                            printf("declarator - %d\n", $$->type);
                                        }
                                    }
    | direct_declarator             {
                                        $$ = $1;
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
                                                            $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, NONE);
                                                            $$ = $1;
                                                            printf("direct-declarator - %s\n", $$->name);
                                                        }
    | IDENTIFIER '['INTEGER_CONSTANT']'                 {printf("direct-declarator\n");}
    | IDENTIFIER '('create_table parameter_list_opt')'  {   
                                                            table_name = $1->name;
                                                            data_type dType = pop(&dTypeStack);
                                                            $$ = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, FUNCTION);

                                                            if (dType.type != TYPE_VOID){
                                                                symbol *temp = symlook(current_table, "retVal");
                                                                temp = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, NONE);
                                                            }

                                                            $1->nested_table = current_table;
                                                            table_pointer = current_table;
                                                            current_table = global_table;
                                                            $$ = $1;

                                                            printf("direct-declarator - function\n");
                                                        }
    ;

parameter_list_opt:
    parameter_list
    |
    ;

pointer:
    '*' {printf("pointer\n");}
    ;

parameter_list:
    parameter_declaration                       {
                                                    printf("parameter-list - Remove\n");
                                                }
    | parameter_list ',' parameter_declaration  {
                                                    printf("parameter-list - Remove\n");
                                                }
    ;

parameter_declaration:
    type_specifier pointer IDENTIFIER       {   

                                                data_type dType = pop(&dTypeStack);
                                                $3 = update_symboltable(current_table, $3->name, dType.type - TYPE_PTR, 0, dType.size, PARAMETER);
                                                // add to parameter list
                                            
                                                printf("parameter-declaration - incom\n");
                                            }
    | type_specifier IDENTIFIER             {   
                                                data_type dType = pop(&dTypeStack);
                                                $2 = update_symboltable(current_table, $2->name, dType.type, 0, dType.size, PARAMETER);
                                                printf("parameter-declaration - incom\n");
                                            }
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
    '{'block_item_list_opt'}'   {
                                    $$ = $2;
                                    printf("compound-statement - normal\n");
                                }
    ;

block_item_list_opt:
    block_item_list
    |
    ;

block_item_list:
    block_item                      {
                                        $$ = $1;
                                        printf("block-item-list - normal\n");
                                    }
    | block_item_list block_item    {printf("block-item-list\n");}
    ;

block_item:
    declaration {
                    $$ = (Statement *)malloc(sizeof(Statement));
                    printf("block-item - normal\n");
                }
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
    external_declaration                        {printf("translation-unit - remove\n");}
    | translation_unit external_declaration     {printf("translation-unit - remove\n");}
    ;

external_declaration:
    declaration             {printf("external-declaration - remove\n");}
    | function_definition   {printf("external-declaration - remove\n");}
    ;

function_definition:
    type_specifier declarator change_table compound_statement   {
                                                                    table_pointer = NULL;
                                                                    emit(FUNC_END, table_name, NULL, NULL);
                                                                    current_table = global_table;
                                                                    printf("function-definition - normal\n");
                                                                }
    ;
%%


void yyerror(char *s) {
    printf("Error: %s on '%s'", s, yytext);
}