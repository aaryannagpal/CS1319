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
    symbol *temp = table;
    while(temp != NULL){
        if(strcmp(temp->name, name) == 0){
            temp->type = type;
            temp->value = value;
            temp->size = size;
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

symbol *symlook(symbol* table, char *name){
    symbol *symb = table;

    if (symb->name == NULL){
        symb->name = name;
        return symb;
    }

    while(symb->next != NULL){
        if(strcmp(symb->name, name) == 0){
            return symb;
        }
        symb = symb->next;
    }
    symbol *new = (symbol *)malloc(sizeof(symbol));
    new->name = name;
    new->type = 0;
    new->value = NULL;
    new->size = 0;
    new->offset = 0;
    new->nested_table = NULL;
    new->next = NULL;
    if (symb->name == NULL){
        symb = new;
        return symb;
    }
    table->next = new;
    return new;
}     

void print_symboltable(symbol *table){
    symbol *sym = table;
    printf("Name\tType\tSize\tOffset\n");
    while(sym != NULL){
        printf("%s\t\t", sym->name);
        switch(sym->type){
            case TYPE_INT:
                printf("int\t");
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
        printf("%d\t\t%d\n", sym->size, sym->offset);
        sym = sym->next;
    }
}

symbol *global_table = NULL;
symbol *current_table = NULL;

int main(){
    global_table = create_symboltable();
    current_table = global_table;
    yyparse();
    print_symboltable(global_table);
    return 0;
}