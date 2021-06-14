// ES7
const { readFile } = require('fs').promises;

async function read(file) {
  await readFile(file);

  console.log(file + ' done');
}
// async 函数返回promise
// const res = read('README.md');

// res.then((data) => {
//   console.log(data);
// });

// test async/await in array
async function test() {
  const fileArr = ['README.md', '.prettierrc', '.gitignore'];
  for (const index in fileArr) {
    await read(fileArr[index]);
  }
}

test();
