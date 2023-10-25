int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int x = 5;
    int result = factorial(x);
    printStr("The factorial of ");
    printInt(x);
    printStr(" is ");
    printInt(result);
    return 0;
}

