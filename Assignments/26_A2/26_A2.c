int yylex();

int main(){
    int tok;
    
    tok = yylex();

    if (tok == -1){
        return 0;
    }
    return 0;
}