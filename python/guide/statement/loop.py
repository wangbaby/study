#!/usr/bin/env python3

a, b = 0, 1
while b < 10:
    print(b, end=',')
    a, b = b, a + b

print()


n = 100
sum = 0
counter = 1
while counter <= n:
    sum = sum + counter
    counter += 1

print("1 到 %d 之和为: %d" % (n, sum))


count = 0
while count < 5:
    print(count, " 小于 5")
    count = count + 1
else:
    print(count, " 大于或等于 5")


# 类似if语句的语法，如果你的while循环体中只有一条语句，你可以将该语句与while写在同一行中


sites = ["Baidu", "Google", "Runoob", "Taobao"]
for site in sites:
    if site == "Runoob":
        print("菜鸟教程!")
        break
    print("循环数据 " + site)
else:
    print("没有循环数据!")
print("完成循环!")


for letter in 'Runoob':     # 第一个实例
    if letter == 'b':
        break
    print('当前字母为 :', letter)

var = 10                    # 第二个实例
while var > 0:
    print('当期变量值为 :', var)
    var = var - 1
    if var == 5:
        break

print("Good bye!")


for n in range(2, 10):
    for x in range(2, n):
        if n % x == 0:
            print(n, '等于', x, '*', n//x)
            break
    else:
        # 循环中没有找到元素
        print(n, ' 是质数')
