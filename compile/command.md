# ldd

查看依赖的共享库

```
ldd /bin/bash
ldd --version #glibc 版本
```

# ldconfig

ldconfig 主要是在默认搜寻目录/lib 和/usr/lib 以及动态库配置文件/etc/ld.so.conf 内所列的目录下，搜索出可共享的动态链接库（格式如 lib*.so*）,进而创建出动态装入程序(ld.so)所需的连接和缓存文件。

缓存文件默认为/etc/ld.so.cache，此文件保存已排好序的动态链接库名字列表，为了让动态链接库为系统所共享，需运行动态链接库的管理命令 ldconfig，此执行程序存放在/sbin 目录下。

```
ldconfig -p # 查看所有共享库
```

# ld

动态装载器（dynamic loader），即在 ldd 清单中看到的作为共享库相关性列出的 ld-linux.so 库, 它负责装入动态链接的可执行程序运行所需的共享库

动态装载器找到共享库要依靠两个文件 : /etc/ld.so.conf 和 /etc/ld.so.cache

ld.so.conf 文件包含一个所有目录（/lib 和 /usr/lib 除外，它们会自动包含在其中）的清单，动态装入器将在其中查找共享库。但是在动态装入器能“看到”这一信息之前，必须将它转换到 ld.so.cache 文件中。可以通过运行 ldconfig 命令做到这一点:当 ldconfig 操作结束时，会有一个最新的 /etc/ld.so.cache 文件，它反映对 /etc/ld.so.conf 所做的更改.从这一刻起，动态装入器在寻找共享库时会查看在 /etc/ld.so.conf 中指定的所有新目录.

```
ld a.o b.o -e main -o ab
// -e main: 将 main 函数作为程序入口，ld 链接器默认程序入口为_start
// -o ab: 链接输出名为 ab, 而不是默认的 a.out
```

# gcc

gcc

glibc

从 libc 说起。libc 是 Linux 下原来的标准 C 库，也就是当初写 hello world 时包含的头文件#include <stdio.h> 定义的地方，后来逐渐被 glibc 取代，也就是传说中的 GNU C Library,在此之前除了有 libc，还有 klibc,uclibc。现在只要知道用的最多的是 glibc 就行了，主流的一些 linux 操作系统如 Debian, Ubuntu，Redhat 等用的都是 glibc 或者其变种，下面会说到。

那 glibc 都做了些什么呢？

glibc 是 Linux 系统中最底层的 API，几乎其它任何的运行库都要依赖 glibc。

glibc 最主要的功能就是对系统调用的封装，你想想看，你怎么能在 C 代码中直接用 fopen 函数就能打开文件？ 打开文件最终还是要触发系统中的 sys_open 系统调用，而这中间的处理过程都是 glibc 来完成的。除了封装系统调用，glibc 自身也提供了一些上层应用函数必要的功能,如 string,malloc,stdlib,linux threads,locale,signal 等等。

那 eglibc 又是什么？ 这里的 e 是 Embedded 的意思，也就是前面说到的变种 glibc。eglibc 的主要特性是为了更好的支持嵌入式架构，可以支持不同的 shell(包括嵌入式)，但它是二进制兼容 glibc 的，就是说如果你的代码之前依赖 eglibc 库，那么换成 glibc 后也不需要重新编译。

你写的 C 代码在编译的过程中有可能出现明明是这些库里面定义的变,却量还会出现’Undefined’, ‘Unreference’等错误，这时候你可能会怀疑是不是这些库出问题了？ 是不是该动手换个 gilbc/eglibc 了？ 这里强调一点，在你准备更换/升级这些库之前，你应该好好思考一下，你真的要更换/升级吗？你要知道你自己在做什么！你要时刻知道 glibc/eglibc 的影响有多大，不管你之前部署的什么程序，linux 系统的 ls,cd,mv,ps 等等全都得依赖它，很多人在更换/升级都有过惨痛的教训，甚至让整个系统奔溃无法启动。所以，强烈不建议更换/升级这些库！

libc++ / libstdc++

当然如果你写的是 C++代码，还有两个库也要非常重视了，libc++/libstdc++,这两个库有关系吗？有。
两个都是 C++标准库。libc++是针对 clang 编译器特别重写的 C++标准库，那 libstdc++自然就是 gcc 的事儿了。

libstdc++与 gcc 的关系就像 clang 与 libc++.

说说 libstdc++，glibc 的关系。

libstdc++与 gcc 是捆绑在一起的，也就是说安装 gcc 的时候会把 libstdc++装上。 那为什么 glibc 和 gcc 没有捆绑在一起呢？相比 glibc，libstdc++虽然提供了 c++程序的标准库，但它并不与内核打交道。对于系统级别的事件，libstdc++首先是会与 glibc 交互，才能和内核通信。相比 glibc 来说，libstdc++就显得没那么基础了。

```
--version gcc 版本

-g 生成调试信息: -g 选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是把整个源文件嵌入到可执行文件中，所以在调试时必须保证 gdb 能找到源文件

-Wall 显式警告信息

-O1 使用优化级别编译程序。级别为 1~3，级别越大优化效果越好，但编译时间越长

gcc -E SimpleSection.c -o SimpleSection.i 输出预处理后文件

gcc -c SimpleSection.c -o SimpleSection.o 只编译不链接,生成目标文件

gcc -S SimpleSection.c -o SimpleSection.s 输出汇编文件

gcc -c SimpleSection.s -o SimpleSection.o 将输出的汇编文件进行汇编

gcc hello.c -o hello 输出完整文件

gcc sin.c -lm -L/lib -L/lib64 -I/usr/include
-l : 加入某个函数库(library)”. m 则是 libm.so 这个函数库，其中 lib 与扩展名(.a 或 .so)不需要写.

-L/path: 由于 Linux 默认是将函数库放置在 /lib 与 /lib64 当中，所以没有写 -L/lib 与 -L/lib64 也没有关系!不过，万一哪天使用的函数库并非放置在这两个目录下，那么 -L/path 就很重要了,否则会找不到函数库.

-I/path: 设置要去搜寻相关的 include 文件的目录

gcc -fPIC -shared -o Lib.so Lib.c
-shared: 表示产生共享对象 -fPIC 生成地址无关代码

gcc -o Program1 Program1.c ./Lib.so 链接生成的 Lib.so
```



objdump

objdump -h SimpleSection.o

打印 elf 文件中关键段的基本信息

objdump -d SimpleSection.o

-d 代码段进行反汇编

objdump -s -d SimpleSection.o

-s 十六进制打印所有段的内容，-d 代码段进行反汇编

objdump -r SimpleSection.o

查看重定位表

readelf

ELF 文件格式解析器

readelf -h SimpleSection.o

查看 ELF 文件头

readelf -S SimpleSection.o

查看 ELF 文件段表的内容

readelf -s SimpleSection.o

查看 ELF 文件符号表的内容

nm

nm SimpleSection.o

查看符号表

ar

ar -t /usr/lib/x86_64-linux-gnu/libc.a

查看静态库包含了哪些目标文件

```

```

```

gcc -ggdb3 -std=c99 -Wall -Wextra -pedantic -o main.out main.c 



-lm -lprotobuf -lpthread

在Linux平台上最广泛使用的C函数库是glibc，其中包括C标准库的实现。几乎所有C程序都要调用glibc的库函数，所以glibc是Linux平台C程序运行的基础。glibc提供一组头文件和一组库文件，最基本、最常用的C标准库函数和系统函数在libc.so库文件中，几乎所有C程序的运行都依赖于libc.so，有些做数学计算的C程序依赖于libm.so，以后我们还会看到多线程的C程序依赖于libpthread.so。以后我说libc时专指libc.so这个库文件，而说glibc时指的是glibc提供的所有库文件