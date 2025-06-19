// HigherOrderComponent.tsx
import React from "react";

type InjectedProps = { injected: string };

function withInjectedProp<P extends object>(
    Wrapped: React.ComponentType<P & InjectedProps>
): React.FC<P> {
    return (props: P) => <Wrapped {...props} injected="Hello from HOC" />;
}

type BaseProps = { name: string };

const BaseComponent: React.FC<BaseProps & InjectedProps> = ({ name, injected }) => (
    <div>
        <p>Name: {name}</p>
        <p>Injected: {injected}</p>
    </div>
);

export const EnhancedComponent = withInjectedProp(BaseComponent);

// Example usage (not exported):
// <EnhancedComponent name="World" />
