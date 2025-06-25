/**
 * @file namespaces.cpp
 * @brief Examples of namespaces and namespace-related features in C++
 *
 * This file demonstrates namespace organization, using directives,
 * nested namespaces and ADL for testing parser capabilities.
 */

// Simple namespace
namespace Basic {
    int value = 42;
    
    void print_value() {
        // Would print the value
    }
    
    class Helper {
    public:
        void assist() {
            // Implementation
        }
    };
}

// Nested namespaces
namespace Outer {
    int outer_value = 100;
    
    namespace Inner {
        int inner_value = 200;
        
        void inner_function() {
            // Implementation
        }
    }
    
    void outer_function() {
        // Can access Inner::inner_value
    }
}

// C++17 nested namespace definition
namespace Graphics::Rendering::Pipeline {
    void render() {
        // Implementation
    }
    
    class Shader {
    public:
        void compile() {
            // Implementation
        }
    };
}

// Using declarations and directives
namespace Math {
    const double PI = 3.14159265359;
    
    double square(double x) {
        return x * x;
    }
    
    double cube(double x) {
        return x * x * x;
    }
}

// Using specific elements from a namespace
void calculation_example() {
    using Math::PI;
    using Math::square;
    
    double area = PI * square(5.0);
}

// Using directive - imports all names
void calculation_extensive() {
    using namespace Math;
    
    double volume = PI * cube(5.0);
}

// Anonymous namespace
namespace {
    // This function is only visible in this translation unit
    void internal_helper() {
        // Implementation
    }
    
    // This variable is only visible in this translation unit
    int internal_value = 10;
}

// Namespace alias
namespace very_long_and_descriptive_namespace_name {
    void function_with_long_namespace() {
        // Implementation
    }
}

// Create alias
namespace shortns = very_long_and_descriptive_namespace_name;

// Using the alias
void use_alias() {
    shortns::function_with_long_namespace();
}

// Argument-dependent lookup (ADL) example
namespace ADL {
    struct Type {
        int value;
    };
    
    void process(const Type& t) {
        // Implementation
    }
}

// Function that uses ADL
void adl_example() {
    ADL::Type obj{42};
    process(obj);  // Found through ADL
}

// Reopening namespaces
namespace Basic {
    // Adding to the previously defined namespace
    int additional_value = 100;
    
    class AdditionalHelper {
    public:
        void additional_assist() {
            // Implementation
        }
    };
}
