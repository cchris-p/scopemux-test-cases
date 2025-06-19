// WithChildren.tsx
import React, { ReactNode } from "react";

type WithChildrenProps = {
    title: string;
    children: ReactNode;
};

export const WithChildren: React.FC<WithChildrenProps> = ({ title, children }) => (
    <section>
        <h3>{title}</h3>
        <div className="content">{children}</div>
    </section>
);

// Example usage (not exported):
// <WithChildren title="Demo">
//     <p>This is a child element.</p>
//     <button>Click me</button>
// </WithChildren>
