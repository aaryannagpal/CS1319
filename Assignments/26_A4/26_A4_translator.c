#include "26_A4_translator.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern void yyerror(char *s);
extern int yyparse();

symbol* create_symbol(){
    symbol *symb = (symbol *)malloc(sizeof(symbol));
    symb->name = NULL;
    symb->type = 0;
    symb->value = NULL;
    symb->size = 0;
    symb->offset = 0;
    symb->category = NONE;
    symb->nested_table = NULL;
    symb->next = NULL;
    symb->arraySize = 0;
    symb->arrayName = NULL;
    return symb;
}


symbol *create_symboltable(){
    symbol *table = (symbol *)malloc(sizeof(symbol));
    table->name = NULL;
    table->type = 0;
    table->value = NULL;
    table->size = 0;
    table->offset = 0;
    table->category = GLOBAL;
    table->nested_table = NULL;
    table->next = NULL;

    return table;
}

symbol *update_symboltable(symbol *table, char *name, enumtype type, char *value, int size, enumcat category, int arraySize, char *arrayName){
    // symbol *symb = table;
    symbol *temp = table;
    
    // printf("-->Updating symbol table entry for %s\n", name);
    
    while(temp != NULL){
        // printf("==>Comparing %s\n", temp->name);
        if(strcmp(temp->name, name) == 0){
            // printf("-->Found symbol table entry for %s\n", temp->name);
            temp->type = type;
            // printf("-->Value already present\n");
            switch(type){
                case TYPE_INT:
                    // printf("-->Int type\n");
                    temp->value = value;
                    // *(int*)temp->value = atoi(value);
                    break;
                case TYPE_CHAR:
                    temp->value = value;
                    break;
                case TYPE_PTR:
                    // printf("-->Pointer type\n");
                    temp->value = &value;
                    break;
            }
            temp->size = size;
            temp->category = category;
            temp->arraySize = arraySize;
            temp->arrayName = arrayName;
            printf("-->Updated %s\n", temp->name);
            
            // table = temp;
            // print_symboltable(table);
            return temp;
        }
        temp = temp->next;
    }
    // printf("-->Symbol table entry for %s not found.\n", name);
}

symbol *searchTable(symbol *table, char *name){
    symbol *temp = table;
    
    if (temp == NULL){
        // printf("-->Table empty therefore %s not found.\n", name);
        return NULL;
    }

    else{
        if (temp->name == NULL){
            // printf("-->Void Table empty therefore %s not found.\n", name);
            return NULL;
        }
    }

    while(temp->next != NULL){
        if(strcmp(temp->name, name) == 0){
            // printf("-->Found symbol table entry for %s\n", temp->name);
            return temp;
        }
        temp = temp->next;
    }
    
    if (strcmp(temp->name, name) == 0){
        // printf("-->Found symbol table entry for %s\n", temp->name);
        return temp;
    }

    // printf("-->Symbol table entry for %s not found.\n", name);
    return NULL;
}

symbol *symlook(symbol *table, char *name){
    symbol *symb = table;
    symbol *temp = global_table;

    // searching whatever table this is
    if (symb->name == NULL){ // First entry 
        symb->name = strdup(name);
        // symb->name = name;
        table = symb;
        // printf("\n\n");
        // // printf("-->Created first symbol table entry for %s\n", name);
        // // print_symboltable(table);
        // printf("\n\n");
        return table;
    }
    // printf("-->Table not empty! Moving on:\n");
    while(symb->next != NULL){
        if(strcmp(symb->name, name) == 0){
            // printf("-->Found symbol table entry for %s\n", name);
            // print_symboltable(symb);
            return symb;
        }
        symb = symb->next;
    }

    if (strcmp(symb->name, name) == 0){
        // printf("-->Found symbol table entry for %s\n", name);
        // print_symboltable(symb);
        return symb;
    }

    // searching global if not found in current table
    

    if (temp->name == NULL){ // First entry 
        temp->name = strdup(name);
        // symb->name = name;
        table = temp;
        printf("\n\n");
        // printf("-->Created first global symbol table entry for %s\n", name);
        // print_symboltable(table);
        printf("\n\n");
        return table;
    }
    // printf("-->Global table not empty! Moving on:\n");
    while(temp->next != NULL){
        printf("==>Comparing %s\n", temp->name);
        if(strcmp(temp->name, name) == 0){
            // printf("-->Found global symbol table entry for %s\n", name);
            // print_symboltable(symb);
            return temp;
        }
        temp = temp->next;
    }
    if (strcmp(temp->name, name) == 0){
        // printf("-->Found global symbol table entry for %s\n", name);
        // print_symboltable(symb);
        return temp;
    }




    // printf("-->Symbol table entry for %s not found. Creating new local entry\n", name);
    printf("%s\n", name);
    symbol *new = (symbol *)malloc(sizeof(symbol));
    new->name = strdup(name);
    new->type = 0;
    new->value = NULL;
    new->size = 0;
    new->offset = 0;
    new->nested_table = NULL;
    new->next = NULL;

    symb->next = new;
    // table->next = new;
    // print_symboltable(table);
    // printf("%p\n", table->next);
    // printf("\n");
    // return new;
    return new;
}     

void print_symboltable(symbol *table){//, char *name){

    symbol *sym = table;
    if (table == global_table){
        printf("\n\nName: ST.GLB\t\tParent: NULL\n");
    }

    // printf("Name: %s\n", sym->name);
    printf("===============================================================================================================================================\n");
    printf("Current\t\t\t\tName\t\tType\t\t\t\t\tValue\t\tSize\tOffset\t\tCategory\tNested Table\t\t\t\tNext\n");
    printf("===============================================================================================================================================\n");
    while(sym != NULL){
        printf("%p\t\t", sym);
        printf("%-10s\t", sym->name);
        switch(sym->type){
            case TYPE_INT:
                if (sym->arraySize > 0){
                    printf("array(int, %d)\t\t\t", sym->arraySize);
                }                
                else{
                    printf("int\t\t\t\t\t\t");
                }
                if (sym->value == NULL){
                    printf("NULL\t\t");
                }
                else{
                    printf("%-10d\t", atoi(sym->value));
                }
                break;

            case TYPE_CHAR:
                if (sym->arraySize > 0){
                    printf("array(char, %d)\t\t", sym->arraySize);
                }                
                else{
                    printf("char\t\t\t\t");
                }
                if (sym->value == NULL){
                    printf("\tNULL\t\t");
                }
                else{
                    printf("\t%-5s\t\t", (char*)sym->value);
                }
                break;

            case TYPE_PTR:
            if (sym->arraySize > 0){
                    printf("array(ptr, %d)\t\t", sym->arraySize);
                }                
                else{
                    printf("ptr\t\t\t\t\t");
                }
                printf("%-10p\t", sym->value);
                break;
            case TYPE_VOID:
                if (sym->arraySize > 0){
                    printf("array(void, %d)\t\t\t", sym->arraySize);
                }                
                else{
                    printf("void\t\t\t\t\t");
                }
                printf("NULL\t\t");
                break;

            case TYPE_VOID_PTR:
                if (sym->arraySize > 0){
                    printf("array(void*, %d)\t\t\t", sym->arraySize);
                }                
                else{
                    printf("void*\t\t\t\t\t");
                }
                if (sym->value == NULL){
                    printf("\t%-10p\t", sym->value);
                }
                else{
                    printf("%-10p\t", sym->value);
                }
                break;
                
            case TYPE_INT_PTR:
                if (sym->arraySize > 0){
                    printf("array(int*, %d)\t\t", sym->arraySize);
                }                
                else{
                    printf("int*\t\t\t\t");
                }
                if (sym->value == NULL){
                    printf("\t%-10p\t", sym->value);
                }
                else{
                    printf("%-10p\t", sym->value);
                }
                break;

            case TYPE_CHAR_PTR:
                if (sym->arraySize > 0){
                    if (sym->arraySize >= 10){
                        printf("array(char*, %d)\t", sym->arraySize);
                    }
                    else{
                        printf("array(char*, %d)\t\t", sym->arraySize);
                    }
                }                
                else{
                    printf("char*\t\t\t\t");
                }
                if (sym->value == NULL){
                    printf("\t%-10p\t", sym->value);
                }
                else{
                    printf("%-10p\t", sym->value);
                }
                // printf("%-10p\t", sym->value);
                break;
        }
        // printf("%s\t\t", (char*)sym->value);
        if (sym->arraySize > 0){
            printf("%-5d\t\t", sym->size * sym->arraySize);
        }
        else{
            printf("%-5d\t\t", sym->size);
        }
        // printf("%-5d\t\t", sym->size);
        printf("%d\t\t\t", sym->offset);
        switch(sym->category){
            case GLOBAL:
                printf("GLB\t\t");
                break;
            case LOCAL:
                printf("LCL\t\t");
                break;
            case PARAMETER:
                printf("PRM\t\t");
                break;
            case FUNCTION:
                printf("FUN\t\t");
                break;
            case TEMP:
                printf("TMP\t\t");
                break;
            // default:
            //     if (table == global_table){
            //         printf("GLB\t\t");
            //     }
            //     else{
            //         printf("LCL\t\t");
            //     }
        }
        printf("%-10p\t\t\t\t", sym->nested_table);
        if (sym->nested_table == NULL){
            printf("\t%-10p\n", sym->next);
        }
        else{
            printf("%-10p\n", sym->next);
        }
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
        sym = sym->next;
    }
    printf("\n\n");
}

void print_all_ST(){
    symbol *sym = global_table;
    print_symboltable(sym);
    while(sym != NULL){
        if (sym->nested_table != NULL){
            if (sym->nested_table->name != NULL){
                printf("Name: ST.%-5s\t\tParent: ST.GLB\n", sym->name);
                print_symboltable(sym->nested_table);
            }
        }
        sym = sym->next;
    }
}

symbol *gentemp(){//data_type type, void *value){
    static int count = 0;
    char *name = (char *)malloc(sizeof(char) * 10);
    sprintf(name, "t%d", count++);
    symbol *temp = symlook(current_table, name);
    temp->category = TEMP;
    printf("Created temporary %s\n", name);
    // temp->type = type.type;
    // temp->size = type.size;
    // temp->value = (void*)value;
    return temp;
}


symbol *global_table = NULL;
symbol *current_table = NULL;
symbol *table_pointer = NULL;
char *table_name = NULL;


// QuadArray *quadArray;

quad* newQuad(){
    quad *new = (quad *)malloc(sizeof(quad));
    new->op = 0;
    new->result = NULL;
    new->arg1 = NULL;
    new->arg2 = NULL;
    return new;
}   

quad *QuadArray[MAXQARRAY];

void emit(opcodeType op, char *result, char *arg1, char *arg2){

    quad *new = newQuad();
    if (new == NULL){
        printf("-->Error creating quad\n");
    }

        printf("-->Emitting quad %s\n", result);
        
        new->op = op;
        if(result != NULL){
            new->result = strdup(result);
        }
        if(arg1 != NULL){
            new->arg1 = strdup(arg1);
        }
        if(arg2 != NULL){
            new->arg2 = strdup(arg2);
        }
        
        QuadArray[next_instr] = new;
        next_instr++;
        printf("COUNTER INCREMENTED TO %d\n", next_instr);
        makeTAC();
        // printf("Quad emitted %s\n", result);
        // print_quad_array();
        // print_symboltable(current_table);
        // print_all_ST();
        return;
}

int giveNextInstr(){
    return next_instr;
}

void print_quad_array(){
    printf("====================================================================\n");
    printf("Instr No.\t\tOp\t\t\t\tResult\t\t\tArg1\t\tArg2\n");
    printf("====================================================================\n");
        
    for (int i = 1; i < next_instr; i++){
        // printf("%p\t\t", QuadArray[i]);
        printf("%-5d\t\t\t", i);
        printf("%-5d\t\t\t", QuadArray[i]->op);
        printf("%-10s\t\t", QuadArray[i]->result);
        printf("%-5s\t\t", QuadArray[i]->arg1);
        printf("%-5s \n", QuadArray[i]->arg2);
        // printf("%p\n", QuadArray[i]->next);
        printf("--------------------------------------------------------------------\n");
    }
    printf("Printed\n\n");
}

void makeTAC(){
    printf("\n====================================================================\n");
    for (int i = 1; i < next_instr; i++){
        printf("%-3d:\t", i);
        switch(QuadArray[i]->op){
            case ASSIGN:
                printf("%s = %s\n", QuadArray[i]->result, QuadArray[i]->arg1);
                break;
            case PLUS:
                printf("%s = %s + %s\n", QuadArray[i]->result, QuadArray[i]->arg1, QuadArray[i]->arg2);
                break;
            case MINUS:
                printf("%s = %s - %s\n", QuadArray[i]->result, QuadArray[i]->arg1, QuadArray[i]->arg2);
                break;
            case MULT:
                printf("%s = %s * %s\n", QuadArray[i]->result, QuadArray[i]->arg1, QuadArray[i]->arg2);
                break;
            case DIV:
                printf("%s = %s / %s\n", QuadArray[i]->result, QuadArray[i]->arg1, QuadArray[i]->arg2);
                break;
            case MOD:
                printf("%s = %s %% %s\n", QuadArray[i]->result, QuadArray[i]->arg1, QuadArray[i]->arg2);
                break;
            case EQUAL:
                printf("if %s == %s goto %s\n", QuadArray[i]->arg1, QuadArray[i]->arg2, QuadArray[i]->result);
                break;
            case NE:
                printf("if %s != %s goto %s\n", QuadArray[i]->arg1, QuadArray[i]->arg2, QuadArray[i]->result);
                break;
            case GT:
                printf("if %s > %s goto %s\n", QuadArray[i]->arg1, QuadArray[i]->arg2, QuadArray[i]->result);
                break;
            case LT:
                printf("if %s < %s goto %s\n", QuadArray[i]->arg1, QuadArray[i]->arg2, QuadArray[i]->result);
                break;
            case GTE:
                printf("if %s >= %s goto %s\n", QuadArray[i]->arg1, QuadArray[i]->arg2, QuadArray[i]->result);
                break;
            case LTE:
                printf("if %s <= %s goto %s\n", QuadArray[i]->arg1, QuadArray[i]->arg2, QuadArray[i]->result);
                break;

            case ADDR:
                printf("%s = &%s\n", QuadArray[i]->result, QuadArray[i]->arg1);
                break;
            case PTR_ASSIGN:
                printf("%s = *%s\n", QuadArray[i]->result, QuadArray[i]->arg1);
                break;
            case READIDX:
                printf("%s = %s[%s]\n", QuadArray[i]->result, QuadArray[i]->arg1, QuadArray[i]->arg2);
                break;
            case WRITEIDX:
                printf("%s[%s] = %s\n", QuadArray[i]->result, QuadArray[i]->arg1, QuadArray[i]->arg2);
                break;
            case UPLUS:
                printf("%s = + %s\n", QuadArray[i]->result, QuadArray[i]->arg1);
                break;
            case UMINUS:
                printf("%s = - %s\n", QuadArray[i]->result, QuadArray[i]->arg1);
                break;
            case NOT:
                printf("%s = ! %s\n", QuadArray[i]->result, QuadArray[i]->arg1);
                break;
            case GOTO:
                printf("goto %s\n", QuadArray[i]->result);
                break;
            case FUNC:
                printf("FUNCTION %s\n", QuadArray[i]->result);
                break;
            case FUNC_END:
                printf("END FUNCTION %s\n", QuadArray[i]->result);
                // print_all_ST();
                break;
            case CALL:
                if (QuadArray[i]->result != NULL){
                    printf("%s = CALL %s, %s\n", QuadArray[i]->result, QuadArray[i]->arg1, QuadArray[i]->arg2);
                }
                else{
                    printf("CALL %s, %s\n", QuadArray[i]->arg1, QuadArray[i]->arg2);
                }
                break;
            case PARAM:
                printf("PARAM %s\n", QuadArray[i]->result);
                break;
            case RET:
                printf("RETURN %s\n", QuadArray[i]->result);
                break;
            default:
                printf("\n");
        }
        printf("--------------------------------------------------------------------\n");
        // print_all_ST();
    }
    printf("====================================================================\n\n");
}

List* newList(int next_instr){
    List *new = (List *)malloc(sizeof(List));
    new->instr = next_instr;
    new->next = (List *)malloc(sizeof(List));
    new->next->instr = -1;
    new->next->next = NULL;
    return new;
}
Expression* exprCreate(){
    Expression *new = (Expression *)malloc(sizeof(Expression));
    new->loc = NULL;
    new->isArray = false;
    new->isPointer = false;
    new->isBoolean = false;
    new->truelist = NULL;
    new->falselist = NULL;
    new->nextlist = NULL;
    return new;
}

Statement* statCreate(){
    Statement *new = (Statement *)malloc(sizeof(Statement));
    new->nextlist = NULL;
    return new;
}


data_type intType = {TYPE_INT, size_of_int};
data_type charType = {TYPE_CHAR, size_of_char};
data_type voidType = {TYPE_VOID, 0};
data_type ptrType = {TYPE_PTR, size_of_pointer};

void push(DataTypeStack *s, data_type dType){
    if (s->top == DSTACK - 1){
        yyerror("-->Data Type Stack Overflow");
    }
    else{
        s->items[++s->top] = dType;
        // printf("-->Pushed (%d)type to data type stack\n", dType.type);
        return;
    }
}

data_type pop(DataTypeStack *s){
    if (s->top == -1){
        yyerror("-->Data Type Stack Underflow");
    }
    else{
        // printf("-->Popped %d from data type stack\n", s->items[s->top].type);
        return s->items[s->top--];
    }
}

DataTypeStack dTypeStack;

void copyArray(int* dest, int* src, int size){
    for (int i = 0; i < size; i++){
        dest[i] = src[i];
    }
}

void backpatch(List *stmList, int inst) {
    List *temp = stmList;
    if (temp == NULL){
        // printf("BACKPATCH DENIED - List empty\n");
        return;
    }
    if (inst > 0) {
        while (temp != NULL) {
            // Check if the instruction is within the valid range of QuadArray
            // printf("Backpatching %d ------> %d\n", inst, temp->instr);
            if (temp->instr > 0 && temp->instr <= MAXQARRAY) {
                char str[10];
                sprintf(str, "%d", inst);
                // printf("Backpatching %d ------> %d\n", inst, temp->instr);
                QuadArray[temp->instr]->result = strdup(str);
                // makeTAC();
            } else {
                // Handle out-of-bounds error
                // printf("BACKPATCH DENIED: Invalid instruction index %d\n", temp->instr);
            }
            temp = temp->next;
        }
    }
}


List *addToList(List *stmList, int inst)
{
    List *temp = stmList;
    List *new = (List *)malloc(sizeof(List));
    new->instr = inst;
    new->next = NULL;
    if (temp == NULL)
    {
        stmList = new;
        return stmList;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
        return stmList;
    }
}

void printList(List *stmList){
    List *temp = stmList;
    while (temp != NULL){
        printf("%d, ", temp->instr);
        temp = temp->next;
    }
    printf("\n");
}

Expression *boolToInt(Expression *e){
    printf("Checking if %s is boolean\n", e->loc->name);
    if (e->isBoolean == true){
        printf("It is boolean\n");
        e->loc = gentemp();
        e->loc->type = TYPE_INT;
        e->loc->size = size_of_int;
        e->loc->category = TEMP;

        backpatch(e->truelist, giveNextInstr());
        emit(ASSIGN, e->loc->name, "true", NULL);
        char str[10];
        sprintf(str, "%d", giveNextInstr()+1);

        emit(GOTO, str, NULL, NULL);
        backpatch(e->falselist, giveNextInstr());
        emit(ASSIGN, e->loc->name, "false", NULL);
    }
    else{
        printf("Already integer\n");
    }
    return e;
}

Expression *intToBool(Expression *e){
    printf("Checking if %s is boolean\n", e->loc->name);
    if (e->isBoolean == false){
        printf("It is integer\n");
        e->falselist = newList(giveNextInstr());
        emit(EQUAL, "", e->loc->name, "0");

        e->truelist = newList(giveNextInstr());
        emit(GOTO, "", NULL, NULL);
    }
    else{
        printf("Already boolean\n");
    }
    return e;
}

List *merge(List *list1, List *list2) {
    List *temp = list1;
    if (temp == NULL) {
        return list2;
    } 
    if (list2 == NULL) {
        return list1;
    }
    else {
        while (temp->next != NULL || temp->instr != -1) {
            temp = temp->next;
        }
        temp->next = list2;
        return list1;
    }
}

int main(){

    // static int nextInstr = 0;
    // quadArray = create_quad_array();
    global_table = create_symboltable();
    current_table = global_table;
    printf("===Created global symbol table===\n");
    // print_symboltable(current_table);
    dTypeStack.top = -1;
    printf("===Created data type stack===\n");
    next_instr = 1;
    printf("COUNTER at %d\n", giveNextInstr());

    yyparse();
    // print_symboltable(global_table);
    // print_symboltable(current_table);
    print_all_ST();
    print_quad_array();
    makeTAC();
    printf("Next Instruction Number: %d\n", next_instr);
    // printf("%d\n", nextInstr);

    return 0;
}