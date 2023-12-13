int armstrong(int lim){
    int num = 0;
    int cnt = 0;
    for (num = 0; num <= lim; num = num + 1) { 
        int copy = 0;
        int sum = 0; 
        copy = num; 
        sum = 0;
        while (num != 0) { 
            int rem = 0; 
            rem = num % 10; 
            sum = sum + (rem * rem * rem); 
            num = num / 10; 
        }
    if (copy == sum) cnt = cnt + 1;
    num = copy; 
    }
    return cnt;
}

int main() { 
    int lim;
    lim = 10000; 

    int cnt = armstrong(lim);
}