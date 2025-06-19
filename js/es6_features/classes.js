// JavaScript program demonstrating classes

// Class declaration
class Animal {
    constructor(name) {
        this.name = name;
    }

    speak() {
        return this.name + " makes a noise.";
    }
}

// Class instantiation
const dog = new Animal("Dog");
console.log(dog.speak()); // Output: Dog makes a noise.
