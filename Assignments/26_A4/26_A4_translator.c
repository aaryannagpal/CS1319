#include "26_A4_translator.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern void yyerror(char *s);
extern int yyparse();


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

symbol *update_symboltable(symbol *table, char *name, enumtype type, char *value, int size, enumcat category){
    // symbol *symb = table;
    symbol *temp = table;
    printf("\n\n");
    printf("-->Updating symbol table entry for %s\n", name);
    printf("\n\n");
    while(temp != NULL){
        printf("==>Comparing %s\n", temp->name);
        if(strcmp(temp->name, name) == 0){
            printf("-->Found symbol table entry for %s\n", temp->name);
            temp->type = type;
            printf("-->Value already present\n");
            switch(type){
                case TYPE_INT:
                    printf("-->Int type\n");
                    temp->value = value;
                    // *(int*)temp->value = atoi(value);
                    break;
                case TYPE_CHAR:
                    temp->value = value;
                    break;
                case TYPE_PTR:
                    printf("-->Pointer type\n");
                    temp->value = &value;
                    break;
                // case TYPE_VOID:
                //     temp->value = NULL;
                //     break;
                // case TYPE_VOID_PTR:
                //     temp->value = (void*)malloc(sizeof(void*));
                //     *(void**)temp->value = NULL;
                //     break;
                // case TYPE_INT_PTR:
                //     temp->value = (void*)malloc(sizeof(int*));
                //     *(int**)temp->value = NULL;
                //     break;
                // case TYPE_CHAR_PTR:
                //     temp->value = (void*)malloc(sizeof(char*));
                //     *(char**)temp->value = NULL;
                //     break;
            }

            printf("-->%d\n", temp->type);

            // temp->value = value;
            temp->size = size;
            temp->category = category;
            
            // table = temp;
            // print_symboltable(table);
            return temp;
        }
        temp = temp->next;
    }
    printf("-->Symbol table entry for %s not found.\n", name);
}

symbol *searchTable(symbol *table, char *name){
    symbol *temp = table;
    
    if (temp == NULL){
        printf("-->Table empty therefore %s not found.\n", name);
        return NULL;
    }

    else{
        if (temp->name == NULL){
            printf("-->Void Table empty therefore %s not found.\n", name);
            return NULL;
        }
    }

    while(temp->next != NULL){
        if(strcmp(temp->name, name) == 0){
            printf("-->Found symbol table entry for %s\n", temp->name);
            return temp;
        }
        temp = temp->next;
    }
    
    if (strcmp(temp->name, name) == 0){
        printf("-->Found symbol table entry for %s\n", temp->name);
        return temp;
    }

    printf("-->Symbol table entry for %s not found.\n", name);
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
        printf("\n\n");
        printf("-->Created first symbol table entry for %s\n", name);
        // print_symboltable(table);
        printf("\n\n");
        return table;
    }
    printf("-->Table not empty! Moving on:\n");
    while(symb->next != NULL){
        if(strcmp(symb->name, name) == 0){
            printf("-->Found symbol table entry for %s\n", name);
            // print_symboltable(symb);
            return symb;
        }
        symb = symb->next;
    }

    if (strcmp(symb->name, name) == 0){
        printf("-->Found symbol table entry for %s\n", name);
        // print_symboltable(symb);
        return symb;
    }

    // searching global if not found in current table
    

    if (temp->name == NULL){ // First entry 
        temp->name = strdup(name);
        // symb->name = name;
        table = temp;
        printf("\n\n");
        printf("-->Created first global symbol table entry for %s\n", name);
        // print_symboltable(table);
        printf("\n\n");
        return table;
    }
    printf("-->Global table not empty! Moving on:\n");
    while(temp->next != NULL){
        printf("==>Comparing %s\n", temp->name);
        if(strcmp(temp->name, name) == 0){
            printf("-->Found global symbol table entry for %s\n", name);
            // print_symboltable(symb);
            return temp;
        }
        temp = temp->next;
    }
    if (strcmp(temp->name, name) == 0){
        printf("-->Found global symbol table entry for %s\n", name);
        // print_symboltable(symb);
        return temp;
    }




    printf("-->Symbol table entry for %s not found. Creating new local entry\n", name);
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
    printf("=======================================================================================================================================\n");
    printf("Current\t\t\t\tName\t\tType\t\tValue\t\tSize\tOffset\t\tCategory\tNested Table\t\t\t\tNext\n");
    printf("=======================================================================================================================================\n");
    while(sym != NULL){
        printf("%p\t\t", sym);
        printf("%-10s\t", sym->name);
        switch(sym->type){
            case TYPE_INT:
                printf("int\t\t\t");
                if (sym->value == NULL){
                    printf("NULL\t\t");
                }
                else{
                    printf("%-10d\t", atoi(sym->value));
                }

                break;
            case TYPE_CHAR:
                // printf("HEKKO\t");
                printf("char\t");
                if (sym->value == NULL){
                    printf("\tNULL\t\t");
                }
                else{
                    printf("\t%-5s\t\t", (char*)sym->value);
                }
                break;
            case TYPE_PTR:
                printf("ptr\t\t");
                printf("%-10p\t", sym->value);
                break;
            case TYPE_VOID:
                printf("void\t\t");
                printf("NULL\t\t");
                break;
            case TYPE_VOID_PTR:
                printf("void*\t");
                if (sym->value == NULL){
                    printf("\t%-10p\t", sym->value);
                }
                else{
                    printf("%-10p\t", sym->value);
                }
                break;
            case TYPE_INT_PTR:
                printf("int*\t");
                if (sym->value == NULL){
                    printf("\t%-10p\t", sym->value);
                }
                else{
                    printf("%-10p\t", sym->value);
                }
                break;
            case TYPE_CHAR_PTR:
                printf("char*\t");
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
        printf("%-5d\t\t", sym->size);
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
            default:
                if (table == global_table){
                    printf("GLB\t\t");
                }
                else{
                    printf("LCL\t\t");
                }
        }
        printf("%-10p\t\t\t\t", sym->nested_table);
        if (sym->nested_table == NULL){
            printf("\t%-10p\n", sym->next);
        }
        else{
            printf("%-10p\n", sym->next);
        }
        printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
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
    // printf("Created temporary %s\n", name);
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

quad *QuadArray[MAXQARRAY];

static int next_instr;

void emit(opcodeType op, char *result, char *arg1, char *arg2){

    quad *new = (quad *)malloc(sizeof(quad));
    if (new == NULL){
        printf("-->Error creating quad\n");
    }

        printf("-->Emitting quad %s\n", result);
        
        new->op = op;
        new->result = strdup(result);
        new->arg1 = arg1;
        new->arg2 = arg2;
        
        QuadArray[next_instr] = new;
        next_instr++;
        // printf("Quad emitted %s\n", result);
        // print_quad_array();
        // print_symboltable(current_table);
        return;
}


void print_quad_array(){
    printf("====================================================================\n");
    printf("Instr No.\t\tOp\t\t\t\tResult\t\t\tArg1\t\tArg2\n");
    printf("====================================================================\n");
        
    for (int i = 0; i < next_instr; i++){
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
        printf("-->Pushed (%d)type to data type stack\n", dType.type);
        return;
    }
}

data_type pop(DataTypeStack *s){
    if (s->top == -1){
        yyerror("-->Data Type Stack Underflow");
    }
    else{
        printf("-->Popped %d from data type stack\n", s->items[s->top].type);
        return s->items[s->top--];
    }
}

DataTypeStack dTypeStack;

void printArray(int *arr, int size){
    for (int i = 0; i < size; i++){
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void copyArray(int* dest, int* src, int size){
    for (int i = 0; i < size; i++){
        dest[i] = src[i];
    }
}

void backpatch(List *stmList, int inst)
{
    List *temp = stmList;
    while (temp != NULL)
    {   
        printf("-->Backpatching from %d\n", temp->instr);
        if (temp->instr < 0){
            printf("-->Backpatching %d\n", inst);
            char inst_str[10];
            sprintf(inst_str, "%d", inst);
            QuadArray[temp->instr]->result = strdup(inst_str);
        }
        temp = temp->next;
    }
	// return;
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


int main(){

    // static int nextInstr = 0;
    // quadArray = create_quad_array();
    global_table = create_symboltable();
    current_table = global_table;
    printf("===Created global symbol table===\n");
    // print_symboltable(current_table);
    dTypeStack.top = -1;
    printf("===Created data type stack===\n");
    // next_instr = 0;
    printf("===Instruction Number Set to 0===\n");

    yyparse();
    // print_symboltable(global_table);
    // print_symboltable(current_table);
    print_all_ST();
    print_quad_array(QuadArray);
    printf("%d\n", next_instr);
    // printf("%d\n", nextInstr);

    return 0;
}