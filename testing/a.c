#include <stdio.h>

// Function C: Modifies the variable via pointer
void C_modify(int *x) {
    *x = 99;
}

// Function B: Passes the pointer to C
void B_forward(int ptr) {
    C_modify(&ptr);
}

// Function A: Declares the variable and calls B
void A_call()
{
    int number = 0;
    printf("Before: number = %d\n", number);

    B_forward(number);

    printf("After:  number = %d\n", number);
}

int main() {
    A_call();
    return 0;
}
