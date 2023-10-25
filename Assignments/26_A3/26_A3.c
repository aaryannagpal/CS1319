#include <stdio.h>
#include "26_A3.tab.h"

extern void yyerror(char *s);

int main(){
    int parser = yyparse();
    return 0;
}