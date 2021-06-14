#!/usr/bin/env python3
import json

# Python 字典类型转换为 JSON 对象
data1 = {
    'no': 1,
    'name': 'Runoob',
    'url': 'http://www.runoob.com'
}

json_str = json.dumps(data1)
print("Python 原始数据：", repr(data1))
print("JSON 对象：", json_str)

# 将 JSON 对象转换为 Python 字python/standard_library/json_test.py典
data2 = json.loads(json_str)
print("data2['name']: ", data2['name'])
print("data2['url']: ", data2['url'])

with open('/home/ubuntu/study/myLinks.txt','r') as f:
    data = f.read()
    # data = data.replace("\'","\"")
    print(data)
    # data = '{"id":"002", "name":"顾明", "age":21}'
    # data1 = data.text
    # data1 = data.json()
    data1 = json.loads(data)
    print(type(data1))
