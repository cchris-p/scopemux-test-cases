/**
 * @file lambda_and_auto.cpp
 * @brief Examples of lambda expressions and type inference in modern C++
 *
 * This file demonstrates various uses of lambda expressions, auto keyword,
 * and related modern C++ features to test parser capabilities.
 */

#include <algorithm>
#include <functional>
#include <vector>
#include <string>

// Basic lambda examples
void lambda_examples() {
    // Simple lambda
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    
    // Lambda with capture
    int multiplier = 10;
    auto multiply = [multiplier](int value) {
        return value * multiplier;
    };
    
    // Lambda with mutable
    auto counter = [count = 0]() mutable {
        return ++count;
    };
    
    // Lambda with reference capture
    int value = 5;
    auto incrementer = [&value]() {
        value++;
    };
    
    // Generic lambda (C++14)
    auto generic_add = [](auto a, auto b) {
        return a + b;
    };
}

// Using auto with containers and algorithms
void auto_with_containers() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Range-based for loop with auto
    for (const auto& num : numbers) {
        // Use the number
    }
    
    // Auto with iterators
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        // Use the iterator
    }
    
    // Auto with algorithms and lambdas
    auto sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    
    // Transform with auto and lambda
    std::vector<int> doubled;
    std::transform(numbers.begin(), numbers.end(), 
                   std::back_inserter(doubled),
                   [](const auto& n) { return n * 2; });
}

// Auto for return type deduction
auto calculate_sum(int a, int b) {
    return a + b;
}

// Trailing return type syntax
auto calculate_product(int a, int b) -> int {
    return a * b;
}

// Decltype examples
template<typename T, typename U>
auto add_values(T t, U u) -> decltype(t + u) {
    return t + u;
}

// Using std::function with lambdas
void function_objects() {
    std::function<int(int, int)> adder = [](int a, int b) {
        return a + b;
    };
    
    std::function<void(int&)> increment = [](int& x) {
        ++x;
    };
}

// Immediately invoked lambda expression (IILE)
int calculate_value() {
    return [](int base) {
        int result = base;
        for (int i = 0; i < 10; ++i) {
            result += i;
        }
        return result;
    }(42);
}
