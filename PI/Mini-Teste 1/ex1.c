#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initial values
    long x = 15, y = 13;
    int v = 5;
    char d = 'n';
    
    // Variables to track maximum continuous distance in one direction
    long max_continuous = 0;
    long current_continuous = 0;
    char previous_d = d;
    
    // Simulate 10000 seconds
    for (int t = 1; t <= 10000; t++) {
        if (t % 3 == 0 && t % 5 == 0) {
            // Store previous direction before changing
            previous_d = d;
            
            // Update direction
            if (d == 'n')
                d = 'e';
            else if (d == 'e')
                d = 's';
            else if (d == 's')
                d = 'w';
            else
                d = 'n';
                
            // Direction changed, reset current continuous tracking
            if (current_continuous > max_continuous)
                max_continuous = current_continuous;
            current_continuous = 0;
            
        } else if (t % 3 == 0) {
            v += 2;
        } else if (t % 5 == 0) {
            v -= 1;
        } else {
            // Store previous direction before potentially moving
            char movement_d = d;
            
            // Move based on current direction
            if (d == 'n') {
                y += v;
                current_continuous += v;
            } else if (d == 'e') {
                x += v;
                current_continuous += v;
            } else if (d == 's') {
                y -= v;
                current_continuous += v;
            } else { // 'w'
                x -= v;
                current_continuous += v;
            }
            
            // If this is a new direction, reset continuous counter
            if (movement_d != previous_d) {
                if (current_continuous > max_continuous)
                    max_continuous = current_continuous;
                current_continuous = v;
                previous_d = movement_d;
            }
        }
    }
    
    // Check one more time in case the maximum is at the end
    if (current_continuous > max_continuous)
        max_continuous = current_continuous;
    
    printf("Final position x: %ld\n", x);
    printf("Maximum continuous distance in one direction: %ld\n", max_continuous);
    
    return 0;
}