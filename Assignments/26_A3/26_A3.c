#include <stdio.h>
#include "26_A3.tab.h"

extern void yyerror(char *s);

int main(){
    int parser = yyparse();

    if (parser == 0){
        printf("Parsing successful\n");
    } else {
        printf("Parsing failed\n");
    }

    return 0;
}