// primitives_vs_any.ts

let str: string = "hello";
let num: number = 42;
let bool: boolean = true;
let anyValue: any = "could be anything";

function printValues(a: string, b: number, c: boolean, d: any) {
    console.log(a, b, c, d);
}

printValues(str, num, bool, anyValue);
