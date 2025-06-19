// HelloComponent.tsx
import React, { useState } from "react";

type HelloProps = {
    name: string;
    initialCount?: number;
};

export const HelloComponent: React.FC<HelloProps> = ({ name, initialCount = 0 }) => {
    const [count, setCount] = useState<number>(initialCount);

    return (
        <div>
            <h1>Hello, {name}!</h1>
            <p>Count: {count}</p>
            <button onClick={() => setCount(count + 1)}>Increment</button>
        </div>
    );
};
