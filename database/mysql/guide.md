# 登录
```
mysql -u root -p
sudo mysql // mysql 8.0
```

# 数据库
## 创建
```
CREATE DATABASE IF NOT EXISTS database_name;
```
## 列出所有数据库
```
SHOW DATABASES;
```

## 删除
```
DROP DATABASE IF EXISTS database_name;
```

# 账号
MySQL中的用户帐户由用户名和主机名部分组成
## 列出所有用户
```
SELECT user, host FROM mysql.user;
```
## 创建
```
CREATE USER IF NOT EXISTS 'database_user'@'localhost' IDENTIFIED BY 'user_password';

```
## 更改密码
```
// mysql 8.0
ALTER USER 'database_user'@'localhost' IDENTIFIED BY 'new_password'; // 账号本身或者root 账号登录
```

## 删除账号
```
DROP USER IF EXISTS 'database_user'@'localhost';
```

# 权限
## 向MySQL用户帐户授予权限
可以向用户帐户授予多种类型的特权
```
// 授予对特定数据库用户帐户的所有特权
GRANT ALL PRIVILEGES ON database_name.* TO 'database_user'@'localhost';

// 授予对所有数据库用户帐户的所有特权
GRANT ALL PRIVILEGES ON *.* TO 'database_user'@'localhost';

// 对数据库中的特定表授予用户帐户的所有特权
GRANT ALL PRIVILEGES ON database_name.table_name TO 'database_user'@'localhost';

// 授予特定数据库类型的用户帐户特定特权
GRANT SELECT, INSERT, DELETE ON database_name.* TO database_user@'localhost';
```
## 撤消权限
```
REVOKE ALL PRIVILEGES ON database_name.* TO 'database_user'@'localhost';
```
## 显示MySQL用户帐户权限
```
SHOW GRANTS FOR 'database_user'@'localhost';
```