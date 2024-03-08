#include <stdio.h>

// Functions from your previous code
int fizz(int n) {
    return ((n + 4) % 43) == 0;
}

int buzz(int n) {
    return ((n + 6) % 52) == 0;
}

void fizzbuzz(int n) {
    if (fizz(n) && buzz(n))
        printf("FizzBuzz\n");
    else if (fizz(n))
        printf("Fizz\n");
    else if (buzz(n))
        printf("Buzz\n");
    else
        printf("%d\n", n);
}

// The fizzbuzz_range function (modified)
void fizzbuzz_range(int from, int to) {
    int fizz_count = 0; // Moved fizz_count inside the function

    for (int i = from; i < to; i++) {
        if (fizz(i)) { // Check for Fizz
            fizz_count++; 
        }
        fizzbuzz(i); // Call fizzbuzz for full output
    }

    printf("Número de linhas 'Fizz': %d\n", fizz_count); // Print count after the loop
}

int main() {
    fizzbuzz_range(247, 5247); 
    return 0;
}