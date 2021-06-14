## 条件语句
#if
# if condition
# then
#     command1
#     command2
#     ...
#     commandN
# fi

# 一行
if echo "hello world" | grep -e hEllo; then echo true; else echo false; fi

# if else
# if condition
# then
#     command1
#     command2
#     ...
#     commandN
# else
#     command
# fi

# if else-if else
# if condition1
# then
#     command1
# elif condition2
# then
#     command2
# else
#     commandN
# fi

a=10
b=20
if (($a == $b)); then
   echo "a 等于 b"
elif [ $a -gt $b ]; then
   echo "a 大于 b"
elif [ $a -lt $b ]; then
   echo "a 小于 b"
else
   echo "没有符合的条件"
fi

# case
# case 值 in
# 模式1)
#     command1
#     command2
#     ...
#     commandN
#     ;;
# 模式2）
#     command1
#     command2
#     ...
#     commandN
#     ;;
# esac
echo '输入 1 到 4 之间的数字:'
echo '你输入的数字为:'
read aNum
case $aNum in
1)
   echo '你选择了 1'
   ;;
2)
   echo '你选择了 2'
   ;;
3)
   echo '你选择了 3'
   ;;
4)
   echo '你选择了 4'
   ;;
*)
   echo '你没有输入 1 到 4 之间的数字'
   ;;
esac

## 循环语句

# break continue

# for
# for var in item1 item2 ... itemN
# do
#     command1
#     command2
#     ...
#     commandN
# done

# 一行
# for var in item1 item2 .... itemN; do command1; command2... done;
for loop in 1 2 3 4 5; do
   echo ${loop}
done

for str in This is a string; do
   echo $str
done

for file in $(ls /etc); do
   echo $file
done

for i in $(seq 10); do
   echo ${i}
done

# 通常情况下 shell 变量调用需要加 $,但是 for 的 (()) 中不需要
for ((i = 1; i <= 5; i++)); do
   echo "这是第 $i 次调用"
done

# while
int=1
while (($int <= 5)); do
   echo $int
   let "int++"
done

echo '按下 <CTRL-D> 退出'
echo -n '输入你最喜欢的网站名: '
while read FILM; do
   echo "是的！$FILM 是一个好网站"
done

# 无限循环
# while :
# do
# command
# done

# while true:
# do
# command
# done

# for ((;;))

# until循环
# until condition
# do
#    command
# done

a=0
until [ ! $a -lt 10 ]; do
   echo $a
   a=$(expr $a + 1)
done
