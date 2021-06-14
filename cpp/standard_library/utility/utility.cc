#include <utility>

int main() {
  int num = 1;
  int&& r_num = std::move(num);
}