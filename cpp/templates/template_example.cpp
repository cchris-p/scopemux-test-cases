/**
 * @file template_example.cpp
 * @brief Example demonstrating C++ template syntax
 * 
 * This file contains examples of C++ templates to test the parser's ability
 * to recognize and parse template structures.
 */

#include <iostream>
#include <vector>

/**
 * @brief A simple template function to find the maximum of two values
 * @tparam T Type parameter that supports comparison operations
 * @param a First value to compare
 * @param b Second value to compare
 * @return The larger of the two values
 */
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

/**
 * @brief A template class for a basic stack implementation
 * @tparam T Type of elements stored in the stack
 */
template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    /**
     * @brief Push an element onto the stack
     * @param element Element to push
     */
    void push(const T& element) {
        elements.push_back(element);
    }

    /**
     * @brief Pop an element from the stack
     * @return The popped element
     */
    T pop() {
        if (elements.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        T top = elements.back();
        elements.pop_back();
        return top;
    }

    /**
     * @brief Check if the stack is empty
     * @return True if stack is empty, false otherwise
     */
    bool isEmpty() const {
        return elements.empty();
    }

    /**
     * @brief Get the current size of the stack
     * @return Number of elements in the stack
     */
    size_t size() const {
        return elements.size();
    }
};

/**
 * @brief Template specialization for string type
 * Adds additional string-specific functionality
 */
template <>
class Stack<std::string> {
private:
    std::vector<std::string> elements;

public:
    void push(const std::string& element) {
        elements.push_back(element);
    }

    std::string pop() {
        if (elements.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        std::string top = elements.back();
        elements.pop_back();
        return top;
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }

    /**
     * @brief Concatenate all strings in the stack
     * @return Concatenated string
     */
    std::string concatenate() const {
        std::string result;
        for (const auto& str : elements) {
            result += str;
        }
        return result;
    }
};

/**
 * @brief A template class with multiple type parameters
 * @tparam K Key type
 * @tparam V Value type
 */
template <typename K, typename V>
class Pair {
private:
    K key;
    V value;

public:
    Pair(const K& k, const V& v) : key(k), value(v) {}

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }
};

// Main function to test the templates
int main() {
    // Test template function
    int maxInt = max<int>(10, 20);
    double maxDouble = max<double>(3.14, 2.71);
    
    std::cout << "Max int: " << maxInt << std::endl;
    std::cout << "Max double: " << maxDouble << std::endl;
    
    // Test template class
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    std::cout << "Int stack size: " << intStack.size() << std::endl;
    std::cout << "Popped: " << intStack.pop() << std::endl;
    
    // Test specialized template class
    Stack<std::string> stringStack;
    stringStack.push("Hello, ");
    stringStack.push("Template ");
    stringStack.push("World!");
    
    std::cout << "Concatenated: " << stringStack.concatenate() << std::endl;
    
    // Test multi-parameter template
    Pair<int, std::string> pair(1, "One");
    std::cout << "Pair: " << pair.getKey() << " - " << pair.getValue() << std::endl;
    
    return 0;
}
