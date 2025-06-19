// ClassCounter.tsx
import React from "react";

type ClassCounterProps = {
    start: number;
};

type ClassCounterState = {
    count: number;
};

export class ClassCounter extends React.Component<ClassCounterProps, ClassCounterState> {
    constructor(props: ClassCounterProps) {
        super(props);
        this.state = { count: props.start };
    }

    increment = () => {
        this.setState((prevState) => ({ count: prevState.count + 1 }));
    };

    render() {
        return (
            <div>
                <h2>Class Counter</h2>
                <p>Count: {this.state.count}</p>
                <button onClick={this.increment}>Increment</button>
            </div>
        );
    }
}
