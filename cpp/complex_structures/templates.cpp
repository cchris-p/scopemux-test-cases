/**
 * Complex C++ template examples for testing AST extraction
 *
 * Contains examples of template classes, template functions, specialization,
 * and more complex template metaprogramming patterns.
 */

// Basic function template
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Class template with multiple type parameters
template<typename T, typename U>
class Pair {
private:
    T first;
    U second;

public:
    Pair(T f, U s) : first(f), second(s) {}

    T getFirst() const { return first; }
    U getSecond() const { return second; }

    void setFirst(const T& f) { first = f; }
    void setSecond(const U& s) { second = s; }
};

// Template specialization
template<>
class Pair<int, int> {
private:
    int first;
    int second;
    int sum;  // Additional member for specialized version

public:
    Pair(int f, int s) : first(f), second(s), sum(f + s) {}

    int getFirst() const { return first; }
    int getSecond() const { return second; }
    int getSum() const { return sum; }

    void setValues(int f, int s) {
        first = f;
        second = s;
        sum = f + s;
    }
};

// Variadic template function
template<typename T>
T addAll(T value) {
    return value;
}

template<typename T, typename... Args>
T addAll(T first, Args... args) {
    return first + addAll(args...);
}

// Template with non-type parameters
template<typename T, int Size>
class FixedArray {
private:
    T data[Size];

public:
    FixedArray() {}

    T& operator[](int index) {
        return data[index];
    }

    int getSize() const {
        return Size;
    }
};

// Template template parameter
template<typename T, template<typename> class Container>
class CustomCollection {
private:
    Container<T> data;

public:
    void add(const T& item) {
        // Implementation would add item to container
    }
    
    // Implementation would continue here
};

// SFINAE example with enable_if
template<typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
isEven(T value) {
    return value % 2 == 0;
}

// Curiously recurring template pattern (CRTP)
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
    
    void implementation() {
        // Default implementation
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        // Specialized implementation
    }
};
