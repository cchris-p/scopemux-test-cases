// variables_loops_conditions.ts
let count: number = 0;
const max: number = 5;

for (let i = 0; i < max; i++) {
  if (i % 2 === 0) {
    console.log(`Even: ${i}`);
  } else {
    console.log(`Odd: ${i}`);
  }
  count += i;
}

switch (count) {
  case 10:
    console.log("Count is ten");
    break;
  default:
    console.log("Count is not ten");
}
