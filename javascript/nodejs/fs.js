const { access } = require("fs").promises;
const { constants } = require("fs")

async function func() {
  const err = await access("/home/ubuntu/code/study/package.json", constants.R_OK);
  if (!err) {
    console.log("acess file ok!");
  }
}

func();