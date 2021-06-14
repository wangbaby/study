#include <iostream>

struct A {
  ~A() = delete;

  int num;
};

int main() {
  {
    // unevaluated expression
    int num = 1;
    std::cout << sizeof(++num) << std::endl;
    std::cout << num << std::endl;
  }

  {
    std::cout << sizeof(A()) << std::endl;
  }

  return EXIT_SUCCESS;
}