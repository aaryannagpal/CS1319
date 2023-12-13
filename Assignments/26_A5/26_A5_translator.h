#ifndef __PARSER_H
#define __PARSER_H

#define size_of_int 4
#define size_of_char 1
#define size_of_pointer 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define DSTACK 100
#define MAXQARRAY 10000
#define MAXLIST 100
#define MAXTEMP 100
#define MAX_AR_SIZE 600
#define MAX_LABELS 600
#define MAX_GLOBAL_VARS 600
#define MAX_STRING_TABLE 600

extern  char* yytext;
extern  int yyparse();

/* Symbol Table */
typedef enum{
	TYPE_VOID_PTR = -3,
	TYPE_INT_PTR,
	TYPE_CHAR_PTR,
	TYPE_VOID,
	TYPE_INT,
	TYPE_CHAR,
	TYPE_PTR,
}enumtype;

typedef enum{
	NONE,
	GLOBAL,
	LOCAL,
	PARAMETER,
	FUNCTION,
	TEMP, 
	RETVAL
}enumcat;

typedef struct hash{
	char* key;
	int value;
	struct hash *next;
}ARHash;

typedef struct hashNode {
    int key;
    int value;
	struct hashNode *next;
}labelHash;


typedef struct hashTable {
	char *name;
	bool value;
	struct hashTable *next;
}globVars;

typedef struct pm{
	char *para;
	struct pm *next;
}param_list;


typedef struct sym {
	char *name;
	enumtype type;
	void *value;
	int size;
	int offset;
	enumcat category;	
	struct sym *nested_table;
	struct sym *next;
	int arraySize; 
	char *arrayName;
	ARHash *ST_AR[MAX_AR_SIZE];
}symbol;
symbol* create_symbol();

extern symbol *global_table;
extern symbol *current_table;
extern symbol *table_pointer;
extern char *table_name;

symbol *symlook(symbol *table, char *name);
void print_symboltable(symbol *table);
symbol *searchTable(symbol *table, char *name);
symbol *create_symboltable();
symbol *update_symboltable(symbol *table, char *name, enumtype type, char *value, int size, enumcat category, int arraySize, char *arrayName);
symbol *gentemp();

typedef struct data_type{
	enumtype type;
	int size;
}data_type;

typedef struct {
    data_type items[DSTACK];
    int top;
} DataTypeStack;

void push(DataTypeStack *s, data_type item);
data_type pop(DataTypeStack *s);

extern DataTypeStack dTypeStack;
extern data_type intType ;
extern data_type charType;
extern data_type voidType;
extern data_type ptrType;

typedef struct LL{
	int instr;
	struct LL *next;
}List;
List* newList(int next_instr);
	

typedef struct exp{
	symbol *loc;
	bool isArray;
	bool isPointer;
	bool isBoolean;

	List *truelist;
	List *falselist;
	List *nextlist; // for statement references

}Expression;
Expression* exprCreate();

typedef struct stat{
	List *nextlist;
}Statement;

Statement* statCreate();


typedef enum {
	ASSIGN = 1,
	STR,
	PLUS,
	MINUS,
	MULT,
	DIV,
	MOD,

	EQUAL, //==
	NE, //!=
	GT, //>
	LT, //<
	GTE, //>=
	LTE, //<=
	
	ADDR,
	PTR_ASSIGN,
	READIDX, // res=arg1[arg2]
	WRITEIDX, // res[arg1]=arg2
	UPLUS,
	UMINUS,
	NOT,

	GOTO,

	FUNC,
	FUNC_END,
	CALL,
	PARAM,
	RET,
} opcodeType;

typedef struct quad_tag {
	opcodeType op;
	char *result, *arg1, *arg2;
} quad;

quad* newQuad();

extern quad *QuadArray[MAXQARRAY];
int giveNextInstr();

void emit(opcodeType op, char *result, char *arg1, char *arg2);
void print_quad_array();

static int next_instr= 0;

void copyArray(int *dest, int *src, int size);
void backpatch(List *list, int instr);
void printList(List *stmlist);

Expression *boolToInt(Expression *e);
Expression *intToBool(Expression *e);
List *merge(List *list1, List *list2);

unsigned int ARhash(char *str);
void insertAR(ARHash *table[], char *key, int value);
int searchAR(symbol* sym, char *key);

unsigned int labHash(int key);
void insertLabel(labelHash *table[], int key, int value);
bool searchLabel(labelHash *table[], int key);
labelHash* getLabel(labelHash *table[], int key);

unsigned int globHash(char *str);
void insertGlob(globVars *table[], char *name, bool value);
bool searchGlob(globVars *table[], char *name);

param_list* para_init();
param_list* para_pop(param_list *head);
void para_push(param_list *head, char *para);

void setOffset(symbol *table);

void makeTAC();
void print_all_ST();

void AR(symbol *table);
void genASM();
void printAR(symbol *table);

#endif // __PARSER_H