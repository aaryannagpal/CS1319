#include "26_A5_translator.h"
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
    symbol *temp = table;    
    // printf("Updating symbol table: %s\n", name);
    while(temp != NULL){
        if(strcmp(temp->name, name) == 0){
            temp->type = type;
            switch(type){
                case TYPE_INT:
                    temp->value = value;
                    break;
                case TYPE_CHAR:
                    temp->value = value;
                    break;
                case TYPE_PTR:
                    temp->value = &value;
                    break;
                case TYPE_VOID:
                    temp->value = value;
                case TYPE_VOID_PTR:
                    temp->value = &value;
                    break;
                case TYPE_INT_PTR:
                    temp->value = &value;
                    break;
                case TYPE_CHAR_PTR:
                    temp->value = &value;
                    break;
            }
            temp->size = size;
            temp->category = category;
            temp->arraySize = arraySize;
            temp->arrayName = arrayName;
            return temp;
        }
        temp = temp->next;
    }
    free(temp);
    return NULL;
}

symbol *searchTable(symbol *table, char *name){
    symbol *temp = table;
    
    if (temp == NULL){
        return NULL;
    }

    else{
        if (temp->name == NULL){
            return NULL;
        }
    }

    while(temp->next != NULL){
        if(strcmp(temp->name, name) == 0){
            return temp;
        }
        temp = temp->next;
    }
    
    if (strcmp(temp->name, name) == 0){
        return temp;
    }
    free(temp);
    return NULL;
}

symbol *symlook(symbol *table, char *name){
    symbol *symb = table;
    symbol *temp = global_table;

    if (symb->name == NULL){ // First entry 
        symb->name = strdup(name);
        table = symb;
        return table;
    }
    while(symb->next != NULL){
        if(strcmp(symb->name, name) == 0){
            return symb;
        }
        symb = symb->next;
    }

    if (strcmp(symb->name, name) == 0){
        return symb;
    }
    /* searching global if not found in current table*/
    if (temp->name == NULL){ // First entry 
        temp->name = strdup(name);
        table = temp;
        return table;
    }
    while(temp->next != NULL){
        if(strcmp(temp->name, name) == 0){
            return temp;
        }
        temp = temp->next;
    }
    if (strcmp(temp->name, name) == 0){
        return temp;
    }
    
    symbol *new = (symbol *)malloc(sizeof(symbol));
    new->name = strdup(name);
    new->type = 0;
    new->value = NULL;
    new->size = 0;
    new->offset = 0;
    new->nested_table = NULL;
    new->next = NULL;

    symb->next = new;
    return new;
}     

void print_symboltable(symbol *table){
    symbol *sym = table;
    if (table == global_table){
        printf("\n\nName: ST.GLB\t\tParent: NULL\n");
    }
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
                break;
        }
        if (sym->arraySize > 0){
            printf("%-5d\t\t", sym->size * sym->arraySize);
        }
        else{
            printf("%-5d\t\t", sym->size);
        }
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
            case RETVAL:
                printf("RET\t\t");
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
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
        sym = sym->next;
    }
    printf("\n\n");
    // free(sym);
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
    // free(sym);
}

symbol *gentemp(){//data_type type, void *value){
    static int count = 0;
    char *name = (char *)malloc(sizeof(char) * 10);
    sprintf(name, "t%d", count++);
    symbol *temp = symlook(current_table, name);
    temp->category = TEMP;
    return temp;
}


symbol *global_table = NULL;
symbol *current_table = NULL;
symbol *table_pointer = NULL;
char *table_name = NULL;
int labelCount = 0;
labelHash *labelTable[MAX_LABELS];
globVars *globalVars[MAX_GLOBAL_VARS];



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
        printf("%-5d\t\t\t", i);
        printf("%-5d\t\t\t", QuadArray[i]->op);
        printf("%-10s\t\t", QuadArray[i]->result);
        printf("%-5s\t\t", QuadArray[i]->arg1);
        printf("%-5s \n", QuadArray[i]->arg2);
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
            case STR:
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
        return;
    }
}

data_type pop(DataTypeStack *s){
    if (s->top == -1){
        yyerror("-->Data Type Stack Underflow");
        return voidType;
    }
    else{
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
        return;
    }
    if (inst > 0) {
        while (temp != NULL) {
            if (temp->instr > 0 && temp->instr <= MAXQARRAY) {
                char str[10];
                sprintf(str, "%d", inst);
                QuadArray[temp->instr]->result = strdup(str);
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
    if (e->isBoolean == true){
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
        // printf("Already integer\n");
    }
    return e;
}

Expression *intToBool(Expression *e){
    if (e->isBoolean == false){
        e->falselist = newList(giveNextInstr());
        emit(EQUAL, "", e->loc->name, "0");

        e->truelist = newList(giveNextInstr());
        emit(GOTO, "", NULL, NULL);
    }
    else{
        // printf("Already boolean\n");
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


param_list* para_init(){
    param_list *new = (param_list *)malloc(sizeof(param_list));
    new->para = NULL;
    new->next = NULL;
    return new;
}

void para_push(param_list *head, char *para){
    if (head->para == NULL){
        head->para = strdup(para);
        return;
    }
    param_list *temp = (param_list *)malloc(sizeof(param_list));
    temp->para = strdup(para);
    temp->next = NULL;

    param_list *current = head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = temp;
}

param_list* para_pop(param_list *head){
    param_list *temp = head;
    if (temp->next == NULL){
        param_list *new = temp;
        temp = temp->next;
        free(temp);
    }
    head = para_init();
    return head;
}

unsigned int ARhash(char *str){
    unsigned int hash = 0;
    for (int i = 0; i < strlen(str); i++){
        hash = hash + str[i];
    }
    return hash % MAX_AR_SIZE;
}

void insertAR(ARHash *table[], char *key, int value){
    if (key == NULL){
        return;
    }
    int hash = ARhash(key);
    ARHash *temp = table[hash];
    while (temp != NULL){
        if (strcmp(temp->key, key) == 0){
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    ARHash *new = (ARHash *)malloc(sizeof(ARHash));
    new->key = strdup(key);
    new->value = value;
    new->next = table[hash];
    table[hash] = new;
}

int searchAR(ARHash *table[], char *key){
    if (key == NULL){
        return -1;
    }
    int hash = ARhash(key);
    ARHash *temp = table[hash];
    while (temp != NULL){
        if (strcmp(temp->key, key) == 0){
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

unsigned int labHash(int key){
    return key % MAX_LABELS;
}

void insertLabel(labelHash *table[], int key, int value){
    if (key == -1){
        return;
    }

    int hash = labHash(key);
    labelHash *temp = table[hash];
    while (temp != NULL){
        if (temp->key == key){
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    labelHash *new = (labelHash *)malloc(sizeof(labelHash));
    new->key = key;
    new->value = value;
    new->next = table[hash];
    table[hash] = new;
}

bool searchLabel(labelHash *table[], int key){
    if (key == -1){
        return false;
    }

    int hash = labHash(key);
    labelHash *temp = table[hash];
    while (temp != NULL){
        if (temp->key == key){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

labelHash* getLabel(labelHash *table[], int key){
    if (key == -1){
        return NULL;
    }

    int hash = labHash(key);
    labelHash *temp = table[hash];
    while (temp != NULL){
        if (temp->key == key){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

unsigned int globHash(char *str){
    unsigned int hash = 0;
    for (int i = 0; i < strlen(str); i++){
        hash = hash + str[i];
    }
    return hash % MAX_GLOBAL_VARS;
}

void insertGlob(globVars *table[], char *key, bool value){
    if (key == NULL){
        return;
    }
    int hash = globHash(key);
    globVars *temp = table[hash];
    while (temp != NULL){
        if (strcmp(temp->name, key) == 0){
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    globVars *new = (globVars *)malloc(sizeof(globVars));
    new->name = strdup(key);
    new->value = value;
    new->next = table[hash];
    table[hash] = new;
}

bool searchGlob(globVars *table[], char *key){
    if (key == NULL){
        return false;
    }
    int hash = globHash(key);
    globVars *temp = table[hash];
    while (temp != NULL){
        if (strcmp(temp->name, key) == 0){
            return temp->value;
        }
        temp = temp->next;
    }
    return false;
}

void AR(symbol *table){
    int localOffset = -4;
    int paramOffset = 8;

    symbol *temp = table;
    while (temp->next != NULL){
        if (temp->category == RETVAL){
            temp = temp->next;
            continue;
        }
        else if (temp->category == PARAMETER){
            insertAR(temp->ST_AR, temp->name, paramOffset);
            printf("Inserting %s at %d for %s\n", temp->ST_AR[ARhash(temp->name)]->key, temp->ST_AR[ARhash(temp->name)]->value, temp->name);
            paramOffset += temp->size;
        }
        else if (temp->category == FUNCTION){
            AR(temp->nested_table);
        }
        else{
            insertAR(temp->ST_AR, temp->name, localOffset);
            printf("Inserting %s at %d for %s\n", temp->ST_AR[ARhash(temp->name)]->key, temp->ST_AR[ARhash(temp->name)]->value, temp->name);
            localOffset -= temp->size;
        }
        temp = temp->next;
    }

    if (temp->category == RETVAL){
        return;
    }
    else if (temp->category == PARAMETER){
        insertAR(temp->ST_AR, temp->name, paramOffset);
        printf("Inserting %s at %d for %s\n", temp->ST_AR[ARhash(temp->name)]->key, temp->ST_AR[ARhash(temp->name)]->value, temp->name);

        paramOffset += temp->size;
    }
    else if (temp->category == FUNCTION){
        AR(temp->nested_table);
    }
    else{
        insertAR(temp->ST_AR, temp->name, localOffset);
        printf("Inserting %s at %d for %s\n", temp->ST_AR[ARhash(temp->name)]->key, temp->ST_AR[ARhash(temp->name)]->value, temp->name);

        localOffset -= temp->size;
    }
    return;
}

void printAR(symbol *table){
    printf("\n\n");
    printf("====================================================================");
    printf("\n\n");
    symbol *sym = table;

    while (sym != NULL){  
        if (sym->category == FUNCTION){
            printAR(sym->nested_table);
        }  
        for (int i = 0; i < MAX_AR_SIZE; i++){
            ARHash *temp = sym->ST_AR[i];
            if (temp != NULL){
                printf("%s\t\t%d\n", temp->key, temp->value);
            }
        }
        sym = sym->next;
    }
    return;
}

int main(){

    global_table = create_symboltable();
    current_table = global_table;
    dTypeStack.top = -1;
    next_instr = 1;

    yyparse();
    print_all_ST();
    printf("Next Instruction Number: %d\n\n", next_instr);
    print_quad_array();
    makeTAC();
    AR(global_table);
    printAR(global_table);

    return 0;
}