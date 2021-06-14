/**
 * typeof
 * 
 *  javascript中变量类型分为值类型（基本数据类型）和引用类型
 * (1) 值类型：string,number,boolean，undefined，null
 * (2) 引用类型：Array，Object，Function...

 * 2. 值类型和引用类型的区别
 * (1) 存储位置不一样
 * ① 值类型的变量会保存在栈内存中。
 * ② 引用类型的变量名会保存在栈内存中，但是变量值会存储在堆内存中。
 * 
 * (2) 复制方式不一样
 * ① 值类型的变量直接赋值就是深复制。
 * ② 引用类型的变量直接赋值实际上是传递引用，只是浅复制。
 * 
 * (3) 值类型无法添加属性和方法，引用类型可以添加属性和方法
 * 
 * (4) 值类型的比较是值的比较，引用类型的比较是引用地址的比较
 */
{
  console.log(typeof 1);
  console.log(typeof '1');
  console.log(typeof true);
  console.log(typeof undefined);
  console.log(typeof null);

  console.log(typeof class {});
  const func = () => {};
  console.log(typeof func);

  console.log(typeof {});
}
