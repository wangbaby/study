const { set } = require('express/lib/application');

function arrayLikeTest() {
  // eslint-disable-next-line prefer-rest-params
  Array.prototype.forEach.call(arguments, (item) => {
    console.log(item);
  });
}
{
  // array-like
  // 类数组是什么呢？顾名思义，就是具备与数组特征类似的对象。比如，下面的这个对象，就是一个类数组

  const arrayLike = {
    0: 1,
    1: 2,
    2: 3,
    length: 3,
  };
  console.log(arrayLike[0], arrayLike.length);
  // 类数组可以通过下标调用，具有length属性，同时也可以通过 for 循环进行遍历
  // 类数组，还是比较常用的，只是我们平时可能没注意到。比如，我们获取 DOM 节点的方法，返回的就是一个类数组。
  // 再比如，在一个方法中使用 arguments 获取到的所有参数，也是一个类数组。
  // 但是需要注意的是：类数组无法使用 forEach、splice、push 等数组原型链上的方法，毕竟它不是真正的数组。
  arrayLikeTest(1, 2, 3);
}

// sort
{
  const arr = [1, 4, 2, 3, 5];
  arr.sort((a, b) => a - b);
  console.log(arr);
}

// shift
{
  const arr = [1, 2, 3];
  console.log(arr.shift(), arr);
}

// splice
{
  const arr = [1, 2, 3, 4, 5];
  // remove 3
  arr.splice(arr.indexOf(3), 1);
  console.log(arr);
}

// reduce
{
  const arr = [1, 2, 3, 4, 5];
  const sum = arr.reduce((last, i) => last + i, 0);
  console.log(sum);
}

{
  const arr = [1, 1, '1', new Date()];
  console.log(arr);
  const s = new Set(arr);
  console.log(s);
  console.log(typeof s);
  console.log(Object.prototype.toString.call(s));
}
