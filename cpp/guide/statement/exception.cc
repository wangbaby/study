#include <iostream>

int main() {
  try {
    /* code */
    throw std::runtime_error("error");
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}