// 集合 set
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  vector<int> vi{1, 2, 3, 4, 5, 6};
  set<int> si(vi.cbegin(), vi.cend());

  for(auto i : si){
    cout << i << " ";
  }
  cout << endl;

  return 0;
}