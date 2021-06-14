#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> vi{5, 2, 3, 4, 1};
  //   std::sort(vi.begin(), vi.end());
  std::sort(std::execution::par, vi.begin(), vi.end());
  for (auto i : vi) std::cout << i << " ";
  std::cout << std::endl;

  return 0;
}