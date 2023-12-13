
int fact(int n){
    if(n == 0) return 1;
    return fact(n-1) * n;
}

int choose(int n, int r){
    if(r == 0) return 1;
    if(n == 0) return 0;
    return fact(n)/(fact(r) * fact(n-r));
}

int main() { 
    int n = 5; int r = 2;
    int res = choose(n, r);
}