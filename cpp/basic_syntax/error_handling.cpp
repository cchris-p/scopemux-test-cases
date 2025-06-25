/**
 * @file error_handling.cpp
 * @brief Examples of C++ exception handling and error management techniques
 *
 * This file demonstrates various error handling patterns in C++
 * to test the parser's ability to handle try-catch blocks,
 * exception specifications, and related constructs.
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <system_error>
#include <functional>

// Custom exception classes
class ApplicationException : public std::exception {
private:
    std::string message;

public:
    ApplicationException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class DatabaseException : public ApplicationException {
public:
    DatabaseException(const std::string& msg) : ApplicationException("Database error: " + msg) {}
};

// Basic exception handling
void basic_exception_handling() {
    try {
        // Code that might throw
        throw std::runtime_error("Something went wrong");
    } catch (const std::runtime_error& e) {
        // Handle runtime_error
        std::cerr << "Runtime error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // Handle other standard exceptions
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        // Catch all other exceptions
        std::cerr << "Unknown exception caught" << std::endl;
    }
}

// Exception specifications
void might_throw_runtime_error() {
    throw std::runtime_error("Runtime error occurred");
}

// noexcept specification
void never_throws() noexcept {
    // This function guarantees it won't throw exceptions
}

// Conditional noexcept
template<typename T>
void conditional_noexcept(T value) noexcept(std::is_nothrow_move_constructible<T>::value) {
    T copy = std::move(value);
}

// Function try-catch blocks
int function_try_catch(bool should_throw) {
    try {
        if (should_throw) {
            throw std::logic_error("Logic error in function");
        }
        return 42;
    } catch (const std::exception& e) {
        std::cerr << "Caught in function: " << e.what() << std::endl;
        return -1;
    }
}

// Constructor with member initializer list and try-catch
class ResourceManager {
private:
    std::unique_ptr<int[]> resource;
    
public:
    ResourceManager(size_t size)
    try : resource(new int[size]) {
        // Constructor body
        for (size_t i = 0; i < size; ++i) {
            resource[i] = i;
        }
    } catch (const std::bad_alloc& e) {
        std::cerr << "Allocation failed: " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
};

// RAII pattern for resource management
class FileHandle {
private:
    FILE* file;
    
public:
    FileHandle(const char* filename, const char* mode) {
        file = fopen(filename, mode);
        if (!file) {
            throw std::runtime_error("Failed to open file");
        }
    }
    
    ~FileHandle() {
        if (file) {
            fclose(file);
        }
    }
    
    // Prevent copying
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
};

// System error handling
void system_error_example() {
    try {
        std::error_code ec;
        // Some operation that sets error code
        if (ec) {
            throw std::system_error(ec, "System operation failed");
        }
    } catch (const std::system_error& e) {
        std::cerr << "System error: " << e.what() << std::endl;
        std::cerr << "Error code: " << e.code().value() << std::endl;
        std::cerr << "Category: " << e.code().category().name() << std::endl;
    }
}

// Nested exception handling
void nested_exception_example() {
    try {
        try {
            throw std::runtime_error("Inner exception");
        } catch (const std::exception& e) {
            std::throw_with_nested(std::logic_error("Outer exception"));
        }
    } catch (const std::nested_exception& e) {
        try {
            std::rethrow_if_nested(e);
        } catch(const std::exception& nested) {
            std::cerr << "Nested exception: " << nested.what() << std::endl;
        }
    }
}

// Exception handling with standard library functions
void standard_library_exceptions() {
    // vector bounds checking
    try {
        std::vector<int> v = {1, 2, 3};
        auto item = v.at(10); // This will throw std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    
    // Bad cast
    try {
        std::string s = "test";
        auto& i = dynamic_cast<std::vector<int>&>(s); // Will throw std::bad_cast
    } catch (const std::bad_cast& e) {
        std::cerr << "Bad cast: " << e.what() << std::endl;
    }
}

// Cleanup with finally pattern (C++11 approach)
void finally_pattern(std::function<void()> cleanup) {
    struct FinalAction {
        std::function<void()> action;
        FinalAction(std::function<void()> a) : action(std::move(a)) {}
        ~FinalAction() { action(); }
    };
    
    FinalAction finally(cleanup);
    
    // Code that might throw
    throw std::runtime_error("Error during processing");
    
    // Cleanup will still be called due to RAII
}
