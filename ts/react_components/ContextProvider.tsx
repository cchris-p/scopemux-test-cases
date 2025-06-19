// ContextProvider.tsx
import React, { createContext, useContext, useState, ReactNode } from "react";

type Theme = "light" | "dark";
type ThemeContextType = { theme: Theme; toggleTheme: () => void };

const ThemeContext = createContext<ThemeContextType | undefined>(undefined);

export const ThemeProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
    const [theme, setTheme] = useState<Theme>("light");
    const toggleTheme = () => setTheme((t) => (t === "light" ? "dark" : "light"));
    return (
        <ThemeContext.Provider value={{ theme, toggleTheme }}>
            {children}
        </ThemeContext.Provider>
    );
};

export const ThemeConsumerComponent: React.FC = () => {
    const ctx = useContext(ThemeContext);
    if (!ctx) return <div>No theme context</div>;
    return (
        <div>
            <p>Current theme: {ctx.theme}</p>
            <button onClick={ctx.toggleTheme}>Toggle Theme</button>
        </div>
    );
};
