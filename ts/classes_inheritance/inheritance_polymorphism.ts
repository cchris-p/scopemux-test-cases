// inheritance_polymorphism.ts

class Animal {
    name: string;
    constructor(name: string) {
        this.name = name;
    }
    speak(): void {
        console.log(`${this.name} makes a sound.`);
    }
}

class Dog extends Animal {
    constructor(name: string) {
        super(name);
    }
    speak(): void {
        console.log(`${this.name} barks.`);
    }
}

const animals: Animal[] = [new Animal("Generic"), new Dog("Fido")];
animals.forEach(a => a.speak());
