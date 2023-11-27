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
#define MAXEXPLIST 100

extern  char* yytext;
extern  int yyparse();

// const unsigned int size_of_char = 1;
// const unsigned int size_of_int = 4;
// const unsigned int size_of_pointer = 4;

/* Symbol Table */
typedef enum{
	TYPE_VOID_PTR = -3,
	TYPE_INT_PTR,
	TYPE_CHAR_PTR,
	TYPE_VOID,
	TYPE_INT,
	TYPE_CHAR,
	TYPE_PTR
}enumtype;

typedef struct sym {
	char *name;
	enumtype type;
	void *value;
	int size;
	int offset;
	// symboltable *nested_table;
	struct sym *nested_table;
	struct sym *next;   
}symbol;

// typedef struct symtab {
// 	char *name;
// 	symboltable *parent;
// 	symbol *syms;
// }symboltable;

extern symbol *global_table;
extern symbol *current_table;

symbol *symlook(symbol *table, char *name);
void print_symboltable(symbol *table);
symbol *create_symboltable();
symbol *update_symboltable(symbol *table, char *name, enumtype type, char *value, int size);
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
extern data_type ptrType ;
typedef struct exp{
	symbol *loc;
	bool isArray;
	bool isPointer;
	bool isBoolean;

	int trueList[MAXEXPLIST];
	int falseList[MAXEXPLIST];

	int nextList[MAXEXPLIST];


}Expression;

/* TAC generation support */
// symbol *gentemp();

// void emit_binary(
// 	char *s1,  // Result
// 	char *s2,  // Arg 1
// 	char c,    // Operator
// 	char *s3); // Arg 2

// void emit_unary(
// 	char *s1, // Result
// 	char *s2, // Arg 1
// 	char c);  // Operator

// void emit_copy(
// 	char *s1,  // Result
// 	char *s2); // Arg 1

// /* Support for Lazy TAC generation through Quad array */
typedef enum {
	ASSIGN = 1,
	PLUS,
	MINUS,
	MULT,
	DIV,
	MOD,

	
	ADDR,
	PTR_ASSIGN,
	UPLUS,
	UMINUS,
	NOT,


	PARAM,
} opcodeType;

typedef struct quad_tag {
	opcodeType op;
	char *result, *arg1, *arg2;
} quad;

extern quad *QuadArray[MAXQARRAY];

void emit(opcodeType op, char *result, char *arg1, char *arg2);
void print_quad_array();


void copyArray(int *dest, int *src, int size);

// quad *new_quad_binary(opcodeType op1, char *s1, char *s2, char *s3);

// quad *new_quad_unary(opcodeType op1, char *s1, char *s2);

// void print_quad(quad* q);
#endif // __PARSER_H