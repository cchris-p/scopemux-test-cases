// JavaScript program demonstrating objects

// Object creation
let person = {
    name: "John",
    age: 30,
    greet: function() {
        return "Hello, my name is " + this.name;
    }
};

// Accessing object properties and methods
console.log(person.name); // Output: John
console.log(person.age);  // Output: 30
console.log(person.greet()); // Output: Hello, my name is John
