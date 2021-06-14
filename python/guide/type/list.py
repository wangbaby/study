#!/usr/bin/env python3

list = ['red', 'green', 'blue', 'yellow', 'white', 'black']
print(list[0])
print(list[1])
print(list[2])

nums = [10, 20, 30, 40, 50, 60, 70, 80, 90]
print(nums[0:4])

list = ['Google', 'Runoob', 1997, 2000]

print("第三个元素为 : ", list[2])

list[2] = 2001
print("更新后的第三个元素为 : ", list[2])

list1 = ['Google', 'Runoob', 'Taobao']
list1.append('Baidu')
print("更新后的列表 : ", list1)

list1[len(list1):] = ['byte dance']
print("更新后的列表 : ", list1)

list = ['Google', 'Runoob', 1997, 2000]
print("原始列表 : ", list)
del list[2]
print("删除第三个元素 : ", list)

# 列表推导式
