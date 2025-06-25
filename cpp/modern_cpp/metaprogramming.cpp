/**
 * @file metaprogramming.cpp
 * @brief Examples of C++ template metaprogramming techniques
 *
 * This file demonstrates advanced template metaprogramming constructs
 * for testing the parser's ability to handle complex template code.
 */

#include <type_traits>
#include <utility>
#include <tuple>

// Compile-time factorial calculation
template<unsigned N>
struct Factorial {
    static constexpr unsigned value = N * Factorial<N - 1>::value;
};

// Specialization for base case
template<>
struct Factorial<0> {
    static constexpr unsigned value = 1;
};

// Type traits and SFINAE example
template<typename T>
struct has_toString {
private:
    // Test for existence of toString method
    template<typename C>
    static auto test(int) -> decltype(std::declval<C>().toString(), std::true_type());

    // Fallback for types without toString
    template<typename>
    static auto test(...) -> std::false_type;

public:
    // Result is the type returned by the test
    static constexpr bool value = decltype(test<T>(0))::value;
};

// Enable_if for conditional function templates
template<typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_even(T value) {
    return value % 2 == 0;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
is_even(T value) {
    // For floating point, consider "close enough" to be even
    return std::fabs(std::fmod(value, 2.0)) < 0.00001;
}

// Tag dispatch pattern
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template<typename Iterator>
void advance_impl(Iterator& it, int n, input_iterator_tag) {
    // For input iterators, can only move forward one at a time
    while (n > 0) {
        ++it;
        --n;
    }
}

template<typename Iterator>
void advance_impl(Iterator& it, int n, random_access_iterator_tag) {
    // For random access iterators, can jump directly
    it += n;
}

// Public interface using tag dispatch
template<typename Iterator>
void advance(Iterator& it, int n) {
    advance_impl(it, n, typename Iterator::iterator_category());
}

// Type list implementation
template<typename... Ts>
struct TypeList {};

// Finding the Nth type in a parameter pack
template<size_t N, typename First, typename... Rest>
struct NthType {
    using type = typename NthType<N-1, Rest...>::type;
};

template<typename First, typename... Rest>
struct NthType<0, First, Rest...> {
    using type = First;
};

// Variadic templates with fold expressions (C++17)
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

// Conditional compilation with concepts (C++20 style)
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T>
T multiply(T a, T b) {
    return a * b;
}

// Type traits library usage
template<typename T>
void check_type() {
    if constexpr (std::is_integral_v<T>) {
        // Integer type handling
    } else if constexpr (std::is_floating_point_v<T>) {
        // Floating point type handling
    } else if constexpr (std::is_class_v<T>) {
        // Class type handling
    }
}

// Type transformation traits
template<typename T>
using RemoveCVRef = std::remove_cv_t<std::remove_reference_t<T>>;

// Tuple manipulation with template metaprogramming
template<size_t... Is, typename Tuple>
auto select_tuple_elements(std::index_sequence<Is...>, Tuple&& tuple) {
    return std::make_tuple(std::get<Is>(std::forward<Tuple>(tuple))...);
}

template<size_t... Is, typename Tuple>
auto selective_tuple(Tuple&& tuple) {
    return select_tuple_elements(std::index_sequence<Is...>{}, 
                               std::forward<Tuple>(tuple));
}

// Compile-time if with constexpr (C++17)
template<typename T>
auto get_value(T t) {
    if constexpr (std::is_pointer_v<T>) {
        return *t; // Dereference pointers
    } else {
        return t;  // Return by value for non-pointers
    }
}

// CRTP (Curiously Recurring Template Pattern)
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }

    // Default implementation
    void implementation() {
        // Default behavior
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        // Override with specific behavior
    }
};

// Mixin pattern with templates
template<typename Base>
class Mixin1 : public Base {
public:
    void feature1() {
        // Implementation of feature 1
    }
};

template<typename Base>
class Mixin2 : public Base {
public:
    void feature2() {
        // Implementation of feature 2
    }
};

// Base class without functionality
class EmptyBase {};

// Final composed class with all features
using ComposedClass = Mixin2<Mixin1<EmptyBase>>;

// Policy-based design
template<typename InputPolicy, typename ProcessingPolicy, typename OutputPolicy>
class DataProcessor {
private:
    InputPolicy inputPolicy;
    ProcessingPolicy processingPolicy;
    OutputPolicy outputPolicy;

public:
    void process() {
        auto data = inputPolicy.getData();
        auto result = processingPolicy.process(data);
        outputPolicy.output(result);
    }
};

// Expression templates (simplified example)
template<typename T>
class Vector {
private:
    T* data;
    size_t size;

public:
    Vector(size_t s) : size(s) {
        data = new T[size];
    }

    ~Vector() {
        delete[] data;
    }

    // Element access
    T& operator[](size_t idx) {
        return data[idx];
    }

    const T& operator[](size_t idx) const {
        return data[idx];
    }

    size_t getSize() const {
        return size;
    }
};

// Expression template for addition
template<typename LHS, typename RHS>
class VectorAddExpr {
private:
    const LHS& lhs;
    const RHS& rhs;

public:
    VectorAddExpr(const LHS& l, const RHS& r) : lhs(l), rhs(r) {}

    auto operator[](size_t idx) const {
        return lhs[idx] + rhs[idx];
    }

    size_t getSize() const {
        return lhs.getSize();
    }
};

// Addition operator that returns expression template
template<typename LHS, typename RHS>
VectorAddExpr<LHS, RHS> operator+(const LHS& lhs, const RHS& rhs) {
    return VectorAddExpr<LHS, RHS>(lhs, rhs);
}
