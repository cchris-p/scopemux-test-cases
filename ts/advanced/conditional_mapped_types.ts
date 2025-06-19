// conditional_mapped_types.ts

// Mapped type: Make all properties optional
type Partial<T> = { [P in keyof T]?: T[P] };

type User = {
    id: number;
    name: string;
    email: string;
};

type PartialUser = Partial<User>;

// Conditional type: Exclude
type Exclude<T, U> = T extends U ? never : T;

type Primitive = string | number | boolean;
type NonString = Exclude<Primitive, string>;

// Example usage
const user: PartialUser = { id: 1 };
const value: NonString = 42;
