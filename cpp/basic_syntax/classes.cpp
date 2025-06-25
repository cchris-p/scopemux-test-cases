/**
 * Basic C++ class examples for testing AST extraction
 *
 * Contains examples of class definitions with member variables,
 * methods, constructors, and inheritance.
 */

// Simple class definition
class SimpleClass {
private:
    int value;

public:
    // Constructor
    SimpleClass(int initialValue) : value(initialValue) {}

    // Member function
    int getValue() const {
        return value;
    }

    // Mutator
    void setValue(int newValue) {
        value = newValue;
    }
};

// Class with inheritance
class Shape {
protected:
    double x, y;

public:
    Shape(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
    virtual ~Shape() {}

    // Pure virtual function
    virtual double calculateArea() = 0;

    // Regular virtual function with implementation
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
    }
};

// Derived class
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double xCoord, double yCoord, double r) 
        : Shape(xCoord, yCoord), radius(r) {}

    // Override
    double calculateArea() override {
        return 3.14159 * radius * radius;
    }
};

// Class with static members
class Counter {
private:
    int count;
    static int totalCount;

public:
    Counter() : count(0) {
        totalCount++;
    }

    static int getTotalCount() {
        return totalCount;
    }
};

// Static member initialization
int Counter::totalCount = 0;

// Class with friend function
class Rectangle {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    friend double calculateArea(const Rectangle& rect);
};

// Friend function implementation
double calculateArea(const Rectangle& rect) {
    return rect.width * rect.height;
}
