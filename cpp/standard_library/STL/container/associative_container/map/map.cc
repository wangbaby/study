// 映射 map
#include <iostream>
#include <map>

using namespace std;

int main() {
  map<int, string> mp;
  auto res = mp.insert({1, "A"});

  if (res.second) {
    cout << (*(res.first)).first << endl;
  }

  auto it2 = mp.insert({4, "D"});
  auto it3 = mp.insert({5, "E"});
  auto it4 = mp.insert({2, "B"});
  auto it5 = mp.insert({3, "C"});


  return 0;
}