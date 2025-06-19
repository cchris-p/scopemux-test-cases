// DiscriminatedUnionProps.tsx
import React from "react";

type SuccessProps = { status: "success"; message: string };
type ErrorProps = { status: "error"; error: Error };
type LoadingProps = { status: "loading" };

type StatusProps = SuccessProps | ErrorProps | LoadingProps;

export const StatusMessage: React.FC<StatusProps> = (props) => {
    switch (props.status) {
        case "success":
            return <div style={{ color: "green" }}>Success: {props.message}</div>;
        case "error":
            return <div style={{ color: "red" }}>Error: {props.error.message}</div>;
        case "loading":
            return <div>Loading...</div>;
        default:
            return null;
    }
};

// Example usage (not exported):
// <StatusMessage status="success" message="Loaded!" />
// <StatusMessage status="error" error={new Error("Failed!")} />
// <StatusMessage status="loading" />
