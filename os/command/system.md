  

  id -u 
  id -g
  
  systemd

cut
  dmesg

dmesg可以在应用程序crash时，显示内核中保存的相关信息。通过dmesg命令可以查看发生段错误的程序名称、引起段错误发生的内存地址、指令指针地址、堆栈指针地址、错误代码、错误原因等

  cron

  ls

  ls -lh 以KB、MB等为单位进行显示

ls -l | grep "^-" | wc -l   查看某个文件夹下文件的个数。
ls -lR | grep "^-" | wc -l   查看某个文件夹下文件的个数，包括子文件夹下的文件个数。
ls -l | grep "^d" | wc -l   查看某个文件夹下文件夹的个数。
ls -lR | grep "^d" | wc -l   查看某个文件夹下文件夹的个数，包括子文件夹下的文件夹个数。
ls -l | wc -l   查看文件夹下所有的文件和文件夹。也就是统计 ls -l 命令所输出的行数

  chsh: 切换 shell

  expr

  计算表达式，表达式和运算符之间要有空格

var=$(expr 2 + 3)
echo ${var}

   date

DATE=$(date "+%Y-%m-%d %H:%M:%S")
echo $DATE

   df

  disk full:检查文件系统的磁盘空间占用情况

df -h
df -aT
df -h /etc   将 /etc 底下的可用的磁盘容量以易读的容量格式显示

   du

  disk used: 检查磁盘空间使用量

du   只列出当前目录下的所有文件夹容量（包括隐藏文件夹）
du -a   将文件的容量也列出来
du -sm /_   检查根目录底下每个目录所占用的容量
du -s /_ | sort -nr   增加排序
du -h –max-depth=1 *，可以查看当前目录下各文件、文件夹的大小
查询当前目录总大小可以使用du -sh，其中s代表统计汇总的意思，即只输出一个总和大小
通过命令du -h –max-depth=0 *，可以只显示直接子目录文件及文件夹大小统计值

   fdisk

  Linux 的磁盘分区表操作工具

fdisk -l

   mdfs 磁盘格式化

   fsck 磁盘校验

   mount

   umount

   /etc/passwd

  对所有用户可读

  用户名:口令:用户标识号:组标识号:注释性描述:主目录:登录 Shell

  pseudo user: 这些用户在/etc/passwd 文件中也占有一条记录，但是不能登录，因为它们的登录 Shell 为空。它们的存在主要是方便系统管理，满足相应的系统进程对文件属主的要求

   /etc/shadow

  /etc/shadow 中的记录行与/etc/passwd 中的一一对应，它由 pwconv 命令根据/etc/passwd 中的数据自动产生

   /etc/group

  组名:口令:组标识号:组内用户列表

  当一个用户同时是多个组中的成员时，在/etc/passwd 文件中记录的是用户所属的主组，也就是登录时所属的默认组，而其他组称为附加组

  用户要访问属于附加组的文件时，必须首先使用 newgrp 命令使自己成为所要访问的组中的成员

   useradd

  在系统中创建一个新账号，然后为新账号分配用户号、用户组、主目录和登录 Shell 等资源。刚添加的账号是被锁定的，无法使用

  增加用户账号就是在/etc/passwd 文件中为新用户增加一条记录，同时更新其他系统文件如/etc/shadow, /etc/group

  useradd -g daryl -G sudo -d /home/daryl -m daryl

   userdel

  userdel -r daryl

   usermod

  passwd

  用户管理的一项重要内容是用户口令的管理。用户账号刚创建时没有口令，但是被系统锁定，无法使用，必须为其指定口令后才可以使用，即使是指定空口令

  指定和修改用户口令的 Shell 命令是 passwd。超级用户可以为自己和其他用户指定口令，普通用户只能用它修改自己的口令

   groupadd

   groupdel

   groupmod

   newgrp

   chgrp

  chgrp -R 组名 文件名

   chown

  更改文件属主，也可以同时更改文件属组

  chown [–R] 属主名 文件名

  chown [-R] 属主名：属组名 文件名

  chmod

4 2 1 / u g o a + - =

   文件夹

文件夹的读和写权限依赖文件夹是否具有执行权限，而文件没有此类限制
- 执行权限 : 代表能否进入文件夹
- 读权限 : 代表能否查看文件夹中的东西
- 写权限 : 代表能否在文件夹中添新东西

   ln

  Linux 链接分两种，一种被称为硬链接（Hard Link），另一种被称为符号链接（Symbolic Link）。默认情况下，ln 命令产生硬链接

 

  硬连接

  硬连接指通过索引节点来进行连接。在 Linux 的文件系统中，保存在磁盘分区中的文件不管是什么类型都给它分配一个编号，称为索引节点号(Inode Index)。

  在 Linux 中，多个文件名指向同一索引节点是存在的。一般这种连接就是硬连接。

  硬连接的作用是允许一个文件拥有多个有效路径名，这样用户就可以建立硬连接到重要文件，以防止“误删”的功能。

  其原因如上所述，因为对应该目录的索引节点有一个以上的连接。只删除一个连接并不影响索引节点本身和其它的连接，只有当最后一个连接被删除后，文件的数据块及目录的连接才会被释放。

  也就是说，文件真正删除的条件是与之相关的所有硬连接文件均被删除。

 

  软连接

  另外一种连接称之为符号连接（Symbolic Link），也叫软连接。软链接文件有类似于 Windows 的快捷方式。它实际上是一个特殊的文件。在符号连接中，文件实际上是一个文本文件，其中包含的有另一文件的位置信息。

 

  touch f1           创建一个测试文件 f1

  ln f1 f2           创建 f1 的一个硬连接文件 f2

  ln -s f1 f3        创建 f1 的一个符号连接文件 f3

  ls -li              -i 参数显示文件的 inode 节点信息

  total 0

  9797648 -rw-r--r--  2 oracle oinstall 0 Apr 21 08:11 f1

  9797648 -rw-r--r--  2 oracle oinstall 0 Apr 21 08:11 f2

  9797649 lrwxrwxrwx  1 oracle oinstall 2 Apr 21 08:11 f3 -> f1

 场景
ln 覆盖已存在的普通文件或目录.

创建软链接
创建一个普通文件的软链接

$ ln -s ~/.bashrc /tmp/test
$ ll /tmp/ | grep test
lrwxrwxrwx  1 cryven users        20 Jan 27 18:43 test -> /home/cryven/.bashrc
如果文件已存在，则会创建失败.

$ ln -s  ~/.vimrc /tmp/test
ln: failed to create symbolic link '/tmp/test': File exists
目录的软链接创建同上

覆盖已存在的文件
普通文件软链接
使用 -f 选项覆盖已存在的普通文件.

$ ln -sf  ~/.vimrc /tmp/test
$ ll /tmp/ | grep test
lrwxrwxrwx  1 cryven users        19 Jan 27 18:52 test -> /home/cryven/.vimrc
目录软链接
-f 选项在对目录的软链接覆盖，不会覆盖原来的，而是在此引用的目录里创建新的引用.

$ ln -s ~/demo/ /tmp/test1
$ ll /tmp/ | grep test1
lrwxrwxrwx  1 cryven users        18 Jan 27 18:56 test1 -> /home/cryven/demo/

$ ln -sf ~/.vim /tmp/test1
$ ll /tmp/ | grep test1
lrwxrwxrwx  1 cryven users        18 Jan 27 18:56 test1 -> /home/cryven/demo/

$ ll -a /tmp/test1/ | grep vim # .vim 的软链接创建在 test1 目录里了
lrwxrwxrwx  1 cryven users   18 Jan 27 19:05 .vim -> /home/cryven/.vim/
使用 -n 和 -f 选项来覆盖目录的软链接.

$ ln -snf ~/.vim /tmp/test1
$ ll /tmp/ | grep test1
lrwxrwxrwx 1 cryven users    17 Jan 27 19:11 test1 -> /home/cryven/.vim
-n treat LINK_NAME as a normal file if it is a symbolic link to a directory

作者：Cryven
链接：https://www.jianshu.com/p/af924a4210dc
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

  echo "I am f1 file" >>f1

 

  rm -f f1

  cat f2

  I am f1 file

  cat f3

  cat: f3: No such file or directory

 

  通过上面的测试可以看出：当删除原始文件 f1 后，硬连接 f2 不受影响，但是符号连接 f3 文件无效

   tar

  五个是独立的命令，可以和别的命令连用但只能用其中一个。

  -c: 建立压缩档案

  -x：解压

  -t：查看内容

  -r：向压缩归档文件末尾追加文件

  -u：更新原压缩包中的文件

 

 

  根据需要在压缩或解压档案时可选的。

  -z：有 gzip 属性的

  -j：有 bz2 属性的

  -Z：有 compress 属性的

  -v：显示所有过程

  -O：将文件解开到标准输出

 

  -f 是必须的

  -f: 使用档案名字，切记，这个参数是最后一个参数，后面只能接档案名。

 

  tar -cf all.tar \*.jpg // 这条命令是将所有.jpg 的文件打成一个名为 all.tar 的包。-c 是表示产生新的包，-f 指定包的文件名。

  tar -rf all.tar \*.gif // 这条命令是将所有.gif 的文件增加到 all.tar 的包里面去。-r 是表示增加文件的意思。

  tar -uf all.tar logo.gif // 这条命令是更新原来 tar 包 all.tar 中 logo.gif 文件，-u 是表示更新文件的意思。

  tar -tf all.tar // 这条命令是列出 all.tar 包中所有文件，-t 是列出文件的意思

  tar -xf all.tar // 这条命令是解出 all.tar 包中所有文件，-x 是解开的意思

  tar -cvf jpg.tar \*.jpg //将目录里所有 jpg 文件打包成 tar.jpg

  tar -czvf jpg.tar.gz \*.jpg   //将目录里所有 jpg 文件打包成 jpg.tar 后，并且将其用 gzip 压缩，生成一个 gzip 压缩过的包，命名为 jpg.tar.gz

  tar -cjvf jpg.tar.bz2 \*.jpg //将目录里所有 jpg 文件打包成 jpg.tar 后，并且将其用 bzip2 压缩，生成一个 bzip2 压缩过的包，命名为 jpg.tar.bz2

  tar -cZvf jpg.tar.Z \*.jpg   //将目录里所有 jpg 文件打包成 jpg.tar 后，并且将其用 compress 压缩，生成一个 umcompress 压缩过的包，命名为 jpg.tar.Z

  tar -xvf file.tar //解压 tar 包

  tar -xzvf file.tar.gz //解压 tar.gz

  tar -xjvf file.tar.bz2   //解压 tar.bz2

  tar -xZvf file.tar.Z   //解压 tar.Z

   scp

  scp -r {用户名}@{ip}:{remote directory} {local directory} // 远程到本地

  scp -r {local directory} {用户名}@{ip}:{remote directory} // 本地到远程

   lsb_release

lsb_release -a   查看 ubuntu 版本

https://blog.csdn.net/qq_38461773/article/details/107593999