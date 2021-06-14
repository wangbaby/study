# 系统版本
```
ubuntu@VM-16-11-ubuntu:~/code/study$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 20.04.3 LTS
Release:        20.04
Codename:       focal
```

# 安装mysql-server
```
sudo apt update
sudo apt install mysql-server

sudo systemctl status mysql
```

# 提高mysql安全性
```
sudo mysql_secure_installation
```

# 登录
```
sudo root // mysql 8.0 上使用root登录
```