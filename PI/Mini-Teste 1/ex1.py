def simulate_robot(initial_x, initial_y, initial_d, initial_v, seconds):
    x, y = initial_x, initial_y
    d = initial_d
    v = initial_v
    
    # Track the maximum continuous distance in one direction
    current_continuous_distance = 0
    max_continuous_distance = 0
    last_direction = d
    
    for t in range(1, seconds + 1):
        if t % 3 == 0 and t % 5 == 0:
            # Change direction
            if d == 'n':
                d = 'e'
            elif d == 'e':
                d = 's'
            elif d == 's':
                d = 'w'
            else:  # d == 'w'
                d = 'n'
                
            # Direction changed, reset continuous distance counter
            current_continuous_distance = 0
            last_direction = d
                
        elif t % 3 == 0:
            # Increase velocity
            v += 2
            # No movement, reset continuous distance counter
            current_continuous_distance = 0
            
        elif t % 5 == 0:
            # Decrease velocity
            v -= 1
            # No movement, reset continuous distance counter
            current_continuous_distance = 0
            
        else:
            # Move according to direction
            if d == 'n':
                y += v
            elif d == 'e':
                x += v
            elif d == 's':
                y -= v
            else:  # d == 'w'
                x -= v
                
            # Check if direction is the same as last time
            if d == last_direction:
                current_continuous_distance += v
            else:
                current_continuous_distance = v
                last_direction = d
                
            # Update max continuous distance
            max_continuous_distance = max(max_continuous_distance, current_continuous_distance)
    
    return x, y, d, v, max_continuous_distance

# Initial values
initial_x = 15
initial_y = 13
initial_d = 'n'
initial_v = 5

# Simulate for 10000 seconds
final_x, final_y, final_d, final_v, max_distance = simulate_robot(initial_x, initial_y, initial_d, initial_v, 10000)

print(f"Final position: ({final_x}, {final_y})")
print(f"Final direction: {final_d}")
print(f"Final velocity: {final_v}")
print(f"Longest continuous distance in one direction: {max_distance}")