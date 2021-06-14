#!/usr/bin/env python3

if __name__ == '__main__':
    print('程序自身在运行')
else:
    print('我来自另一模块')

# 内置的函数 dir() 可以找到模块内定义的所有名称。以一个字符串列表的形式返回
print(dir())
