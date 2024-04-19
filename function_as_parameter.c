#include <stdio.h>

// Function to add two numbers
int add(int a, int b) {
    return a + b;
}

// Function to subtract two numbers
int subtract(int a, int b) {
    return a - b;
}

// Function that accepts a function pointer as a parameter
int calculate(int (*operation)(int, int), int a, int b) {
    return operation(a, b);
}

int main() {
    int x = 100, y = 200;
    int sum = calculate(add, x, y);
    int diff = calculate(subtract, x, y);
    printf("Sum: %d\n", sum); 
    printf("Difference: %d\n", diff); 
    return 0;
}
