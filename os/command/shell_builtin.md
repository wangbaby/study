# ulimit

ulimit命令用来限制系统用户对shell资源的访问。

- -a 显示当前所有的资源限制;
- -c size: 设置core文件的最大值，单位:blocks;
- -n size: 设置内核可以同时打开的文件描述符的最大值





# type: 命令类型
type type # type is shell builtin
type set  # set is shell builtin

# read : 读取输入
# read name

# echo
echo "it is a test"
echo it is a test # 双引号可以省略

echo "\"it is a test \""
echo \"it is a test \"

# read name
echo "$name it is a test"

echo -e "ok \n" # -e开启转义
echo "it is a test"

echo -e "ok \c" # -e开启转义, -c 不换行
echo "it is a test"

echo "hello" >test.txt

echo $(date)

# printf
# printf 命令模仿 C library里的 printf() 程序
# printf 由 POSIX 标准所定义，因此使用 printf 的脚本比使用 echo 移植性好
# printf 使用引用文本或空格分隔的参数，外面可以在 printf 中使用格式化字符串，还可以制定字符串的宽度、左右对齐方式等
# 默认的 printf 不会像 echo 自动添加换行符，我们可以手动添加 \n
printf "%-10s %-8s %-4s\n" 姓名 性别 体重kg
printf "%-10s %-8s %-4.2f\n" 郭靖 男 66.1234
printf "%-10s %-8s %-4.2f\n" 杨过 男 48.6543
printf "%-10s %-8s %-4.2f\n" 郭芙 女 47.9876

# format-string为双引号
printf "%d %s\n" 1 "abc"
# 单引号与双引号效果一样
printf '%d %s\n' 1 "abc"
# 没有引号也可以输出
printf %s abcdef
# 格式只指定了一个参数，但多出的参数仍然会按照该格式输出，format-string 被重用
printf %s abc def
printf "%s\n" abc def
printf "%s %s %s\n" a b c d e f g h i j
# 如果没有 arguments，那么 %s 用NULL代替，%d 用 0 代替
printf "%s and %d \n"

# test: 用于检查某个条件是否成立，它可以进行数值、字符和文件三个方面的测试
num1=100
num2=100
if test $((num1)) -eq $((num2)); then
    echo '两个数相等！'
else
    echo '两个数不相等！'
fi
num1="ru1noob"
num2="runoob"
if test $num1 = $num2; then
    echo '两个字符串相等!'
else
    echo '两个字符串不相等!'
fi
if test -e /bin/bash; then
    echo '文件已存在!'
else
    echo '文件不存在!'
fi

# export
# export -p 列出所有环境变量
export name=wang
export -p

# let
# 用于执行一个或多个表达式，变量计算中不需要加上 $ 来表示变量。如果表达式中包含了空格或其他特殊字符，则必须引起来
a=1
let a++
echo ${a}


set参数介绍
set指令能设置所使用shell的执行方式，可依照不同的需求来做设置
　-a 　标示已修改的变量，以供输出至环境变量。
　-b 　使被中止的后台程序立刻回报执行状态。
　-C 　转向所产生的文件无法覆盖已存在的文件。
　-d 　Shell预设会用杂凑表记忆使用过的指令，以加速指令的执行。使用-d参数可取消。
　-e 　若指令传回值不等于0，则立即退出shell。　　
　-f　 　取消使用通配符。
　-h 　自动记录函数的所在位置。
　-H Shell 　可利用"!"加<指令编号>的方式来执行history中记录的指令。
　-k 　指令所给的参数都会被视为此指令的环境变量。
　-l 　记录for循环的变量名称。
　-m 　使用监视模式。
　-n 　只读取指令，而不实际执行。
　-p 　启动优先顺序模式。
　-P 　启动-P参数后，执行指令时，会以实际的文件或目录来取代符号连接。
　-t 　执行完随后的指令，即退出shell。
　-u 　当执行时使用到未定义过的变量，则显示错误信息。
　-v 　显示shell所读取的输入值。
　-x 　执行指令后，会先显示该指令及所下的参数。
　+<参数> 　取消某个set曾启动的参数。

回到顶部(go to top)
set -x介绍
用于脚本调试，在liunx脚本中可用set -x就可有详细的日志输出.免的老是要echo了

示例

1
2
3
4
#!/bin/bash
set -x
a=${1}
b=$
运行结果

1
2
3
bash a.sh 1 2
+ a=1
+ b=1
　　

回到顶部(go to top)
set -e介绍
-----------------------------------------------------------
#!/bin/bash
set -e
command 1
command 2
...
exit 0
----------------------------------------------------------
你写的每个脚本都应该在文件开头加上set -e,这句语句告诉bash如果任何语句的执行结果不是true则应该退出。这样的好处是防止错误像滚雪球般变大导致一个致命的错误，而这些错误本应该在之前就被处理掉。如果要增加可读性，可以使用set -o errexit，它的作用与set -e相同。

使用-e帮助你检查错误。如果你忘记检查（执行语句的结果），bash会帮你执行。不幸的是，你将无法检查$?，因为如果执行的语句不是返回0，bash将无法执行到检查的代码。你可以使用其他的结构：

command  
if [ "$?"-ne 0]; then   
    echo "command failed";   
    exit 1;   
fi   
could be replaced with
能够被代替为
command || { echo "command failed"; exit 1; }

或者

if ! command; then  
     echo "command failed";   
    exit 1;   
fi  
如果你有一个命令返回非0或者你对语句执行的结果不关心，那你可以使用command || true，或者你有一段很长的代码，你可以关闭错误检查（不使用set -e），但是我还是建议你保守地使用这个语句

# exit