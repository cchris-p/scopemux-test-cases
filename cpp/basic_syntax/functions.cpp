/**
 * Basic C++ function examples for testing AST extraction
 *
 * Contains examples of simple function declarations and definitions
 * with various parameter types and return values.
 */

// Simple function with no parameters or return value
void simple_function() {
    // Do nothing
}

// Function with parameters and return value
int add(int a, int b) {
    return a + b;
}

// Function with default parameters
double calculate_area(double radius, double pi = 3.14159) {
    return pi * radius * radius;
}

// Function with reference parameters
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function declaration only
int multiply(int x, int y);

// Function implementation
int multiply(int x, int y) {
    return x * y;
}

// Function with const parameters
double calculate_circumference(const double radius, const double pi = 3.14159) {
    return 2 * pi * radius;
}

// Overloaded function
void print(int value);
void print(double value);
void print(const char* value);

void print(int value) {
    // Implementation would print integer
}

void print(double value) {
    // Implementation would print double
}

void print(const char* value) {
    // Implementation would print string
}

// Recursive function
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
