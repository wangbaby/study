#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string s;
  while (cin >> s) {
    int n = s.size();
    vector<string> vs;
    int pos = 0;
    while (n >= 8) {
      vs.push_back(s.substr(pos, 8));
      n -= 8;
      pos += 8;
    }

    if (n < 8 && n > 0) {
      string temp = s.substr(pos, n);
      temp.append(8 - n, '0');
      vs.push_back(temp);
    }

    for (auto it = vs.begin(); it != vs.end(); it++)
      cout << *it << endl;
  }

  return 0;
}