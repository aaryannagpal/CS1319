#include <stdio.h>
#include "26_A4.tab.h"

extern void yyerror(char *s);
extern int yyparse();

int main(){
    int parser = yyparse();
    return 0;
}