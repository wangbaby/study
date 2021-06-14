#include <iostream>

int main() {
  auto arr = new int[10]();
  arr[1] = 1;

  std::cout << arr[1] << std::endl;

  delete[] arr;

  return EXIT_SUCCESS;
}