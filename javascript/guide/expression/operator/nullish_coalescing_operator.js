// 空值合并操作符（??）是一个逻辑操作符，当左侧的操作数为 null 或者 undefined 时，返回其右侧操作数，否则返回左侧操作数

const a = null ?? 'hello';
console.log(a);

const b = 0 ?? 'world';
console.log(b);
