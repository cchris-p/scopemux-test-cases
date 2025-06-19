// union_intersection_types.ts

type Admin = { role: "admin"; accessLevel: number };
type User = { role: "user"; name: string };

type Person = Admin | User;

function printPerson(p: Person) {
    if (p.role === "admin") {
        console.log(`Admin with access: ${p.accessLevel}`);
    } else {
        console.log(`User: ${p.name}`);
    }
}

// Intersection type
type Timestamped = { createdAt: Date };
type Post = { title: string } & Timestamped;

const post: Post = { title: "Hello", createdAt: new Date() };
