#!/usr/bin/env python3

# len
# 返回对象（字符、列表、元组等）长度或项目个数
str = "hello"
print(len(str))

# type
str = "hello"
print(type(str))
#!/usr/bin/env python3
from functools import reduce

# map
items = [1, 2, 3, 4]
res = list(map(lambda x: x**2, items))
print(res)


# filter
number_list = range(-5, 4)
res = list(filter(lambda x: x < 0, number_list))
print(res)

# reduce
res = reduce(lambda x, y: x * y, [1, 2, 3, 4])
print(res)

'''
自省
'''
# dir
# 运行dir()而不传入参数，那么它会返回当前作用域的所有名字
list = [1, 2, 3, 4]
print(dir(list))


# type
print(type(''))
# Output: <type 'str'>

print(type([]))
# Output: <type 'list'>

print(type({}))
# Output: <type 'dict'>

print(type(dict))
# Output: <type 'type'>

print(type(3))
# Output: <type 'int'>

# id
name = "Yasoob"
print(id(name))
