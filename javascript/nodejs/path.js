const path = require('path');
const { resolve, extname, basename } = require('path');

const filePath = path.resolve(__dirname, 'path.js');
console.log(filePath);

console.log(extname(filePath));
console.log(basename(filePath));
console.log(basename(filePath, extname(filePath)));
