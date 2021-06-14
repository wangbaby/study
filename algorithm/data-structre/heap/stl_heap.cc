#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> numbers{2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0};
  make_heap(numbers.begin(), numbers.end()); //{12 10 3.5 6.5 8 2.5 1.5 6}

  // make_heap(numbers.begin(), numbers.end(), greater<double>());

  numbers.push_back(20.5);
  push_heap(numbers.begin(), numbers.end());

  pop_heap(numbers.begin(), numbers.end());
  numbers.pop_back();

  cout << boolalpha << is_heap(numbers.begin(), numbers.end()) << endl;

  sort_heap(numbers.begin(), numbers.end());

  return 0;
}