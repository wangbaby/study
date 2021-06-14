// 可选链操作符( ?. )允许读取位于连接对象链深处的属性的值，而不必明确验证链中的每个引用是否有效
// obj?.prop;
// obj?.[expr];
// arr?.[index];
// func?.(args);

const obj = {
  a: 1,
  b: {
    c: 2,
    d: {
      e: 3,
    },
  },
};

console.log(obj?.b?.c, obj?.b?.f ?? 'hello');

const arr = '123';
console.log(arr?.filter((value) => value > 1));
