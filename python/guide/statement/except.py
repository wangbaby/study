#!/usr/bin/env python3
while True:
    try:
        x = int(input("请输入一个数字: "))
        break
    except ValueError as e:
        print("您输入的不是数字，请再次尝试输入！")
        print('An error occurred. {}'.format(e.args[-1]))

'''
处理多个异常
try:
    file = open('test.txt', 'rb')
except (IOError, EOFError) as e:
    print("An error occurred. {}".format(e.args[-1]))

try:
    file = open('test.txt', 'rb')
except EOFError as e:
    print("An EOF error occurred.")
    # raise e
except IOError as e:
    print("An error occurred.")
    # raise e

try:
    file = open('test.txt', 'rb')
except Exception:
    # 打印一些异常日志，如果你想要的话
    raise

'''

try:
    file = open('test.txt', 'rb')
except IOError as e:
    print('An IOError occurred. {}'.format(e.args[-1]))
finally:
    print("This would be printed whether or not an exception occurred!")
