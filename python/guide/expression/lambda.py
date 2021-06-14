#!/usr/bin/env python3

test = 1
func = lambda x, y : print(x, y, test)
func(3,5)
test = 10000
def fun():
    test = 2
    func(y=100, x=200)

fun()