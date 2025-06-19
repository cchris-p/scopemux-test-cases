// interfaces_and_types.ts

interface Person {
    name: string;
    age?: number; // optional property
    [key: string]: any; // index signature
}

type Employee = Person & { employeeId: string };

const alice: Person = { name: "Alice" };
const bob: Employee = { name: "Bob", employeeId: "E123", department: "HR" };

function printPerson(p: Person) {
    console.log(p.name, p.age);
}

printPerson(alice);
printPerson(bob);
