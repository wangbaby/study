```
~/.ssh/config

Host *
ServerAliveInterval 120

Host pi
HostName bt.awesome-daryl.cn
User pi
```

# command

```
ssh-keygen -t rsa -C "wangwangbupt@163.com"
```

# ssh 保持连接不断开

## 服务器主动保持连接

```
vim /etc/ssh/sshd_config

ClientAliveInterval 120
ClientAliveCountMax 720
```

重启 sshd 服务

第一句意思是服务端每间隔 120s 会向客户端发送一个空数据包
第二句表示服务器最大会发送 720 次,120\*720=24 小时, 24 小时期间连接是不会断开的

## 客户端主动保持连接

```
~/.ssh/config

ServerAliveInterval 120
```

每隔 120 秒向服务器发送一个空数据包

# 公钥免密码登录

所谓"公钥登录"，原理很简单，就是用户将自己的公钥储存在远程主机上。登录的时候，远程主机会向用户发送一段随机字符串，用户用自己的私钥加密后，再发回来。远程主机用事先储存的公钥进行解密，如果成功，就证明用户是可信的，直接允许登录 shell，不再要求密码。

这种方法要求用户必须提供自己的公钥。如果没有现成的，可以直接用 ssh-keygen 生成一个

运行结束以后，在$HOME/.ssh/目录下，会新生成两个文件：id_rsa.pub 和 id_rsa。前者是你的公钥，后者是你的私钥。
这时再输入下面的命令，将公钥传送到远程主机 host 上面：

```
ssh-copy-id user@host
```

如果还是不行，就打开远程主机的/etc/ssh/sshd_config 这个文件，检查下面几行前面"#"注释是否取掉。

```
RSAAuthentication yes
PubkeyAuthentication yes
AuthorizedKeysFile .ssh/authorized_keys
```

远程主机将用户的公钥，保存在登录后的用户主目录的$HOME/.ssh/authorized_keys 文件中。公钥就是一段字符串，只要把它追加在 authorized_keys 文件的末尾就行了。

这里不使用上面的 ssh-copy-id 命令，改用下面的命令，解释公钥的保存过程：

```
ssh user@host 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub
```

这条命令由多个语句组成，依次分解开来看：

- 单引号中的 mkdir .ssh && cat >> .ssh/authorized_keys，表示登录后在远程 shell 上执行的命令
- "mkdir -p .ssh"的作用是，如果用户主目录中的.ssh 目录不存在，就创建一个；
- 'cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub 的作用是，将本地的公钥文件~/.ssh/id_rsa.pub，重定向追加到远程文件 authorized_keys 的末尾。写入 authorized_keys 文件后，公钥登录的设置就完成了。
