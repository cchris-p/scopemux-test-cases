// generic_classes.ts

class Box<T> {
    value: T;
    constructor(value: T) {
        this.value = value;
    }
    getValue(): T {
        return this.value;
    }
}

const numberBox = new Box<number>(123);
const stringBox = new Box<string>("abc");

console.log(numberBox.getValue(), stringBox.getValue());

// Generic class with constraint
interface HasLength {
    length: number;
}

class LengthBox<T extends HasLength> {
    item: T;
    constructor(item: T) {
        this.item = item;
    }
    getLength(): number {
        return this.item.length;
    }
}

const arrBox = new LengthBox([1, 2, 3]);
console.log(arrBox.getLength());
