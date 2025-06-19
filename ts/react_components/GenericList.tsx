// GenericList.tsx
import React from "react";

type GenericListProps<T> = {
    items: T[];
    renderItem: (item: T, index: number) => React.ReactNode;
};

export function GenericList<T>({ items, renderItem }: GenericListProps<T>): JSX.Element {
    return (
        <ul>
            {items.map((item, idx) => (
                <li key={idx}>{renderItem(item, idx)}</li>
            ))}
        </ul>
    );
}

// Example usage (not exported):
// <GenericList items={[1, 2, 3]} renderItem={(n) => <span>{n}</span>} />
