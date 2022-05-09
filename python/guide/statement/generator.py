#!/usr/bin/env python3

def func(n):
    a, b, counter = 0,1,0
    while True:
        if(counter > n):
            return
        yield a
        a, b = b, a + b
        counter+=1

f =  func(10)

for x in f:
    print(x)
