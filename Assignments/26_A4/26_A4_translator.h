#ifndef __PARSER_H
#define __PARSER_H

#define size_of_int 4
#define size_of_char 1
#define size_of_pointer 4

extern  char* yytext;
extern  int yyparse();

// const unsigned int size_of_char = 1;
// const unsigned int size_of_int = 4;
// const unsigned int size_of_pointer = 4;

/* Symbol Table */
typedef enum{
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

symbol *symlook(symbol* table, char *name);

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
// typedef enum {
// 	PLUS = 1,
// 	MINUS,
// 	MULT,
// 	DIV,
// 	UNARYMINUS,
// 	COPY,
// } opcodeType;

// typedef struct quad_tag {
// 	opcodeType op;
// 	char *result, *arg1, *arg2;
// } quad;

// quad *new_quad_binary(opcodeType op1, char *s1, char *s2, char *s3);

// quad *new_quad_unary(opcodeType op1, char *s1, char *s2);

// void print_quad(quad* q);
#endif // __PARSER_H