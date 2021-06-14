#!/usr/bin/env python3

a, b = "Hello", "Python"

print("a + b 输出结果：", a + b)
print("a * 2 输出结果：", a * 2)
print("a[1] 输出结果：", a[1])
print("a[1:4] 输出结果：", a[1:4])

if("H" in a):
    print("H 在变量 a 中")
else:
    print("H 不在变量 a 中")

if("M" not in a):
    print("M 不在变量 a 中")
else:
    print("M 在变量 a 中")

print(r'\n')
print(R'\n')


# 格式化字符串
print("我叫 %s 今年 %d 岁!" % ('小明', 10))

# 三引号
para_str = """这是一个多行字符串的实例
多行字符串可以使用制表符
TAB ( \t )。
也可以使用换行符 [ \n ]。
"""
print(para_str)


# f-string
x = 1
print((f'{x + 1}'))


# upper

str = "hello"
print(str.upper())
