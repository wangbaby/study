#!/usr/bin/env python3

'''
默认参数
'''

'''
不定长参数
'''
# 加了星号 * 的参数会以元组(tuple)的形式导入，存放所有未命名的变量参数


def func1(a, *args):
    print(a)
    print(args)
    for i in args:
        print(i)


func1(1, 2, 3, 4)

# 加了两个星号 ** 的参数会以字典的形式导入


def func2(a, **args):
    print(a)
    print(args)
    for i in args:
        print(i, args[i])
    for k, v in args.items():
        print(f'k = {k}, v = {v}')


func2(1, b=3, c=4)


# 使用*args/**kwargs调用函数
def test_args_kwargs(arg1, arg2, arg3):
    print("arg1:", arg1)
    print("arg2:", arg2)
    print("arg3:", arg3)


args = ('two', 2, 3)
test_args_kwargs(*args)

kwargs = {
    "arg1": 1,
    "arg2": 2,
    "arg3": 3
}
test_args_kwargs(**kwargs)

# 声明函数时，参数中星号 * 可以单独出现, 如果单独出现星号 * 后的参数必须用关键字传入


def func3(a, b, *, c):
    print(a, b, c)


func3(1, 2, c=100)
# immutable 不可变类型


def change(a):
    print(id(a))   # 指向的是同一个对象
    a = 10
    print(id(a))   # 一个新对象


a = 1
print(id(a))
change(a)


# 关键字参数
def printinfo(name, age):
    "打印任何传入的字符串"
    print("名字: ", name)
    print("年龄: ", age)
    return


printinfo(age=50, name="runoob")

# 默认参数


def printinfo(name, age=35):
    "打印任何传入的字符串"
    print("名字: ", name)
    print("年龄: ", age)
    return


printinfo(age=50, name="runoob")
print("------------------------")
printinfo(name="runoob")


# 不定长参数

def printinfo(arg1, *vartuple):
    "打印任何传入的参数"
    print("输出: ")
    print(arg1)
    for var in vartuple:
        print(var)
    return


printinfo(10)
printinfo(70, 60, 50)


def printinfo(arg1, **vardict):
    "打印任何传入的参数"
    print("输出: ")
    print(arg1)
    print(vardict)


# 调用printinfo 函数
printinfo(1, a=2, b=3)

# 如果单独出现星号 * 后的参数必须用关键字传入


"""
lambda 只是一个表达式，函数体比 def 简单很多。
lambda的主体是一个表达式，而不是一个代码块。仅仅能在lambda表达式中封装有限的逻辑进去。
lambda 函数拥有自己的命名空间，且不能访问自己参数列表之外或全局命名空间里的参数。
虽然lambda函数看起来只能写一行，却不等同于C或C++的内联函数，后者的目的是调用小函数时不占用栈内存从而增加运行效率。

sum = lambda a, b : a + b

"""

'''
Python3.8 新增了一个函数形参语法 / 用来指明函数形参必须使用指定位置参数，不能使用关键字参数的形式。
在以下的例子中，形参 a 和 b 必须使用指定位置参数，c 或 d 可以是位置形参或关键字形参，而 e 和 f 要求为关键字形参:
'''


def f(a, b, /, c, d, *, e, f):
    print(a, b, c, d, e, f)


"""

return

"""


def profile():
    name = "Danny"
    age = 30
    return (name, age)


profile_data = profile()
print(profile_data[0])


def profile():
    name = 'wang'
    age = 30
    return name, age


res = profile()
print(res)

print(type(res))


"""
在Python中当函数被定义时，默认参数只会运算一次，而不是每次被调用时都会重新运算。你应该永远不要定义可变类型的默认参数，除非你知道你正在做什么
"""


def func(num, target=[]):
    target.append(num)
    return target


print(func(1))
print(func(2))
print(func(3))
