// namespaces_example.ts

namespace Geometry {
    export function areaOfCircle(radius: number): number {
        return Math.PI * radius * radius;
    }
    export function areaOfSquare(side: number): number {
        return side * side;
    }
}

const circleArea = Geometry.areaOfCircle(2);
const squareArea = Geometry.areaOfSquare(3);

console.log(circleArea, squareArea);
