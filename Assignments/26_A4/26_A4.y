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
                    printf("create_table - table created\n");
                }
                ;

change_table:   {
                    current_table = table_pointer;
                    emit(FUNC, table_name, NULL, NULL);
                    printf("change_table - table changed\n");
                }
                ;

M:  {   
        $$ = statCreate();
        $$->nextlist = newList(giveNextInstr());
        printf("COUNTER AT M %d\n", giveNextInstr());
        char *value = (char*)malloc(sizeof(char)*100);
        sprintf(value, "%d", giveNextInstr());
        emit(GOTO, "M", NULL, NULL);
        printf("M - normal\n");
    }
    ;

N: {    
        printf("NNN COUNTER SET TO %d\n", giveNextInstr());
        $$ = giveNextInstr();
    }
    ;
    

/*expressions*/

primary_expression:
    IDENTIFIER              {   
                                $$ = exprCreate();
                                $$->loc = $1;
                                $$->isBoolean = false;
                                
                                printf("primary-expression - identifer found\n");
                            }
    | INTEGER_CONSTANT      {
                                $$ = exprCreate();
                                $$->loc = gentemp();
                                char * value = (char*)malloc(sizeof(char)*100);
                                sprintf(value, "%d", $1);
                                
                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, value, size_of_int, TEMP, 0, NULL);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                                printf("primary-expression - interger const\n");
                            }
    | CHARACTER_CONSTANT    {
                                $$ = exprCreate();
                                $$->loc = gentemp();
                                
                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup($1);

                                $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_CHAR, value, size_of_char, TEMP, 0, NULL);
                                $$->isBoolean = false;
                                emit(ASSIGN, $$->loc->name, value, NULL);
                                printf("primary-expression - char detected\n");
                            }
    | STRING_LITERAL        {
                                $$ = exprCreate();
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
                                                                    $$ = exprCreate();
                                                                    $$->loc = $3->loc;
                                                                    $$->loc->arrayName = $1->loc->name; 
                                                                    $$->isArray = true;
                                                                    printf("postfix-expression - array\n");
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
                                                                        printf("KANYE %d for %s\n", $1->loc->type, $1->loc->name);
                                                                    }
                                                                    
                                                                    printf("AAAAA %d %s\n", $1->loc->type, $1->loc->name);
                                                                    printf("postfix-expression - function\n");
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
                                            $$ = exprCreate();
                                            
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
                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $2->loc->type + TYPE_PTR, NULL, size_of_pointer, TEMP, 0, $$->loc->name);
                                                    $$->loc->arrayName = $2->loc->arrayName;
                                                    emit(PTR_ASSIGN, $$->loc->name, $2->loc->arrayName, NULL);
                                                    printf("unary-expression - *\n");

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
                                                        $$->truelist = $2->falselist;
                                                        $$->falselist = $2->truelist;
                                                        $$->loc = $2->loc;
                                                        $$->loc->arrayName = $2->loc->arrayName;
                                                        printf("unary-expression - !\n");

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
                                                            $$ = exprCreate();
                                                            
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
                                                                //
                                                                printf("multiplicative-expression - normal\n");
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
                            
                                                            printf("multiplicative-expression - Multiply\n");
                                                        }
    | multiplicative_expression '/' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = exprCreate();
                                                            $$->loc = gentemp();
                                                            
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(DIV, $$->loc->name, $1->loc->name, $3->loc->name);
                            
                                                            printf("multiplicative-expression - Divide\n");
                                                        }
    | multiplicative_expression '%' unary_expression    {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            $$ = exprCreate();
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
                                                            $$ = exprCreate();
                                                            $$->loc = gentemp();
                                                            
                                                            $$->loc = update_symboltable(current_table, $$->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);
                                                            emit(PLUS, $$->loc->name, $1->loc->name, $3->loc->name);
                            
                                                            printf("additive-expression - addition\n");
                                                        }
    | additive_expression '-' multiplicative_expression {
                                                            if ($1->loc->type != TYPE_INT || $3->loc->type != TYPE_INT){
                                                               yyerror("Type mismatch");
                                                            }
                                                            $$ = exprCreate();
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
                                                                    printf("relational-expression - LT\n");
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
                                                                    printf("relational-expression - GT\n");
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
                                                                    printf("relational-expression - LTE\n");
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
                                                                    printf("relational-expression - GTE\n");
                                                                }
    ;

equality_expression:
    relational_expression                           {
                                                        $$ = $1;
                                                        printf("equality-expression - normal\n");
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
                                                        printf("equality-expression - EQ\n");
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

                                                        printf("equality-expression - NE\n");
                                                    }
    ;

logical_and_expression:
    equality_expression                                     {
                                                                $$ = $1;
                                                                printf("logical-AND-expression - normal\n");
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
                                                                printf("logical-AND-expression - using AND\n");
                                                            }
    ;

logical_or_expression:
    logical_and_expression                                      {
                                                                    $$ = $1;
                                                                    printf("logical-OR-expression - normal\n");
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
                                                                    printf("logical-OR-expression - using OR\n");
                                                                }
    ;

conditional_expression:
    logical_or_expression                                               {
                                                                            $$ = $1;
                                                                            printf("%s >> %d\n", $$->loc->name, $$->loc->type);
                                                                            printf("conditional-expression - normal\n");
                                                                        }
    | logical_or_expression M '?' N expression M ':' N conditional_expression   {
                                                                                    $$->loc = gentemp();
                                                                                    $$->loc = update_symboltable(current_table, $$->loc->name, $5->loc->type, NULL, $1->loc->size, TEMP, 0, NULL);
                                                                                    printf("%s >>>> %d\n", $$->loc->name, $$->loc->type);
                                                                                    
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

                                                                                    printf("conditional-expression\n");
                                                                                }
    ;

assignment_expression:
    conditional_expression                          {
                                                        $$ = $1;
                                                        printf("%s >>> %d\n", $$->loc->name, $$->loc->type);

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
                printf("type-specifier VOID\n");
            }
    | CHAR  {
                push(&dTypeStack, charType);
                printf("type-specifier CHAR\n");
            }
    | INT   {
                push(&dTypeStack, intType);
                printf("type-specifier INT\n");
            }
    ;

declarator:
    pointer direct_declarator       {
                                        if ($2->nested_table != NULL){
                                            
                                            $$ = $2;
                                            printf("FUNCTION TYPE: %s\n", $$->name);
                                            int type = $$->type;
                                            $$->type = type - TYPE_PTR;
                                            $$->size = size_of_pointer;
                                            
                                            if ($$->type != TYPE_VOID){
                                                symbol *RV = symlook($$->nested_table, "retVal");
                                                RV = update_symboltable($$->nested_table, RV->name, $$->type, 0, $$->size, LOCAL, 0, NULL);
                                            }
                                            printf("Implement for function\n");

                                        }
                                        else{
                                            $$ = $2;
                                            //$$->arraySize = 1;
                                            //$$->arrayName = $2->arrayName; // not sure if that would be array or not
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

direct_declarator:
    IDENTIFIER                                          {   
                                                            $$ = create_symbol();
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
                                                            $$ = create_symbol();
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
                                                            print_all_ST();
                                                            printf("LO for: %s == %d\n", $1->name, $1->type);

                                                            if (dType.type != TYPE_VOID){
                                                                //print_symboltable(current_table);
                                                                symbol *RV = symlook(current_table, "retVal");
                                                                RV = update_symboltable(current_table, RV->name, $1->type, 0, dType.size, LOCAL, 0, NULL);
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

initializer:
    assignment_expression   {   
                                $$ = $1->loc;
                                printf("initializer - normal\n");
                            }
    ;

/*statements*/

statement:
    compound_statement      {   
                                $$ = $1;
                                printf("statement - normal compound\n");
                            }
    | expression_statement  {
                                $$ = statCreate();
                                $$->nextlist = $1->nextlist;
                                printf("statement COME BACK\n");
                            }
    | selection_statement   {
                                $$ = $1;
                                printf("statement - selection\n");
                            }
    | iteration_statement   {
                                $$ = $1;
                                printf("statement\n");
                            }
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
                        $$ = statCreate();
                        printf("block-item-list-opt - empty\n");
                    }
    ;

block_item_list:
    block_item                      {
                                        $$ = $1;
                                        printf("block-item-list - normal\n");
                                    }
    | block_item_list N block_item    {
                                        $$ = $3;
                                        printf("WHAT THIS; %d\n" , $2);
                                        backpatch($1->nextlist, $2);
                                        printf("block-item-list - backpatch\n");
                                    }
    ;

block_item:
    declaration {
                    $$ = statCreate();                    
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
                        $$ = exprCreate();
                        printf("expression-statement - null\n");
                    }
    ;

expression_opt:
    expression  {
                    $$ = $1;
                    printf("expression-opt - normal\n");
                }
    |           {
                    $$ = exprCreate();
                    $$->nextlist = newList(-1); // a checker if expression is null
                    printf("expression-opt - null\n");
                }
    ;

selection_statement:
    IF '(' expression M ')' N statement M                   {  
                                                                backpatch($4->nextlist, giveNextInstr());
                                                                printf("COUNTER AT IF %d\n", giveNextInstr());
                                                                $3 = intToBool($3);
                                                                $$ = statCreate();
                                                                printf("WHAY THIS %d\n", $6);
                                                                backpatch($3->truelist, $6);

                                                                List *t = merge($3->falselist, $7->nextlist);

                                                                $$->nextlist = merge($8->nextlist, t);

                                                                printf("selection-statement - ongoing\n");
                                                            }
    | IF '(' expression M ')' N statement M ELSE N statement   {
                                                                printList($4->nextlist);
                                                                backpatch($4->nextlist, giveNextInstr());
                                                                intToBool($3);

                                                                $$ = statCreate();

                                                                printList($3->truelist);
                                                                printList($3->falselist);

                                                                backpatch($3->truelist, $6);
                                                                backpatch($3->falselist, $10);

                                                                printf("COUNTER AT ELSE %d\n", giveNextInstr());
                                                                printList($7->nextlist);
                                                                printList($8->nextlist);
                                                                printList($11->nextlist);

                                                                List *t = merge($7->nextlist, $8->nextlist);

                                                                printList(t);
                                                                $$->nextlist = merge($11->nextlist, t);
                                                                printf("selection-statement\n");
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
        printf("iteration-statement - normal\n");
    }    
    ;

jump_statement:
    RETURN expression ';'       {
                                    symbol *RV = searchTable(current_table, "retVal");

                                    if ($2->loc->type != RV->type){
                                        printf("Type mismatch %d and %d\n", $2->loc->type, RV->type);
                                        yyerror("Return value mismatch.");
                                    }
                                    else{

                                        $$ = statCreate();
                                        emit(RET, $2->loc->name, NULL, NULL);
                                        
                                    }
                                    
                                    printf("jump-statement - to change\n");
                                }
    | RETURN ';'                {   
                                    symbol *RV = searchTable(current_table, "retVal");
                                    if (RV != NULL){
                                        yyerror("Return value mismatch. Type not VOID");
                                    }
                                    else{
                                        $$ = statCreate();
                                        
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
                                                                    
                                                                    //if ($2->type == TYPE_VOID){
                                                                    //    backpatch($4->nextlist, giveNextInstr()-1);
                                                                    //}
                                                                    //else{
                                                                    //    backpatch($4->nextlist, giveNextInstr());
                                                                    //}
                                                                    
                                                                    
                                                                    printf("CHECK AT FUNC %d\n", giveNextInstr());
                                                                    printList($4->nextlist);
                                                                    backpatch($4->nextlist, giveNextInstr());
                                                                    emit(FUNC_END, table_name, NULL, NULL);


                                    
                                                                    current_table = global_table;
                                                                    printf("function-definition - normal\n");
                                                                }
    ;
%%


void yyerror(char *s) {
    printf("Error: %s on '%s'", s, yytext);
}