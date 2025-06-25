/**
 * @file class_example.cpp
 * @brief Example demonstrating C++ class syntax
 * 
 * This file contains examples of C++ classes with methods,
 * constructors, and inheritance to test the parser.
 */

#include <iostream>
#include <string>

/**
 * @brief A simple Person class to demonstrate class structure
 */
class Person {
private:
    std::string name;
    int age;

public:
    /**
     * @brief Default constructor
     */
    Person() : name("Unknown"), age(0) {}

    /**
     * @brief Parameterized constructor
     * @param n Person's name
     * @param a Person's age
     */
    Person(const std::string& n, int a) : name(n), age(a) {}

    /**
     * @brief Get person's name
     * @return Person's name as string
     */
    std::string getName() const {
        return name;
    }

    /**
     * @brief Get person's age
     * @return Person's age as integer
     */
    int getAge() const {
        return age;
    }

    /**
     * @brief Print person's information
     */
    void printInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

/**
 * @brief A Student class that inherits from Person
 */
class Student : public Person {
private:
    std::string studentId;

public:
    /**
     * @brief Student constructor
     * @param n Student's name
     * @param a Student's age
     * @param id Student's ID
     */
    Student(const std::string& n, int a, const std::string& id)
        : Person(n, a), studentId(id) {}

    /**
     * @brief Get student ID
     * @return Student ID as string
     */
    std::string getStudentId() const {
        return studentId;
    }
    
    /**
     * @brief Print student information
     */
    void printInfo() const {
        Person::printInfo();
        std::cout << "Student ID: " << studentId << std::endl;
    }
};

// Main function to test the classes
int main() {
    // Create instances of the classes
    Person person("John Doe", 30);
    Student student("Jane Smith", 20, "S12345");
    
    // Print information
    person.printInfo();
    student.printInfo();
    
    return 0;
}
