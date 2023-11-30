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

    int paranum;
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
    expression_opt

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

%type <paranum> 
    argument_expression_list 
    argument_expression_list_opt
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
                                
                                char *value = (char *)malloc(sizeof(char) * 10);
                                sprintf(value, "%d", $1);
                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, value, size_of_int, TEMP, 0, NULL);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                                printf("primary-expression - interger const\n");
                            }
    | CHARACTER_CONSTANT    {
                                $$ = (Expression *)malloc(sizeof(Expression));
                                $$->loc = gentemp();
                                
                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup($1);

                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_CHAR, value, size_of_char, TEMP, 0, NULL);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                                printf("primary-expression - char detected\n");
                            }
    | STRING_LITERAL        {
                                $$ = (Expression *)malloc(sizeof(Expression));
                                $$->loc = gentemp();
                                
                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup($1);

                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_CHAR, value, size_of_char, TEMP, 0, NULL);
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
                                                                    $$->loc->arrayName = $1->loc->name;
                                                                    printf("postfix-expression - normal %s\n", $$->loc->name);
                                                                }
    | postfix_expression '[' expression ']'                     {
                                                                    $$ = (Expression *)malloc(sizeof(Expression));
                                                                    $$->loc = $3->loc;
                                                                    $$->loc->arrayName = $1->loc->name; 
                                                                    $$->isArray = true;
                                                                    printf("postfix-expression - array\n");
                                                                }
    | postfix_expression '(' argument_expression_list_opt ')'   {
                                                                    $$ = (Expression *)malloc(sizeof(Expression));
                                                                    
                                                                    if ($1->loc->nested_table == NULL){
                                                                        yyerror("Function not defined");
                                                                    }
                                                                    $$->loc = gentemp();
                                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $1->loc->type, NULL, $1->loc->size, TEMP, 0, NULL);
                                                                    $$->loc->arrayName = $1->loc->name;
                                                                    emit(CALL, $$->loc->name, $1->loc->name, NULL);
                                                                    
                                                                    printf("postfix-expression - function\n");
                                                                }
    | postfix_expression ARROW IDENTIFIER                       {printf("postfix-expression\n");}
    ;

argument_expression_list_opt:
    argument_expression_list    {
                                    $$ = $1;
                                }
    |                           {
                                    $$ = 0;
                                }
    ;

argument_expression_list:
    assignment_expression                                   {
                                                                $$ = 1;
                                                                emit(PARAM, $1->loc->name, NULL, NULL);
                                                                printf("argument-expression-list - param\n");
                                                            }
    | argument_expression_list ',' assignment_expression    {
                                                                $$ = $1 + 1;
                                                                emit(PARAM, $3->loc->name, NULL, NULL);
                                                                printf("argument-expression-list - n-param\n");
                                                            }
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
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_PTR, NULL, size_of_pointer, TEMP, 0, $$->loc->name);
                                                    emit(ADDR, $$->loc->arrayName, $2->loc->arrayName, NULL);
                    
                                                    printf("unary-expression - &\n");
                                                    break;
                                                
                                                case '*':
                                                    $$->isPointer = true;
                                                    $$->loc = gentemp();
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $2->loc->type, NULL, $2->loc->size, TEMP, 0, $$->loc->name);
                                                    $$->loc->arrayName = $2->loc->arrayName;
                                                    emit(PTR_ASSIGN, $$->loc->name, $2->loc->arrayName, NULL);
                    
                                                    break;

                                                case '+':
                                                    $$ = $2;
                                                    printf("unary-expression - +\n");
                                                    break;

                                                case '-':
                                                    $$->loc = gentemp();
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $2->loc->type, NULL, $2->loc->size, TEMP, 0, $$->loc->name);
                                                    emit(UMINUS, $$->loc->arrayName, $2->loc->arrayName, NULL);
                    
                                                    printf("unary-expression - -\n");
                                                    break;

                                                case '!':
                                                    if ($2->isBoolean){
                                                        $$->isBoolean = true;
                                                        //copyArray($2->trueList, $$->falseList, MAXLIST);
                                                        //copyArray($2->falseList, $$->trueList, MAXLIST);
                                                        $$->loc = $2->loc;
                                                        $$->loc->arrayName = $2->loc->arrayName;
                                                        printf("unary-expression - !\n");

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
                                                                $$->loc = gentemp();
                                                                $$->loc = update_symboltable(current_table, $$->loc->name, $1->loc->type, NULL, $1->loc->size, TEMP, 0, NULL);
                                                                emit(READIDX, $$->loc->name, $1->loc->arrayName, $1->loc->name);
                                                                $1->isArray = false;
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
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(MULT, $$->loc->name, $1->loc->name, $3->loc->name);
                            
                                                            printf("multiplicative-expression - Multiply\n");
                                                        }
    | multiplicative_expression '/' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            $$->loc = gentemp();
                                                            
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(DIV, $$->loc->name, $1->loc->name, $3->loc->name);
                            
                                                            printf("multiplicative-expression - Divide\n");
                                                        }
    | multiplicative_expression '%' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            $$->loc = gentemp();
                                                            
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
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
                                                            
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);
                                                            emit(PLUS, $$->loc->name, $1->loc->name, $3->loc->name);
                            
                                                            printf("additive-expression - addition\n");
                                                        }
    | additive_expression '-' multiplicative_expression {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                               yyerror("Type mismatch");
                                                            }
                                                            $$ = (Expression *)malloc(sizeof(Expression));
                                                            $$->loc = gentemp();
                                                            
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);
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
                                                            emit(WRITEIDX, $1->loc->arrayName, $1->loc->name, $3->loc->name);
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
                                printf("%s\n", $$->loc->name);
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
                                            //printf("%p\n", current_table);
                                            if($1->type == TYPE_INT || $1->type == TYPE_CHAR || $1->type == TYPE_PTR || $1->type == TYPE_INT_PTR || $1->type == TYPE_CHAR_PTR || $1->type == TYPE_VOID_PTR){
                                                if ($1->type == TYPE_PTR || $1->type == TYPE_INT_PTR || $1->type == TYPE_CHAR_PTR || $1->type == TYPE_VOID_PTR){
                                                    $1->size = size_of_pointer;
                                                }
                                                //if ($1->arraySize != 0){
                                                //    $1->size = $1->arraySize * $1->size;
                                                //}
                                                update_symboltable(current_table, $1->name, $1->type, 0, $1->size, GLOBAL, $1->arraySize, NULL);
                                                printf("init-declarator - value initialized in global\n");
                                            }
                                            else{
                                                printf("$1->type = %d\n", $1->type);
                                                yyerror("Invalid type");
                                            }
                                        }
                                        else{
                                            printf("init-declarator - value not globally initialized\n");
                                        }
                                    }
    | declarator '=' initializer    {
                                        if ($3->value != NULL){
                                            $1->value = $3->value;
                                        }
                                        if ($1->type == TYPE_INT_PTR || $1->type == TYPE_CHAR_PTR || $1->type == TYPE_VOID_PTR){
                                            emit(PTR_ASSIGN, $1->name, $3->name, NULL);
                                        }
                                        else if ($1->arraySize != 0){
                                            emit(WRITEIDX, $1->name, $1->arrayName, $3->name);
                                        }
                                        else{
                                            emit(ASSIGN, $1->name, $3->name, NULL);
                                        }
        
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
                                            $$->size = size_of_pointer;
                                            printf("declarator - pointer and %d\n", $$->type);
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
    IDENTIFIER                                          {   
                                                            $$ = (symbol *)malloc(sizeof(symbol));
                                                            data_type dType = pop(&dTypeStack);
                                                            printf("Checking for: %s\n", $1->name);
                                                            if (current_table != global_table){
                                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, LOCAL, 0, NULL);
                                                            }
                                                            else{
                                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, NONE, 0, NULL);
                                                            }
                                                            $$ = $1;
                                                            printf("direct-declarator - %s\n", $$->name);
                                                        }
    | IDENTIFIER '['INTEGER_CONSTANT']'                 {   
                                                            $$ = (symbol *)malloc(sizeof(symbol));
                                                            data_type dType = pop(&dTypeStack);
                                                            printf("Checking for: %s\n", $1->name);
                                                            if (current_table != global_table){
                                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, LOCAL, $3, $1->name);
                                                            }
                                                            else{
                                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, NONE, $3, $1->name);
                                                            }
                                                            $$->arrayName = $1->name;
                                                            $$ = $1;
                                                            printf("direct-declarator - array\n");
                                                        }
    | IDENTIFIER '('create_table parameter_list_opt')'  {   
                                                            table_name = strdup($1->name);
                                                            data_type dType = pop(&dTypeStack);
                                                            $1 = update_symboltable(global_table, $1->name, dType.type, 0, 0, FUNCTION, 0, NULL);

                                                            if (dType.type != TYPE_VOID){
                                                                //print_symboltable(current_table);
                                                                symbol *RV = symlook(current_table, "retVal");
                                                                RV = update_symboltable(current_table, RV->name, dType.type, 0, dType.size, LOCAL, 0, NULL);
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
                                                $3 = update_symboltable(current_table, $3->name, dType.type - TYPE_PTR, 0, size_of_pointer, PARAMETER, 0, NULL);
                                                // add to parameter list
                                            
                                                printf("parameter-declaration - incom\n");
                                            }
    | type_specifier IDENTIFIER             {   
                                                data_type dType = pop(&dTypeStack);
                                                $2 = update_symboltable(current_table, $2->name, dType.type, 0, dType.size, PARAMETER, 0, NULL);
                                                printf("parameter-declaration - incom\n");
                                            }
    | type_specifier pointer                {
                                                data_type dType = pop(&dTypeStack);
                                                printf("parameter-declaration - no id *\n");
                                            }
    | type_specifier                        {   
                                                data_type dType = pop(&dTypeStack);
                                                printf("parameter-declaration - no id\n");
                                            }
    ;

identifier_opt:
    IDENTIFIER
    |
    ;

initializer:
    assignment_expression   {   
                                $$ = $1->loc;
                                printf("initializer - normal\n");
                            }
    ;

/*statements*/

statement:
    compound_statement      {printf("statement\n");}
    | expression_statement  {
                                $$ = (Statement *)malloc(sizeof(Statement));
                                $$->nextlist = $1->nextlist;
                                printf("statement COME BACK\n");
                            }
    | selection_statement   {printf("statement\n");}
    | iteration_statement   {printf("statement\n");}
    | jump_statement        {
                                $$ = $1;
                                printf("statement - jumped\n");
                            }
    ;

compound_statement:
    '{'block_item_list_opt'}'   {
                                    $$ = $2;
                                    printf("compound-statement - normal\n");
                                }
    ;

block_item_list_opt:
    block_item_list {
                        $$ = $1;
                        printf("block-item-list-opt - normal\n");
                    }
    |               {
                        
                        printf("block-item-list-opt - empty\n");
                    }
    ;

block_item_list:
    block_item                      {
                                        $$ = $1;
                                        printf("block-item-list - normal\n");
                                    }
    | block_item_list block_item    {
                                        $$ = $2;

                                        backpatch($1->nextlist, next_instr);
                                        printf("block-item-list - backpatch\n");
                                    }
    ;

block_item:
    declaration {
                    $$ = (Statement *)malloc(sizeof(Statement));
                    
                    printf("block-item - declaration\n");
                }
    | statement {
                    $$ = $1;
                    printf("block-item - statement\n");
                }
    ;

expression_statement:
    expression ';'  {   
                        $$ = $1;
                        printf("expression-statement - incomp\n");
                    }
    | ';'           {
                        $$ = (Expression *)malloc(sizeof(Expression));
                        printf("expression-statement - null\n");
                    }
    ;

expression_opt:
    expression  {
                    $$ = $1;
                    printf("expression-opt - normal\n");
                }
    |           {
                    //$$ = NULL;
                    printf("expression-opt - null\n");
                }
    ;

selection_statement:
    IF '(' expression ')' statement                     {printf("selection-statement\n");}
    | IF '(' expression ')' statement ELSE statement    {printf("selection-statement\n");}
    ;

iteration_statement:
    FOR '(' expression_opt ';' expression_opt ';' expression_opt ')' statement  {printf("iteration-statement\n");}
    ;

jump_statement:
    RETURN expression ';'       {
                                    symbol *RV = searchTable(current_table, "retVal");
                                    if (RV == NULL){
                                        yyerror("Return value mismatch.");
                                    }
                                    else{
                                        if ($2->loc->type != RV->type){
                                            yyerror("Return value mismatch.");
                                        }
                                        else{
                                            $$ = (Statement *)malloc(sizeof(Statement));
                                            
                                            emit(RET, $2->loc->name, NULL, NULL);
                                        }
                                    }
                                    printf("jump-statement - to change\n");
                                }
    | RETURN ';'                {   
                                    symbol *RV = searchTable(current_table, "retVal");
                                    if (RV != NULL){
                                        yyerror("Return value mismatch. Type not VOID");
                                    }
                                    else{
                                        $$ = (Statement *)malloc(sizeof(Statement));
                                        
                                        emit(RET, "", NULL, NULL);
                                        printf("jump-statement - null to change\n");
                                    }
                                }
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