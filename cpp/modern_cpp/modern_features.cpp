/**
 * @file modern_features.cpp
 * @brief Example demonstrating modern C++ features
 * 
 * This file showcases features from C++11 and later standards
 * to test the parser's ability to handle modern C++ code.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

/**
 * @brief Example of auto type deduction
 * @param container Any container supporting begin/end
 */
template <typename Container>
void printContainer(const Container& container) {
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief A simple class to demonstrate unique pointer ownership
 */
class Resource {
private:
    std::string name;
    
public:
    Resource(const std::string& n) : name(n) {
        std::cout << "Resource " << name << " created" << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource " << name << " destroyed" << std::endl;
    }
    
    void use() const {
        std::cout << "Using resource " << name << std::endl;
    }
};

/**
 * @brief Demonstrates lambda expressions and std::function
 * @param value Input value
 * @param operation Function to apply to the value
 * @return Result of the operation
 */
int applyOperation(int value, std::function<int(int)> operation) {
    return operation(value);
}

/**
 * @brief Class that uses move semantics
 */
class MovableObject {
private:
    std::vector<int> data;
    
public:
    // Constructor
    MovableObject(std::vector<int> d) : data(std::move(d)) {}
    
    // Move constructor
    MovableObject(MovableObject&& other) noexcept : data(std::move(other.data)) {
        std::cout << "Move constructor called" << std::endl;
    }
    
    // Move assignment operator
    MovableObject& operator=(MovableObject&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            std::cout << "Move assignment called" << std::endl;
        }
        return *this;
    }
    
    const std::vector<int>& getData() const {
        return data;
    }
};

int main() {
    // Auto type deduction
    auto x = 42;
    auto y = 3.14;
    
    // Range-based for loop
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    printContainer(numbers);
    
    // Smart pointers
    auto resource = std::make_unique<Resource>("primary");
    resource->use();
    
    // Lambda expressions
    auto square = [](int x) { return x * x; };
    auto cube = [](int x) { return x * x * x; };
    
    std::cout << "Square of 5: " << applyOperation(5, square) << std::endl;
    std::cout << "Cube of 5: " << applyOperation(5, cube) << std::endl;
    
    // Move semantics
    std::vector<int> vec = {10, 20, 30, 40, 50};
    MovableObject obj1(std::move(vec));
    MovableObject obj2 = std::move(obj1);
    
    // C++11 algorithm with lambda
    std::vector<int> moreNumbers = {3, 1, 4, 1, 5, 9, 2, 6};
    std::sort(moreNumbers.begin(), moreNumbers.end(), 
              [](int a, int b) { return a > b; });
    
    std::cout << "Sorted in descending order: ";
    printContainer(moreNumbers);
    
    return 0;
}
