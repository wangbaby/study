# gdb

the GNU Project debugger

-ggdb3: 包含更多调试信息 如调试宏需要设置

# command

## help

help : GDB 帮助命令，提供对 GDB 名种命令的解释说明。如果指定了“命令名称”参数，则显示该命令的详细说明；如果没有指定参数，则分类显示所有 GDB 命令，供用户进一步浏览和查询。

## shell 

执行 shell 命令行 

## pwd 

显示当前目录

## file

加载被调试的可执行程序文件 

## directory

设置源文件的目录

## quit (q)
退出 GDB 调试环境
 
## kill
 
将强行终止当前正在调试的程序 
 
## Ctrl + l

刷新窗口

## Ctrl + x

- Ctrl + x 再按 1：单窗口模式，显示一个窗口
- Ctrl + x 再按 2：双窗口模式，显示两个窗口
- Ctrl + x 再按 a：回到传统模式，即退出 layout，回到执行 layout 之前的调试窗口

## layout

用于分割窗口，可以一边查看代码，一边测试
- layout src：显示源代码窗口
- layout asm：显示反汇编窗口
- layout regs：显示源代码/反汇编和 CPU 寄存器窗口
- layout split：显示源代码和反汇编窗口 


## list (l)

从第一行开始列出源码, 默认每次显示 10 行 

- list 行号：将显示当前文件以“行号”为中心的前后 10 行代码
- list 函数名：将显示“函数名”所在函数的源代码

## break (b)

- break n :在第 n 行处设置断点 
- break func：在函数 func()的入口处设置断点
- break test.c:6 ：在 test.c 上设置这个断点
- break [where] if [condition] : 条件断点 

## clear 

清除断点 

## disable 

暂停断点 

## enable

开启断点 

## delete (d)

delete: 删除所有断点
delete <断点id>: 删除指定断点 

## run (r)

运行程序 

## call

调用“函数”，并传递“参数”

## continue (c)

继续执行被调试程序，直至下一个断点或程序结束 

## next (n)

执行一行源程序代码，此行代码中的函数调用也一并执行, 相当于其它调试器中的"Step Over"(单步跟踪)”

ni 所针对的是汇编指令，而 n 针对的是源代码

## step (s)

执行一行源程序代码，如果此行代码中有函数调用，则进入该函数，相当于其它调试器中的“Step Into (单步跟踪进入)

”si 所针对的是汇编指令，而 s 针对的是源代码 

## until

当你厌倦了在一个循环体内单步跟踪时，这个命令可以运行程序直到退出循环体

## finish

运行程序，直到当前函数完成返回，并打印函数返回时的堆栈地址和返回值及参数值等信息

## backtrace (bt)

查看函数堆栈

## frame (f)

f 1 :选择 1 号栈帧

## watch

设置一个监视点，一旦被监视的“表达式”的值改变，gdb 将强行终止正在被调试的程序

## info (i)

用于显示各类信息

- info watchpoints
- info break
- info locals
- info symbol

## x 

查看内存 x/32xb 0x555555557d90 : 十六进制显示 32 个字节 

## print (p)

打印表达式的值, 其中“表达式”可以是任何当前正在被测试程序的有效表达式

- print a：将显示 a 的值 
- print ++a：将把 a 中的值加 1,并显示出来 
- print gdb_test(22)：将以整数 22 作为参数调用 gdb_test() 函数
- print gdb_test(a)：将以变量 a 作为参数调用 gdb_test() 

## set

set args 参数:指定运行时的参数
set environment varname [=value] 设置环境变量 如：set env USER=hchen

## show

show args：查看设置好的参数
show environment [varname] 查看环境变量
show configuration


## display

在单步运行时将非常有用，使用 display 命令设置一个表达式后，它将在每次单步进行指令后，紧接着输出被设置的表达式及值

设置程序中断后欲显示的数据及其格式。例如，如果希望每次程序中断后可以看到即将被执行的下一条汇编指令，可以使用命令“display /i $pc”其中 $pc 代表当前汇编指令，/i 表示以十六进行显示。当需要关心汇编代码时，此命令相当有用

## undispaly

取消先前的 display 设置，编号从 1 开始递增

# 多线程调试

- break file.c:100 thread all 在 file.c 文件第 100 行处为所有经过这里的线程设置断点。
- info threads 查看当前进程的线程, GDB 会为每个线程分配一个 ID, 后面操作线程的时候会用到这个 ID. 前面有\*的是当前调试的线程.
- thread <ID> 切换调试的线程为指定 ID 的线程。
- thread apply ID1 ID2 command 让一个或者多个线程执行 GDB 命令 command
- thread apply all command  让所有被调试线程执行 GDB 命令 command

## set scheduler-locking off|on|step

在使用 step 或者 continue 命令调试当前被调试线程的时候，其他线程也是同时执行的,怎么只让被调试程序执行呢？
- off 不锁定任何线程，也就是所有线程都执行，这是默认值。
- on 只有当前被调试程序会执行。
- step 

# 调试宏

在 GDB 下, 我们无法 print 宏定义，因为宏是预编译的。但是我们还是有办法来调试宏，这个需要 GCC 的配合。在 GCC 编译程序的时候，加上-ggdb3参数，这样，你就可以调试宏了。

- info macro 查看这个宏在哪些文件里被引用了，以及宏定义是什么样的。
- macro 查看宏展开的样子
