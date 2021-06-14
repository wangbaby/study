对于值类型，你可以通过typeof判断，string/number/boolean都很清楚，但是typeof在判断到引用类型的时候，返回值只有object/function，你不知道它到底是一个object对象，还是数组，还是new Number等等。

这个时候就需要用到instanceof。例如：
instanceof的判断队则是：沿着A的__proto__这条线来找，同时沿着B的prototype这条线来找，如果两条线能找到同一个引用，即同一个对象，那么就返回true。如果找到终点还未重合，则返回false。
function func() {}
func.prototype.name = '王福朋';
func.prototype.getYear = function () {
  return 1988;
};
console.log(func.__proto__ === Function.prototype);
console.log(func instanceof Object);
console.log(func instanceof Function);
console.log(Function instanceof Object);

console.log(Reflect.ownKeys(func));
console.log(Reflect.ownKeys(Function));
console.log(Reflect.ownKeys(Object));
console.log(Reflect.ownKeys(Object.prototype));

Object instanceof Function
Function instanceof Function
Function instanceof Object
