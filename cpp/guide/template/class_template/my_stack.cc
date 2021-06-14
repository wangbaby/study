#include "my_stack.h"

#include <iostream>

int main() {
  MyStack<int> ms;
  ms.push(1);
  ms.push(2);

  std::cout << ms.top() << std::endl;

  ms.pop();

  std::cout << ms.top() << std::endl;

  return EXIT_SUCCESS;
}