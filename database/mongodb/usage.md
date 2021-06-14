# mongod

```
mongod --port 27017 --dbpath /data/db1

mongod --auth --port 27017 --dbpath /data/db1 // 带访问控制

```

# mongo

```
mongo --host localhost --port 27017

mongo --host localhost --port 27017 -u "adminUser" -p "adminPass" --authenticationDatabase "admin"

```

# use

```
use admin

```

# db

## db.createUser

内建角色

- read：允许用户读取指定数据库
- readWrite：允许用户读写指定数据库
- dbAdmin：允许用户在指定数据库中执行管理函数，如索引创建、删除，查看统计或访问 system.profile
- userAdmin：允许用户向 system.users 集合写入，可以找指定数据库里创建、删除和管理用户
- clusterAdmin：只在 admin 数据库中可用，赋予用户所有分片和复制集相关函数的管理权限。
- readAnyDatabase：只在 admin 数据库中可用，赋予用户所有数据库的读权限
- readWriteAnyDatabase：只在 admin 数据库中可用，赋予用户所有数据库的读写权限
- userAdminAnyDatabase：只在 admin 数据库中可用，赋予用户所有数据库的 userAdmin 权限
- dbAdminAnyDatabase：只在 admin 数据库中可用，赋予用户所有数据库的 dbAdmin 权限。
- root：只在 admin 数据库中可用。超级账号，超级权限

```
// 如果 admin 库没有任何用户的话，即使在其他数据库中创建了用户，启用身份验证，默认的连接方式依然会有超级权限
use admin

db.createUser(
  {
    user: "adminUser",
    pwd: "adminPass",
    roles: [ { role: "userAdminAnyDatabase", db: "admin" } ],
  }
)

// use foo表示用户在 foo 库中创建，就一定要 foo 库验证身份，即用户的信息跟随随数据库。比如上述 simpleUser 虽然有 bar 库的读取权限，但是一定要先在 foo 库进行身份验证，直接访问会提示验证失败。
use foo

db.createUser(
  {
    user: "simpleUser",
    pwd: "simplePass",
    roles: [ { role: "readWrite", db: "foo" },
             { role: "read", db: "bar" } ]
  }
)

use foo
db.auth("simpleUser", "simplePass")

use bar
show collections

```

## db.auth

# URI

```
mongodb://simpleUser:simplePass@your.db.ip.address:27017/foo
```
