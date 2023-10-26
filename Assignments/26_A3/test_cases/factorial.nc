int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int n = 5;
    int result = factorial(n);
    printStr("Factorial of ");
    printInt(n);
    printStr(" is ");
    printInt(result);
    return 0;
}

