// oop_basics.ts

class Animal {
    name: string;
    constructor(name: string) {
        this.name = name;
    }
    speak(): void {
        console.log(`${this.name} makes a sound.`);
    }
}

const dog = new Animal("Rex");
dog.speak();
