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
    table->nested_table = NULL;
    table->next = NULL;

    return table;
}

symbol *update_symboltable(symbol *table, char *name, enumtype type, void *value, int size){
    // symbol *symb = table;
    symbol *temp = table;
    printf("\n\n");
    printf("Updating symbol table entry for %s?\n", name);
    printf("\n\n");
    while(temp != NULL){
        if(strcmp(temp->name, name) == 0){
            temp->type = type;
            temp->value = value;
            temp->size = size;
            
            // table = temp;
            print_symboltable(table);
            return temp;
        }
        temp = temp->next;
    }
}

symbol *symlook(symbol *table, char *name){
    symbol *symb = table;

    if (symb->name == NULL){ // First entry 
        symb->name = strdup(name);
        // symb->name = name;
        table = symb;
        printf("\n\n");
        printf("Created first symbol table entry for %s\n", name);
        print_symboltable(table);
        printf("\n\n");
        return table;
    }
    printf("Table not empty! Moving on:\n");
    while(symb->next != NULL){
        if(strcmp(symb->name, name) == 0){
            printf("Found symbol table entry for %s\n", name);
            print_symboltable(symb);
            return symb;
        }
        symb = symb->next;
    }
    printf("Symbol table entry for %s not found. Creating new entry\n", name);
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
    print_symboltable(table);
    printf("%p\n", table->next);
    // printf("\n");
    // return new;
    return new;
}     

void print_symboltable(symbol *table){
    symbol *sym = table;
    printf("=================================================================================\n");
    printf("Current\t\t\tName\tType\tValue\tSize\tOffset\tNested Table\tNext\n");
    printf("=================================================================================\n");
    while(sym != NULL){
        printf("%p\t\t", sym);
        printf("%s\t", sym->name);
        switch(sym->type){
            case TYPE_INT:
                printf("int\t\t");
                break;
            case TYPE_CHAR:
                printf("char\t");
                break;
            case TYPE_PTR:
                printf("ptr\t");
                break;
            case TYPE_VOID:
                printf("void\t");
                break;
        }
        printf("%p\t\t", sym->value);
        printf("%d\t\t", sym->size);
        printf("%d\t\t", sym->offset);
        printf("%p\t\t", sym->nested_table);
        printf("%p\n", sym->next);
        printf("---------------------------------------------------------------------------------\n");
        sym = sym->next;
    }
}

symbol *gentemp(data_type type, void *value){
    static int count = 0;
    char *name = (char *)malloc(sizeof(char) * 10);
    sprintf(name, "t%d", count++);
    symbol *temp = symlook(current_table, name);
    printf("Created temporary %s\n", name);
    temp->type = type.type;
    temp->size = type.size;
    temp->value = (void*)value;
    return temp;
}

symbol *global_table = NULL;
symbol *current_table = NULL;


















data_type intType = {TYPE_INT, size_of_int};
data_type charType = {TYPE_CHAR, size_of_char};
data_type voidType = {TYPE_VOID, 0};
data_type ptrType = {TYPE_PTR, size_of_pointer};

void push(DataTypeStack *s, data_type dType){
    if (s->top == DSTACK - 1){
        yyerror("Data Type Stack Overflow");
    }
    else{
        s->items[++s->top] = dType;
        printf("Pushed (%d)type to data type stack\n", dType.type);
        return;
    }
}

data_type pop(DataTypeStack *s){
    if (s->top == -1){
        yyerror("Data Type Stack Underflow");
    }
    else{
        printf("Popped %d from data type stack\n", s->items[s->top].type);
        return s->items[s->top--];
    }
}

DataTypeStack dTypeStack;




int main(){
    global_table = create_symboltable();
    current_table = global_table;
    printf("Created global symbol table\n");
    print_symboltable(current_table);
    dTypeStack.top = -1;

    yyparse();
    print_symboltable(global_table);


    return 0;
}