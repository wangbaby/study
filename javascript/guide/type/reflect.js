// Reflect.ownKeys
const obj = {
    a: 1,
    b: 2,
    [Symbol('obj')]: 'obj',
};

console.log(Reflect.ownKeys(obj));
