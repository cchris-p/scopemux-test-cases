// generic_functions.ts

function identity<T>(arg: T): T {
    return arg;
}

function merge<T, U>(a: T, b: U): T & U {
    return { ...a, ...b };
}

const num = identity(42);
const str = identity("hello");
const merged = merge({ a: 1 }, { b: "two" });

console.log(num, str, merged);
