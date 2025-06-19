// RenderPropExample.tsx
import React, { useState } from "react";

type CounterProps = {
    children: (count: number, increment: () => void) => React.ReactNode;
};

export const Counter: React.FC<CounterProps> = ({ children }) => {
    const [count, setCount] = useState(0);
    const increment = () => setCount((c) => c + 1);
    return <>{children(count, increment)}</>;
};

// Example usage (not exported):
// <Counter>
//   {(count, increment) => (
//     <div>
//       <p>Count: {count}</p>
//       <button onClick={increment}>Increment</button>
//     </div>
//   )}
// </Counter>
