#include <iostream>
#include <stack>

using namespace std;

int main() {
  std::stack<int> c1;
  c1.push(5);
  std::cout << c1.size() << '\n';

  std::stack<int> c2(c1);
  std::cout << c2.size() << '\n';

  std::deque<int> deq{3, 1, 4, 1, 5};
  std::stack<int> c3(deq);
  std::cout << c3.size() << '\n';

  swap(c1, c3);

  return 0;
}