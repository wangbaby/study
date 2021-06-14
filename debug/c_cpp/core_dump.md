# 生成 core dump 文件

应用程序在运行过程中由于各种异常或者bug导致退出，在满足一定条件下产生一个core文件。

通常core文件包含了程序运行时内存、寄存器状态、堆栈指针、内存管理信息以及函数调用堆栈信息。

core就是程序当前工作转改存储生成的一个文件，通过工具分析这个文件，可以定位到程序异常退出的时候对应的堆栈调用等信息，找出问题点并解决。


由于 core dump 文件会占据一定的磁盘空间，默认情况下，Linux 不允许生成 core dump 文件。例如，下面的命令显示，Linux 允许的最大 core dump 文件大小为 0：
```
$ ulimit -a | grep core
core file size          (blocks, -c) 0
```

可以通过下面设置，允许 Linux 生成 core dump 文件：
```
$ ulimit -c unlimited
```
注意到，这个设置只对当前登录回话有效。如果想要这个设置持久有效，可以把它写入到/etc/security/limits.conf文件中：
```
$ sudo vi /etc/security/limits.conf
* soft core unlimited
* hard core unlimited
```

# core dump 文件的路径

那么 core dump 会存放在哪个目录呢？这是由系统参数kernel.core_pattern决定的。例如，在 Ubuntu 16.04 中，它的值如下：
```
$ cat /proc/sys/kernel/core_pattern
|/usr/share/apport/apport %p %s %c %P
```
开头的I表示，core dump 文件会交给 apport 程序去处理，而 apport 会将 core dump 文件保存在/var/crash目录下。
在实践中，更好的做法是自己指定 core dump 目录，以及 core dump 文件的命名方式：
```
$ sudo vi /etc/sysctl.conf
kernel.core_pattern=/var/crash/%E.%p.%t.%s
$ sudo sysctl -p
```
我们设置 core dump 目录为/var/crash，core dump 的命名方式为%E.%p.%t.%s，它们的含义：
```
%E：程序文件的完整路径（路径中的/会被!替代）
%p：进程 ID
%t：进程奔溃的时间戳
%s：哪个信号让进程奔溃
```