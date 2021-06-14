const MongoClient = require('mongodb').MongoClient;
const url = 'mongodb://localhost/';

async function dataOperate() {
  var conn = null;
  try {
    conn = await MongoClient.connect(url);
    console.log('数据库已连接');
    const test = conn.db('wang').collection('test');
    // 增加
    await test.insertOne({ site: 'runoob.com' });
  } catch (err) {
    console.log('错误：' + err.message);
  } finally {
    if (conn != null) conn.close();
  }
}

dataOperate();
