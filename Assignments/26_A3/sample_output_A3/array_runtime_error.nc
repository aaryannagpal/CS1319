int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int index = 7; // Attempt to access an out-of-bounds index

    for(int i=1; i<index; i++){
        int value = arr[i];
        printStr("Value at index ");
        printInt(i);
        printStr(": ");
        printInt(value);
        printStr("\n");
    }

    return 0;
}
