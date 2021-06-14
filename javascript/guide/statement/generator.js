function* func() {
  const a = yield 1;
  console.log(a);
  yield 2;
  yield 3;
}

/**
let it = func();
for (let i of it) console.log(i);
*/

it = func();
let res = it.next();
console.log(res);
console.log(it.next(res));

const fs = require('fs');

const thunk = function (file, codeType) {
  return function (callback) {
    fs.readFile(file, codeType, callback);
  };
};

const readfileThunk = thunk();
