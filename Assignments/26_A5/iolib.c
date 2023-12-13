#include "iolib.h"
#include <unistd.h>
#include <stdbool.h>


// refered GFG: https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

int printStr(char *str) {
    int len = 0;
    for (len = 0; str[len] != '\0'; len++);  // Calculate string length

    write(1, str, len);  // Write to STDOUT
    return len;
}

int printInt(int num) {
    char buffer[100];
    int index = 0, bytes;
    bool isNegative = false;

    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    do {
        buffer[index++] = (num % 10) + '0'; // Get the digit
        num /= 10;
    } while (num != 0);

    if (isNegative) {
        buffer[index++] = '-';
    }

    for (int i = 0; i < index / 2; i++) { // Reverse the string
        char temp = buffer[i];
        buffer[i] = buffer[index - 1 - i];
        buffer[index - 1 - i] = temp;
    }

    bytes = index;
    write(1, buffer, bytes);
    return bytes;
}

int readInt(int *error) {
    char buffer[100]; // Buffer to store the input
    int index = 0, sign = 1; 
    *error = OK; // No error

    while (1) {
        read(0, &buffer[index], 1); // Read one character

        if (buffer[index] == '-' && index == 0) {
            sign = -1;
            continue;
        }

        if (buffer[index] == '\n' || buffer[index] == '\t' || buffer[index] == ' ' || buffer[index] == '\0') {
            break;
        }

        if (buffer[index] < '0' || buffer[index] > '9') {
            *error = ERROR;
            return 0;
        }

        index++;
    }

    int num = 0;
    for (int i = 0; i < index; i++) {
        num = num * 10 + (buffer[i] - '0');
    }

    return num * sign;
}