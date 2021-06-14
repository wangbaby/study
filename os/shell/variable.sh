#!/bin/bash

# 变量
# 等号两边不能直接接空白字符
# 变量内容若有空白字符可使用双引号或单引号将变量内容结合起来，但双引号内的特殊字符如 $ 等，可以保有原本的特性
# 需要借由其他额外的指令所提供的信息时，可以使用反引号`指令`或 $(指令)
# 使用变量时候加花括号是为了帮助解释器识别变量的边界.推荐给所有变量加上花括号，这是个好的编程习惯

a=test
echo ${a}
a="test $(uname -r)"
echo ${a}
a=$(cat /etc/issue)
echo ${a}
a="${a} hello $(ls)"
echo ${a}
a=1
b=2
echo $((a + b))
echo $(expr $a + $b)

# 只读变量
a="readonly"
readonly a
# a="update" # error: a is readonly

# 删除变量
# unset 不能删除只读命令
url="www.baidu.con"
echo ${url}
unset url
echo ${url}

# 变量类型
# 运行shell时，会同时存在三种变量：
# 1) 局部变量 局部变量在脚本或命令中定义，仅在当前shell实例中有效，其他shell启动的程序不能访问局部变量。
# 2) 环境变量 所有的程序，包括shell启动的程序，都能访问环境变量，有些程序需要环境变量来保证其正常运行。必要的时候shell脚本也可以定义环境变量。
# 3) shell变量 shell变量是由shell程序设置的特殊变量。shell变量中有一部分是环境变量，有一部分是局部变量，这些变量保证了shell的正常运行
echo ${PS1}   # 提示字符
echo ${$}     # 本次shell pid
echo ${?}     # 上次指令回传值
echo ${SHELL} # 查看当前shell
# BASH_SOURCE
# 数组变量BASH_SOURCE，该数组保存了bash的SOURCE调用层次
echo ${BASH_SOURCE[*]}
# http_proxy https_proxy all_proxy no_proxy
# 参数传递 eg: bash variable.sh 1 2 3
echo ${0}
echo ${1}
echo ${2}
echo ${3}
echo $# # $#: 传递到脚本的参数个数
echo $* # $*: 以一个单字符串显示所有向脚本传递的参数
# LD_LIBRARY_PATH 告诉动态装入器在尝试任何 /etc/ld.so.conf 路径以前先尝试使用特定目录中的共享库
# export LD_LIBRARY_PATH="/usr/lib/old:/opt/lib"

# 字符串
# 获取字符串长度
string="hello world"
echo ${#string}
# 截取
echo ${string:1:4}

# 数组
array=(1 2 3 4 5)
echo ${#array}
echo ${array[3]}
# 使用@ 或 * 可以获取数组中的所有元素
echo ${array[*]}
echo ${array[@]}
