#include <iostream>
#include <numeric>
#include <string>
#include <vector>

template <class T>
void Print(const T &data) {
  for (const auto &i : data) std::cout << i << " ";

  std::cout << std::endl;
}

int main() {
  {
    // iota
    std::vector<int> vi(10);
    std::iota(vi.begin(), vi.end(), 1);
    Print(vi);
  }

  return 0;
}
