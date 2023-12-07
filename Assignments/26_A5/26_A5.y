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

    int num;
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
    M

%type <unary_op> unary_operator

%type <num> 
    argument_expression_list 
    argument_expression_list_opt
    N
%%

/*table*/
create_table:   {
                    current_table = create_symboltable();
                }
                ;

change_table:   {
                    current_table = table_pointer;
                    emit(FUNC, table_name, NULL, NULL);
                }
                ;

M:  {   
        $$ = statCreate();
        $$->nextlist = newList(giveNextInstr());
        char *value = (char*)malloc(sizeof(char)*100);
        sprintf(value, "%d", giveNextInstr());
        emit(GOTO, "M", NULL, NULL);
    }
    ;

N: {    
        $$ = giveNextInstr();
    }
    ;
    

/*expressions*/

primary_expression:
    IDENTIFIER              {   
                                $$ = exprCreate();
                                $$->loc = $1;
                                $$->isBoolean = false;
                            }
    | INTEGER_CONSTANT      {
                                $$ = exprCreate();
                                $$->loc = gentemp();
                                char * value = (char*)malloc(sizeof(char)*100);
                                sprintf(value, "%d", $1);
                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, value, size_of_int, TEMP, 0, NULL);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                            }
    | CHARACTER_CONSTANT    {
                                $$ = exprCreate();
                                $$->loc = gentemp();
                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup($1);
                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_CHAR, value, size_of_char, TEMP, 0, NULL);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                            }
    | STRING_LITERAL        {
                                $$ = exprCreate();
                                $$->loc = gentemp();
                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup($1);
                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_CHAR, value, size_of_char, TEMP, 0, NULL);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                            }
    | '(' expression ')'    {
        
                                $$ = $2;
                            }
    ;

postfix_expression:
    primary_expression                                          {
                                                                    $$ = $1;
                                                                    $$->loc->arrayName = $1->loc->name;
                                                                }
    | postfix_expression '[' expression ']'                     {
                                                                    $$ = exprCreate();
                                                                    $$->loc = $3->loc;
                                                                    $$->loc->arrayName = $1->loc->name; 
                                                                    $$->isArray = true;
                                                                }
    | postfix_expression '(' argument_expression_list_opt ')'   {
                                                                    $$ = exprCreate();
                                                                    
                                                                    if ($1->loc->nested_table == NULL){
                                                                        yyerror("Function not defined");
                                                                    }

                                                                    char* value = (char*)malloc(sizeof(char)*100);
                                                                    if ($1->loc->type == TYPE_VOID){
                                                                        sprintf(value, "%d", $3);
                                                                        emit(CALL, NULL, $1->loc->name, value);
                                                                        $$->loc = $1->loc;
                                                                    }
                                                                    else{
                                                                        $$->loc = gentemp();
                                                                        $$->loc = update_symboltable(current_table, $$->loc->name, $1->loc->type, NULL, $1->loc->size, TEMP, 0, NULL);
                                                                        $$->loc->arrayName = $1->loc->name;
                                                                        sprintf(value, "%d", $3);
                                                                        emit(CALL, $$->loc->name, $1->loc->name, value);
                                                                    }
                                                                }
    | postfix_expression ARROW IDENTIFIER                       /*no rules for this*/
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
                                                            }
    | argument_expression_list ',' assignment_expression    {   
                                                                $$ = $1 + 1;
                                                                emit(PARAM, $3->loc->name, NULL, NULL);
                                                            }
    ;

unary_expression:
    postfix_expression                  {
                                            $$ = $1;    
                                        }
    | unary_operator unary_expression   {
                                            $$ = exprCreate();
                                            
                                            switch($1){
                                                case '&':
                                                    $$->loc = gentemp();
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_PTR, NULL, size_of_pointer, TEMP, 0, $$->loc->name);
                                                    emit(ADDR, $$->loc->arrayName, $2->loc->arrayName, NULL);
                                                    break;
                                                
                                                case '*':
                                                    $$->isPointer = true;
                                                    $$->loc = gentemp();
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $2->loc->type + TYPE_PTR, NULL, size_of_pointer, TEMP, 0, $$->loc->name);
                                                    $$->loc->arrayName = $2->loc->arrayName;
                                                    emit(PTR_ASSIGN, $$->loc->name, $2->loc->arrayName, NULL);
                                                    break;

                                                case '+':
                                                    $$ = $2;
                                                    break;

                                                case '-':
                                                    $$->loc = gentemp();
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $2->loc->type, NULL, $2->loc->size, TEMP, 0, $$->loc->name);
                                                    emit(UMINUS, $$->loc->arrayName, $2->loc->arrayName, NULL);
                                                    break;

                                                case '!':
                                                    if ($2->isBoolean){
                                                        $$->isBoolean = true;
                                                        $$->truelist = $2->falselist;
                                                        $$->falselist = $2->truelist;
                                                        $$->loc = $2->loc;
                                                        $$->loc->arrayName = $2->loc->arrayName;
                                                    }    
                                                    else{
                                                        yyerror("Value not Boolean");
                                                    }
                                                    break;
                                            }
                                        }
    ;

unary_operator:
    '&'     {
                $$ = '&'; 
            }
    | '*'   {
                $$ = '*'; 
            }
    | '+'   {
                $$ = '+'; 
            }
    | '-'   {
                $$ = '-'; 
            }
    | '!'   {
                $$ = '!'; 
            }
    ;

multiplicative_expression:
    unary_expression                                    {
                                                            $$ = exprCreate();
                                                            
                                                            if ($1->isArray){
                                                                $$->loc = gentemp();
                                                                $$->loc = update_symboltable(current_table, $$->loc->name, $1->loc->type, NULL, $1->loc->size, TEMP, 0, NULL);
                                                                emit(READIDX, $$->loc->name, $1->loc->arrayName, $1->loc->name);
                                                                $1->isArray = false;
                                                            }
                                                            else if ($1->isPointer){
                                                                $$->loc = $1->loc;
                                                            }
                                                            else{
                                                                $$ = $1;
                                                            }
                                                        }
    | multiplicative_expression '*' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = exprCreate();
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(MULT, $$->loc->name, $1->loc->name, $3->loc->name);
                                                        }
    | multiplicative_expression '/' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = exprCreate();
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(DIV, $$->loc->name, $1->loc->name, $3->loc->name);
                                                        }
    | multiplicative_expression '%' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = exprCreate();
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(MOD, $$->loc->name, $1->loc->name, $3->loc->name);
                                                        }
    ;

additive_expression:
    multiplicative_expression                           {
                                                            $$ = $1;
                                                        }
    | additive_expression '+' multiplicative_expression {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                               yyerror("Type mismatch");
                                                            }
                                                            $$ = exprCreate();
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);
                                                            emit(PLUS, $$->loc->name, $1->loc->name, $3->loc->name);
                                                        }
    | additive_expression '-' multiplicative_expression {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                               yyerror("Type mismatch");
                                                            }
                                                            $$ = exprCreate();
                                                            $$->loc = gentemp();
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);
                                                            emit(MINUS, $$->loc->name, $1->loc->name, $3->loc->name);
                                                        }
    ;

relational_expression:
    additive_expression                                         {
                                                                    $$ = $1;
                                                                }
    | relational_expression '<' additive_expression             {
                                                                    if ($1->loc->type != $3->loc->type){
                                                                        yyerror("Type mismatch");
                                                                    }
                                                                    else{
                                                                        $$ = exprCreate();
                                                                        $$->loc = $1->loc;
                                                                        $$->isBoolean = true;

                                                                        $$->truelist = newList(giveNextInstr());

                                                                        $$->falselist = newList(giveNextInstr()+1);

                                                                        emit(LT, NULL, $1->loc->name, $3->loc->name);
                                                                        emit(GOTO, "RE", NULL, NULL);
                                                                    }
                                                                }
    | relational_expression '>' additive_expression             {
                                                                    if ($1->loc->type != $3->loc->type){
                                                                        yyerror("Type mismatch");
                                                                    }
                                                                    else{
                                                                        $$ = exprCreate();
                                                                        $$->loc = $1->loc;
                                                                        $$->isBoolean = true;

                                                                        $$->truelist = newList(giveNextInstr());

                                                                        $$->falselist = newList(giveNextInstr()+1);

                                                                        emit(GT, "GT", $1->loc->name, $3->loc->name);
                                                                        emit(GOTO, "RE", NULL, NULL);
                                                                    }
                                                                }
    | relational_expression LESSTHANEQ additive_expression      {
                                                                    if ($1->loc->type != $3->loc->type){
                                                                        yyerror("Type mismatch");
                                                                    }
                                                                    else{
                                                                        $$ = exprCreate();
                                                                        $$->loc = $1->loc;
                                                                        $$->isBoolean = true;
                                                                        $$->truelist = newList(giveNextInstr());
                                                                        $$->falselist = newList(giveNextInstr()+1);
                                                                        emit(LTE, "", $1->loc->name, $3->loc->name);
                                                                        emit(GOTO, "RE", NULL, NULL);
                                                                    }
                                                                }
    | relational_expression GREATERTHANEQ additive_expression   {
                                                                    if ($1->loc->type != $3->loc->type){
                                                                        yyerror("Type mismatch");
                                                                    }
                                                                    else{
                                                                        $$ = exprCreate();
                                                                        $$->loc = $1->loc;
                                                                        $$->isBoolean = true;

                                                                        $$->truelist = newList(giveNextInstr());

                                                                        $$->falselist = newList(giveNextInstr()+1);

                                                                        emit(GTE, "", $1->loc->name, $3->loc->name);
                                                                        emit(GOTO, "RE", NULL, NULL);
                                                                    }
                                                                }
    ;

equality_expression:
    relational_expression                           {
                                                        $$ = $1;
                                                    }
    | equality_expression EQ relational_expression  {
                                                        if ($1->loc->type != $3->loc->type){
                                                            yyerror("Type mismatch");
                                                        }
                                                        else{
                                                            boolToInt($1);
                                                            boolToInt($3);
                                                            $$ = exprCreate();
                                                            $$->loc = $1->loc;
                                                            $$->isBoolean = true;
                                                            $$->truelist = newList(giveNextInstr());
                                                            $$->falselist = newList(giveNextInstr()+1);
                                                            emit(EQUAL, "", $1->loc->name, $3->loc->name);
                                                            emit(GOTO, "EQEXP", NULL, NULL);
                                                        }
                                                    }
    | equality_expression NEQ relational_expression {
                                                        if ($1->loc->type != $3->loc->type)
                                                        {
                                                            yyerror("Type mismatch");
                                                        }
                                                        else{
                                                            boolToInt($1);
                                                            boolToInt($3);
                                                            $$ = exprCreate();
                                                            $$->loc = $1->loc;
                                                            $$->isBoolean = true;
                                                            $$->truelist = newList(giveNextInstr());
                                                            $$->falselist = newList(giveNextInstr()+1);

                                                            emit(NE, "", $1->loc->name, $3->loc->name);
                                                            emit(GOTO, "EQEXP", NULL, NULL);
                                                        }
                                                    }
    ;

logical_and_expression:
    equality_expression                                     {
                                                                $$ = $1;
                                                            }
    | logical_and_expression LOGICALAND N equality_expression {
                                                                
                                                                intToBool($4);
                                                                intToBool($1);
                                                                $$ = exprCreate();
                                                                $$->loc = $1->loc;
                                                                $$->isBoolean = true;
                                                                backpatch($1->truelist, $3);
                                                                $$->truelist = $4->truelist;
                                                                $$->falselist = merge($1->falselist, $4->falselist);
                                                            }
    ;

logical_or_expression:
    logical_and_expression                                      {
                                                                    $$ = $1;
                                                                }
    | logical_or_expression LOGICALOR N logical_and_expression    {
                                                                    intToBool($4);
                                                                    intToBool($1);
                                                                    $$ = exprCreate();
                                                                    $$->loc = $1->loc;
                                                                    $$->isBoolean = true;
                                                                    backpatch($1->falselist, $3);
                                                                    $$->truelist = merge($1->truelist, $4->truelist);
                                                                    $$->falselist = $4->falselist;
                                                                }
    ;

conditional_expression:
    logical_or_expression                                               {
                                                                            $$ = $1;
                                                                        }
    | logical_or_expression M '?' N expression M ':' N conditional_expression   {
                                                                                    $$->loc = gentemp();
                                                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $5->loc->type, NULL, $1->loc->size, TEMP, 0, NULL);
                                                                                    emit(ASSIGN, $$->loc->name, $9->loc->name, NULL);
                                                                                    List *t = newList(giveNextInstr());
                                                                                    emit(GOTO, "ConExp", NULL, NULL);
                                                                                    backpatch($6->nextlist, giveNextInstr());
                                                                                    emit(ASSIGN, $$->loc->name, $5->loc->name, NULL);
                                                                                    List *l = newList(giveNextInstr());
                                                                                    l = merge(l, t);
                                                                                    emit(GOTO, "ConExp", NULL, NULL);
                                                                                    backpatch($2->nextlist, giveNextInstr());
                                                                                    intToBool($1);
                                                                                    backpatch($1->truelist, $4);
                                                                                    backpatch($1->falselist, $8);
                                                                                    backpatch(l, giveNextInstr());
                                                                                }
    ;

assignment_expression:
    conditional_expression                          {
                                                        $$ = $1;
                                                    }
    | unary_expression '=' assignment_expression    {
                                                        if($1->isArray){
                                                            emit(WRITEIDX, $1->loc->arrayName, $1->loc->name, $3->loc->name);
                                                        }
                                                        else if($1->isPointer){
                                                            emit(PTR_ASSIGN, $1->loc->name, $3->loc->name, NULL);
                                                        }
                                                        else{
                                                            emit(ASSIGN, $1->loc->name, $3->loc->name, NULL);
                                                        }
                                                        $$ = $3;
                                                    }
    ;

expression:
    assignment_expression   {
                                $$ = $1;
                            }
    ;

/*declarations*/

declaration:
    type_specifier init_declarator ';'  {   
                                            table_pointer = NULL;
                                        }
    ;

init_declarator:
    declarator                      {
                                        if (current_table == global_table){
                                            if($1->type == TYPE_INT || $1->type == TYPE_CHAR || $1->type == TYPE_PTR || $1->type == TYPE_INT_PTR || $1->type == TYPE_CHAR_PTR || $1->type == TYPE_VOID_PTR){
                                                if ($1->type == TYPE_PTR || $1->type == TYPE_INT_PTR || $1->type == TYPE_CHAR_PTR || $1->type == TYPE_VOID_PTR){
                                                    $1->size = size_of_pointer;
                                                }
                                                update_symboltable(current_table, $1->name, $1->type, 0, $1->size, GLOBAL, $1->arraySize, NULL);
                                            }
                                            else{
                                                yyerror("Invalid type");
                                            }
                                        }
                                        else{
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
                                    }
    ;

type_specifier:
    VOID    {
                push(&dTypeStack, voidType);
            }
    | CHAR  {
                push(&dTypeStack, charType);
            }
    | INT   {
                push(&dTypeStack, intType);
            }
    ;

declarator:
    pointer direct_declarator       {
                                        if ($2->nested_table != NULL){
                                            
                                            $$ = $2;
                                            int type = $$->type;
                                            $$->type = type - TYPE_PTR;
                                            $$->size = size_of_pointer;
                                            if ($$->type != TYPE_VOID){
                                                symbol *RV = symlook($$->nested_table, "retVal");
                                                RV = update_symboltable($$->nested_table, RV->name, $$->type, 0, $$->size, LOCAL, 0, NULL);
                                            }
                                        }
                                        else{
                                            $$ = $2;
                                            //$$->arraySize = 1;
                                            //$$->arrayName = $2->arrayName; // not sure if that would be array or not
                                            $$->type = $$->type - TYPE_PTR;
                                            $$->size = size_of_pointer;
                                        }
                                    }
    | direct_declarator             {
                                        $$ = $1;
                                    }
    ;

direct_declarator:
    IDENTIFIER                                          {   
                                                            $$ = create_symbol();
                                                            data_type dType = pop(&dTypeStack);
                                                            if (current_table != global_table){
                                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, LOCAL, 0, NULL);
                                                            }
                                                            else{
                                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, NONE, 0, NULL);
                                                            }
                                                            $$ = $1;
                                                        }
    | IDENTIFIER '['INTEGER_CONSTANT']'                 {   
                                                            $$ = create_symbol();
                                                            data_type dType = pop(&dTypeStack);
                                                            if (current_table != global_table){
                                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, LOCAL, $3, $1->name);
                                                            }
                                                            else{
                                                                $1 = update_symboltable(current_table, $1->name, dType.type, 0, dType.size, NONE, $3, $1->name);
                                                            }
                                                            $$->arrayName = $1->name;
                                                            $$ = $1;
                                                        }
    | IDENTIFIER '('create_table parameter_list_opt')'  {   
                                                            table_name = strdup($1->name);
                                                            data_type dType = pop(&dTypeStack);
                                                            $1 = update_symboltable(global_table, $1->name, dType.type, 0, 0, FUNCTION, 0, NULL);
                                                            if (dType.type != TYPE_VOID){
                                                                symbol *RV = symlook(current_table, "retVal");
                                                                RV = update_symboltable(current_table, RV->name, $1->type, 0, dType.size, LOCAL, 0, NULL);
                                                            }
                                                            $1->nested_table = current_table;
                                                            table_pointer = current_table;
                                                            current_table = global_table;
                                                            $$ = $1;
                                                        }
    ;

parameter_list_opt:
    parameter_list
    |
    ;

pointer:
    '*' {} // maybe next time can directly manipulate the data type from here
    ;

parameter_list:
    parameter_declaration                       {
                                                }
    | parameter_list ',' parameter_declaration  {
                                                }
    ;

parameter_declaration:
    type_specifier pointer IDENTIFIER       {   

                                                data_type dType = pop(&dTypeStack);
                                                $3 = update_symboltable(current_table, $3->name, dType.type - TYPE_PTR, 0, size_of_pointer, PARAMETER, 0, NULL);
                                            }
    | type_specifier IDENTIFIER             {   
                                                data_type dType = pop(&dTypeStack);
                                                $2 = update_symboltable(current_table, $2->name, dType.type, 0, dType.size, PARAMETER, 0, NULL);
                                            }
    | type_specifier pointer                {
                                                data_type dType = pop(&dTypeStack);
                                            }
    | type_specifier                        {   
                                                data_type dType = pop(&dTypeStack);
                                            }
    ;

initializer:
    assignment_expression   {   
                                $$ = $1->loc;
                            }
    ;

/*statements*/

statement:
    compound_statement      {   
                                $$ = $1;
                            }
    | expression_statement  {
                                $$ = statCreate();
                                $$->nextlist = $1->nextlist;
                            }
    | selection_statement   {
                                $$ = $1;
                            }
    | iteration_statement   {
                                $$ = $1;
                            }
    | jump_statement        {
                                $$ = $1;
                            }
    ;

compound_statement:
    '{'block_item_list_opt'}'   {
                                    $$ = $2;
                                }
    ;

block_item_list_opt:
    block_item_list {
                        $$ = $1;
                    }
    |               {
                        $$ = statCreate();
                    }
    ;

block_item_list:
    block_item                      {
                                        $$ = $1;
                                    }
    | block_item_list N block_item  {
                                        $$ = $3;
                                        backpatch($1->nextlist, $2);
                                    }
    ;

block_item:
    declaration {
                    $$ = statCreate();
                }
    | statement {
                    $$ = $1;
                }
    ;

expression_statement:
    expression ';'  {   
                        $$ = $1;
                    }
    | ';'           {
                        $$ = exprCreate();
                    }
    ;

expression_opt:
    expression  {
                    $$ = $1;
                }
    |           {
                    $$ = exprCreate();
                    $$->nextlist = newList(-1); // a checker if expression is null
                }
    ;

selection_statement:
    IF '(' expression M ')' N statement M                   {  
                                                                backpatch($4->nextlist, giveNextInstr());
                                                                $3 = intToBool($3);
                                                                $$ = statCreate();
                                                                backpatch($3->truelist, $6);
                                                                List *t = merge($3->falselist, $7->nextlist);
                                                                $$->nextlist = merge($8->nextlist, t);
                                                            }
    | IF '(' expression M ')' N statement M ELSE N statement   {
                                                                backpatch($4->nextlist, giveNextInstr());
                                                                intToBool($3);
                                                                $$ = statCreate();
                                                                backpatch($3->truelist, $6);
                                                                backpatch($3->falselist, $10);
                                                                List *t = merge($7->nextlist, $8->nextlist);
                                                                $$->nextlist = merge($11->nextlist, t);
                                                            }
    ;

iteration_statement:
     FOR '(' expression_opt ';' N expression_opt ';' N expression_opt M ')' N statement  
                                                                                        {   
                                                                                            $$ = statCreate();
                                                                                            if ($6->nextlist != NULL){ 
                                                                                                // missing the middle expression, making it while loop
                                                                                                backpatch($10->nextlist, $12);
                                                                                                backpatch($13->nextlist, $8);
                                                                                                char *value = (char*)malloc(sizeof(char)*100);
                                                                                                sprintf(value, "%d", $5);
                                                                                                emit(GOTO, value, NULL, NULL);
                                                                                            }
                                                                                            else{
                                                                                                intToBool($6);
                                                                                                backpatch($6->truelist, $12);
                                                                                                backpatch($10->nextlist, $5);
                                                                                                backpatch($13->nextlist, $8);
                                                                                                char *value = (char*)malloc(sizeof(char)*100);
                                                                                                sprintf(value, "%d", $8);
                                                                                                emit(GOTO, value, NULL, NULL);
                                                                                                $$->nextlist = $6->falselist;
                                                                                            }
                                                                                        }    
    ;

jump_statement:
    RETURN expression ';'       {
                                    symbol *RV = searchTable(current_table, "retVal");

                                    if ($2->loc->type != RV->type){
                                        yyerror("Return value mismatch.");
                                    }
                                    else{
                                        $$ = statCreate();
                                        emit(RET, $2->loc->name, NULL, NULL);
                                    }
                                }
    | RETURN ';'                {   
                                    symbol *RV = searchTable(current_table, "retVal");
                                    if (RV != NULL){
                                        yyerror("Return value mismatch. Type not VOID");
                                    }
                                    else{
                                        $$ = statCreate();
                                        
                                        emit(RET, "", NULL, NULL);
                                    }
                                }
    ;
    
translation_unit:
    external_declaration                        {}
    | translation_unit external_declaration     {}
    ;

external_declaration:
    declaration             {}
    | function_definition   {}
    ;

function_definition:
    type_specifier declarator change_table compound_statement   {
                                                                    table_pointer = NULL;
                                                                    
                                                                    backpatch($4->nextlist, giveNextInstr());
                                                                    emit(FUNC_END, table_name, NULL, NULL);
                                                                    current_table = global_table;
                                                                }
    ;
%%


void yyerror(char *s) {
    printf("Error: %s on '%s'", s, yytext);
}