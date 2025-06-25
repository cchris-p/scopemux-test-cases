/**
 * @file control_flow.cpp
 * @brief Examples of C++ control flow statements
 *
 * This file contains examples of various control flow statements in C++
 * to test the parser's ability to handle conditional logic, loops, and jumps.
 */

#include <iostream>
#include <vector>

// Basic if-else statements
void conditional_examples(int value) {
    // Simple if statement
    if (value > 0) {
        // Positive value handling
    }

    // If-else statement
    if (value % 2 == 0) {
        // Even number handling
    } else {
        // Odd number handling
    }

    // If-else if-else chain
    if (value < 0) {
        // Negative value handling
    } else if (value == 0) {
        // Zero value handling
    } else if (value > 100) {
        // Large value handling
    } else {
        // Default case handling
    }

    // Ternary operator
    bool is_positive = (value >= 0) ? true : false;

    // Nested if statements
    if (value != 0) {
        if (value > 0) {
            if (value % 2 == 0) {
                // Positive even number
            } else {
                // Positive odd number
            }
        } else {
            // Negative number
        }
    }
}

// Loop examples
void loop_examples(int count) {
    // For loop
    for (int i = 0; i < count; i++) {
        // Loop body
    }

    // While loop
    int j = 0;
    while (j < count) {
        // Loop body
        j++;
    }

    // Do-while loop
    int k = 0;
    do {
        // Loop body
        k++;
    } while (k < count);

    // Range-based for loop
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (const auto& num : numbers) {
        // Process each number
    }

    // Nested loops
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            // Nested loop body
        }
    }
}

// Break and continue
void break_continue_examples() {
    // Break example
    for (int i = 0; i < 100; i++) {
        if (i > 10) {
            break;
        }
    }

    // Continue example
    for (int i = 0; i < 20; i++) {
        if (i % 2 == 0) {
            continue;
        }
        // Only process odd numbers
    }

    // Break in nested loops
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i * j > 50) {
                break; // Breaks inner loop only
            }
        }
    }
}

// Switch statement examples
void switch_examples(int option) {
    // Basic switch
    switch (option) {
        case 1:
            // Option 1 handling
            break;
        case 2:
            // Option 2 handling
            break;
        case 3:
            // Option 3 handling
            break;
        default:
            // Default handling
            break;
    }

    // Switch with fallthrough
    switch (option) {
        case 1:
        case 2:
        case 3:
            // Handle options 1, 2, and 3 the same way
            break;
        case 4:
            // Option 4 handling
            // Falls through to case 5
        case 5:
            // Common handling for 4 and 5
            break;
        default:
            // Default handling
            break;
    }

    // Switch with initialization (C++17)
    switch (int local_scope = option * 2; local_scope) {
        case 2:
            // Handle local_scope == 2
            break;
        case 4:
            // Handle local_scope == 4
            break;
        default:
            // Default handling
            break;
    }
}

// Goto statement (rarely used but should be parsed correctly)
void goto_example() {
    int i = 0;

start:
    i++;
    if (i < 10) {
        goto start;
    }

    // Exit point
}
