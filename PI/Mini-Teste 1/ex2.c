#include <stdio.h>

int main() {
    // Initial values - using the values from the question
    long x = 15, y = 13;
    int v = 5;
    char d = 'n';
    
    // Tracking variables
    long max_continuous = 0;
    long current_continuous = 0;
    char last_movement_dir = d;
    
    // Number of seconds to simulate
    int total_seconds = 10000;
    
    // Simulate robot movement
    for (int t = 1; t <= total_seconds; t++) {
        // Save previous state for tracking
        char prev_d = d;
        
        if (t % 3 == 0 && t % 5 == 0) {
            // Change direction
            if (d == 'n')
                d = 'e';
            else if (d == 'e')
                d = 's';
            else if (d == 's')
                d = 'w';
            else  // d == 'w'
                d = 'n';
            
            // Direction changed, reset continuous counter
            if (current_continuous > max_continuous)
                max_continuous = current_continuous;
            current_continuous = 0;
            
        } else if (t % 3 == 0) {
            // Increase speed
            v += 2;
            
        } else if (t % 5 == 0) {
            // Decrease speed
            v -= 1;
            
        } else {
            // Move in current direction
            if (d == 'n') {
                y += v;
            } else if (d == 'e') {
                x += v;
            } else if (d == 's') {
                y -= v;
            } else {  // d == 'w'
                x -= v;
            }
            
            // Update continuous distance tracking
            if (d == last_movement_dir) {
                current_continuous += v;
            } else {
                if (current_continuous > max_continuous)
                    max_continuous = current_continuous;
                current_continuous = v;
                last_movement_dir = d;
            }
        }
        
        // Debugging output for the example in the problem statement
        if (t <= 4) {
            printf("After second %d: position=(%ld,%ld), velocity=%d, direction=%c\n", 
                   t, x, y, v, d);
        }
    }
    
    // Final check for max continuous distance
    if (current_continuous > max_continuous)
        max_continuous = current_continuous;
    
    // Output final results
    printf("\nFinal results after %d seconds:\n", total_seconds);
    printf("Position: (%ld,%ld)\n", x, y);
    printf("Velocity: %d\n", v);
    printf("Direction: %c\n", d);
    printf("Max continuous distance in one direction: %ld\n", max_continuous);
    
    return 0;
}