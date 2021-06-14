#!/bin/bash

# 算术运算符
a=10
b=20

val=$(expr $a + $b)
echo "a + b : $val"

val=$(expr $a - $b)
echo "a - b : $val"

# 乘号(*)前边必须加反斜杠(\)才能实现乘法运算
val=$(expr $a \* $b)
echo "a * b : $val"

val=$(expr $b / $a)
echo "b / a : $val"

val=$(expr $b % $a)
echo "b % a : $val"

# 条件表达式要放在方括号之间，并且要有空格，例如: [$a==$b] 是错误的，必须写成 [ $a == $b ]
if [ $a == $b ]; then
   echo "a 等于 b"
fi
if [ $a != $b ]; then
   echo "a 不等于 b"
fi

# 关系运算符
# 关系运算符只支持数字，不支持字符串，除非字符串的值是数字
a=10
b=20

if [ $a -eq $b ]; then
   echo "$a -eq $b : a 等于 b"
else
   echo "$a -eq $b: a 不等于 b"
fi
if [ $a -ne $b ]; then
   echo "$a -ne $b: a 不等于 b"
else
   echo "$a -ne $b : a 等于 b"
fi
if [ $a -gt $b ]; then
   echo "$a -gt $b: a 大于 b"
else
   echo "$a -gt $b: a 不大于 b"
fi
if [ $a -lt $b ]; then
   echo "$a -lt $b: a 小于 b"
else
   echo "$a -lt $b: a 不小于 b"
fi
if [ $a -ge $b ]; then
   echo "$a -ge $b: a 大于或等于 b"
else
   echo "$a -ge $b: a 小于 b"
fi
if [ $a -le $b ]; then
   echo "$a -le $b: a 小于或等于 b"
else
   echo "$a -le $b: a 大于 b"
fi

# 布尔运算符
a=10
b=20

if [ $a != $b ]; then
   echo "$a != $b : a 不等于 b"
else
   echo "$a == $b: a 等于 b"
fi
if [ $a -lt 100 -a $b -gt 15 ]; then
   echo "$a 小于 100 且 $b 大于 15 : 返回 true"
else
   echo "$a 小于 100 且 $b 大于 15 : 返回 false"
fi
if [ $a -lt 100 -o $b -gt 100 ]; then
   echo "$a 小于 100 或 $b 大于 100 : 返回 true"
else
   echo "$a 小于 100 或 $b 大于 100 : 返回 false"
fi
if [ $a -lt 5 -o $b -gt 100 ]; then
   echo "$a 小于 5 或 $b 大于 100 : 返回 true"
else
   echo "$a 小于 5 或 $b 大于 100 : 返回 false"
fi

# 逻辑运算符
a=10
b=20

if [[ $a -lt 100 && $b -gt 100 ]]; then
   echo "返回 true"
else
   echo "返回 false"
fi

if [[ $a -lt 100 || $b -gt 100 ]]; then
   echo "返回 true"
else
   echo "返回 false"
fi

# 字符串运算符
a="abc"
b="efg"

if [ $a = $b ]; then
   echo "$a = $b : a 等于 b"
else
   echo "$a = $b: a 不等于 b"
fi
if [ $a != $b ]; then
   echo "$a != $b : a 不等于 b"
else
   echo "$a != $b: a 等于 b"
fi
if [ -z $a ]; then
   echo "-z $a : 字符串长度为 0"
else
   echo "-z $a : 字符串长度不为 0"
fi
if [ -n "$a" ]; then
   echo "-n $a : 字符串长度不为 0"
else
   echo "-n $a : 字符串长度为 0"
fi
if [ $a ]; then
   echo "$a : 字符串不为空"
else
   echo "$a : 字符串为空"
fi

# 文件测试运算符
file="README.md"
if [ -r $file ]; then
   echo "文件可读"
else
   echo "文件不可读"
fi
if [ -w $file ]; then
   echo "文件可写"
else
   echo "文件不可写"
fi
if [ -x $file ]; then
   echo "文件可执行"
else
   echo "文件不可执行"
fi
if [ -f $file ]; then
   echo "文件为普通文件"
else
   echo "文件为特殊文件"
fi
if [ -d $file ]; then
   echo "文件是个目录"
else
   echo "文件不是个目录"
fi
if [ -s $file ]; then
   echo "文件不为空"
else
   echo "文件为空"
fi
if [ -e $file ]; then
   echo "文件存在"
else
   echo "文件不存在"
fi

# (())
# 运算符拓展
# ((表达式1,表达式2…))
# 特点：
# 所有表达式可以像c语言一样，如：a++,b--等
# 所有变量可以不加入$符号前缀
# 双括号可以进行逻辑运算，四则运算, 扩展了for，while,if条件测试运算
# 支持多个表达式运算，各个表达式之间用“，”分开
# 双括号带$，将获得表达式值，赋值给左边变量

a=1
b=2
c=3
((a = a + 1))
echo $a
a=$((a + 1, b++, c++))
echo $a,$b,$c
a=1
b="ab"
echo $((a > 1 ? 8 : 9))
((b != "a")) && echo "err2"
((a < 2)) && echo "ok"

num=100
total=0
for ((i = 0; i <= num; i++)); do
   ((total += i))
done
echo ${total}
total=0
i=0
while ((i <= num)); do
   ((total += i, i++))
done
echo $total
if ((total >= 5050)); then
   echo "ok"
fi
