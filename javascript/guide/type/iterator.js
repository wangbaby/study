// symbol 数据类型可以作为对象类型的key
console.log(Symbol.iterator);
console.log(Array.prototype[Symbol.iterator]);

const arr = [1, 2, 3];

for (let i of arr) console.log(i);

let iter = arr[Symbol.iterator]();
console.log(typeof iter);
for (let i of iter) console.log(i);

iter = arr[Symbol.iterator]();

console.log(iter[Symbol.iterator]);
console.log(iter.next());
console.log(iter.next());
console.log(iter.next());
console.log(iter.next());
