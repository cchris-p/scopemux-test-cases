/**
 * @file preprocessor.cpp
 * @brief Examples of C++ preprocessor directives and macros
 *
 * This file demonstrates various preprocessor features to test
 * the parser's ability to handle conditional compilation,
 * macro definition, and other preprocessor constructs.
 */

#include <iostream>

// Basic macro definitions
#define PI 3.14159265359
#define MAX_SIZE 100
#define UNUSED(x) (void)(x)
#define SQUARE(x) ((x) * (x))

// Function-like macros
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CONCAT(a, b) a ## b

// Multiline macro with backslash continuation
#define MULTI_LINE_MACRO(x, y) do { \
    int temp = x; \
    x = y; \
    y = temp; \
} while(0)

// Stringification
#define STRINGIFY(x) #x
#define EXPAND_AND_STRINGIFY(x) STRINGIFY(x)

// Conditional compilation
#ifdef DEBUG
#define LOG(msg) std::cout << "[DEBUG] " << msg << std::endl
#else
#define LOG(msg) ((void)0)
#endif

// Error directive for compile-time assertions
#if __cplusplus < 201103L
#error "This code requires C++11 or later"
#endif

// Include guards example (usually in header files)
#ifndef HEADER_GUARD_H
#define HEADER_GUARD_H
// Header content would go here
#endif

// Pragma directives
#pragma once  // Modern include guard alternative
#pragma warning(disable: 4996)  // Disable specific compiler warning

// Predefined macros
void predefined_macros() {
    // These will be replaced with appropriate values by preprocessor
    const char* file = __FILE__;
    int line = __LINE__;
    const char* date = __DATE__;
    const char* time = __TIME__;
    const char* function = __func__; // Not preprocessor but similar usage
}

// Conditional compilation with #if, #elif, #else
#if defined(_WIN32)
#define PLATFORM "Windows"
#elif defined(__APPLE__)
#define PLATFORM "macOS"
#elif defined(__linux__)
#define PLATFORM "Linux"
#else
#define PLATFORM "Unknown"
#endif

// Complex nested directives
#ifdef FEATURE_X
#  ifdef FEATURE_Y
#    define COMBINED_FEATURES
#  else
#    ifdef FEATURE_Z
#      define ALTERNATE_COMBO
#    endif
#  endif
#endif

// Token pasting operator example
#define MAKE_FUNCTION(name, type) type get_##name() { return name##_value; }

// Various real-world macro patterns
#define DECLARE_PROPERTY(type, name) \
    private: \
        type m_##name; \
    public: \
        type get_##name() const { return m_##name; } \
        void set_##name(const type& value) { m_##name = value; }

#define SAFE_DELETE(ptr) do { if (ptr) { delete ptr; ptr = nullptr; } } while(0)

// Testing the macros in actual code
int global_value = 42;
MAKE_FUNCTION(global, int)

class PropertyTest {
    DECLARE_PROPERTY(int, count)
    DECLARE_PROPERTY(std::string, name)
};

// Function that uses macros
void test_macros() {
    int a = 5, b = 10;
    int max_val = MAX(a, b);
    int min_val = MIN(a, b);
    int squared = SQUARE(a);
    
    // Concatenation example
    int concat12 = CONCAT(1, 2);  // becomes int concat12 = 12;
    
    // Stringification example
    const char* str_macro = STRINGIFY(Hello World);  // becomes "Hello World"
    
    // Swap with multiline macro
    MULTI_LINE_MACRO(a, b);
}
