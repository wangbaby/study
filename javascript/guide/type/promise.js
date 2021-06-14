const fs = require('fs');
const path = require('path');

const readFilePromise = function (fileName) {
  return new Promise((resolve, reject) => {
    fs.readFile(fileName, (err, data) => {
      if (err) reject(err);
      else resolve(data.toString());
    });
  });
};

readFilePromise('README.md')
  .then(
    (data) => {
      console.log(data);
    },
    (err) => {
      console.log(err);
    }
  )
  .then(
    (data) => {
      console.log('success', data);
    },
    (err) => {
      console.log('error', err);
    }
  );
