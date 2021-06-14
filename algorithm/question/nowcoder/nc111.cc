#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
  /**
   * 最大数
   * @param nums int整型vector
   * @return string字符串
   */
  string solve(vector<int> &nums) {
    vector<string> ve;
    for (auto i : nums) {
      ve.push_back(to_string(i));
    }
    sort(ve.begin(), ve.end(),
         [](string a, string b) { return a + b > b + a; });
    //这个地方需要注意如果第一个字符串已经是0了，那么直接输出0
    if (ve[0] == "0")
      return "0";

    string res = "";
    for (int i = 0; i < ve.size(); i++) {
      res += ve[i];
    }
    return res;
  }
};

int main() {
  vector<int> nums{91, 92, 9, 90, 99, 100};
  cout << Solution().solve(nums) << endl;

  return 0;
}