// es6_modules.ts

// moduleA.ts
export function greet(name: string): string {
    return `Hello, ${name}!`;
}

// moduleB.ts
import { greet } from "./moduleA";

const message = greet("World");
console.log(message);
