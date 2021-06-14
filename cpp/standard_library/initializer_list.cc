#include <initializer_list>
#include <iostream>

void test(std::initializer_list<int> il) {
  for (auto i : il) std::cout << i << " ";

  std::cout << std::endl;
}
int main() {
  test({1, 2, 3, 4});

  return 0;
}