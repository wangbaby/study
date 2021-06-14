const express = require('express');
const app = express();
const port = 8000;
const process = require('process');
const https = require('https');
const fs = require('fs');

const key = fs.readFileSync('private.key');
const cert = fs.readFileSync('mydomain.crt');

const options = {
  key,
  cert,
};
app.get('/', (req, res) => {
  console.log(process.pid);
  process.send({
    type: 'process:msg',
    data: {
      success: process.pid,
    },
  });
  res.status(200).send('hello');
});

https.createServer(options, app).listen(port);
