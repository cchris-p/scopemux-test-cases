/**
 * @file template_specialization.cpp
 * @brief Examples of template specialization patterns in C++
 *
 * This file demonstrates full and partial template specialization
 * for testing the parser's ability to handle complex template code.
 */

#include <iostream>
#include <type_traits>

// Primary template
template<typename T>
struct TypeIdentifier {
    static constexpr const char* name = "unknown";
    
    void identify() {
        // Generic implementation
    }
};

// Full specialization for int
template<>
struct TypeIdentifier<int> {
    static constexpr const char* name = "int";
    
    void identify() {
        // int-specific implementation
    }
};

// Full specialization for double
template<>
struct TypeIdentifier<double> {
    static constexpr const char* name = "double";
    
    void identify() {
        // double-specific implementation
    }
};

// Primary template with multiple parameters
template<typename T, typename U>
struct PairType {
    T first;
    U second;
    
    PairType(T t, U u) : first(t), second(u) {}
    
    void process() {
        // Generic implementation
    }
};

// Partial specialization (first type is int)
template<typename U>
struct PairType<int, U> {
    int first;
    U second;
    
    PairType(int t, U u) : first(t), second(u) {}
    
    void process() {
        // Partially specialized implementation
    }
};

// Partial specialization (both types are the same)
template<typename T>
struct PairType<T, T> {
    T first;
    T second;
    
    PairType(T t1, T t2) : first(t1), second(t2) {}
    
    void process() {
        // Specialized implementation for same types
    }
};

// Template specialization with non-type parameters
template<typename T, int Size>
class Array {
private:
    T data[Size];
    
public:
    Array() {}
    
    T& operator[](int index) {
        return data[index];
    }
    
    constexpr int size() const {
        return Size;
    }
};

// Specialization for Size = 0
template<typename T>
class Array<T, 0> {
public:
    Array() {}
    
    constexpr int size() const {
        return 0;
    }
};

// Complex nested specialization
template<typename T, typename U, template<typename> class Container>
struct CompositeType {
    Container<T> first;
    Container<U> second;
};

// Recursive templates for compile-time computation
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

// Base case specialization
template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// SFINAE example with enable_if
template<typename T, 
         typename = typename std::enable_if<std::is_integral<T>::value>::type>
T add_one(T value) {
    return value + 1;
}
