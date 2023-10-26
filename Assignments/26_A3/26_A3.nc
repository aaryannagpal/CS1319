int multiply(int a, int b) {
    return a*b;
}

int divide(int a, int b) {
    if (b == 0) {
        return -1; // Division by zero error
    } else {
        return a/b;
    }
}

int main() {
    int x = 10;
    int y = 2;
    int z;

    if (x > 0) {
        if (y > 0) {
            z = multiply(x, y);
            if (z < 20) {
                printStr("Result is less than 20.\n");
            } else {
                printStr("Result is greater than or equal to 20.\n");
            }
        } else {
            z = divide(x, y);
            if (z == -1) {
                printStr("Division by zero error.\n");
            } else {
                printStr("Division result: ");
                printInt(z);
                printStr("\n");
            }
        }
    } else {
        printStr("x is not positive.\n");
    }

    return 0;
}

