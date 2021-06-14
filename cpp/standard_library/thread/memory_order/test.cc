#include <iostream>
#include <thread>

int a, b, c, y, z, w;

int func(int x) {
  // segment 1
  a = x + 32;
  b = x + a;
  c = a + b;

  // segment 2
  y = x + 54;
  z = y + 64;
  w = y + z;
}

int func2() {
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;

  std::cout << y << std::endl;
  std::cout << z << std::endl;
  std::cout << w << std::endl;
}

int main() {
  std::thread thd1(func, 100);
  std::thread thd2(func2);

  thd1.join();
  thd2.join();

  return 0;
}