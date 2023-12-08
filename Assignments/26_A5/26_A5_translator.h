#ifndef __PARSER_H
#define __PARSER_H

#define size_of_int 4
#define size_of_char 1
#define size_of_pointer 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DSTACK 100
#define MAXQARRAY 10000
#define MAXLIST 100
#define MAXTEMP 100

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
	TEMP
}enumcat;


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

void makeTAC();
void print_all_ST();

#endif // __PARSER_H