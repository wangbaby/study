#!/usr/bin/env python3

arr = [1, 2, 3, 4]
it = iter(arr)
print(next(it))
print(next(it))
print(next(it))
print(next(it))

it = iter(arr)
for x in it:
    print(x)


class MyNumbers:
    def __iter__(self):
        self.a = 1
        return self

    def __next__(self):
        if self.a <= 20:
            x = self.a
            self.a += 1
            return x
        else:
            raise StopIteration


myclass = MyNumbers()
myiter = iter(myclass)

for x in myiter:
    print(x)
