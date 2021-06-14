#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int parttion(vector<int> &nums, int l, int r) {
  int pos = rand() % (r - l + 1) + l;
  swap(nums[pos], nums[l]);

  pos = l;
  for (int i = l + 1; i <= r; i++) {
    if (nums[i] < nums[l]) {
      swap(nums[i], nums[pos + 1]);
      pos++;
    }
  }

  swap(nums[pos], nums[l]);

  return pos;
}

void quicksort_(vector<int> &nums, int l, int r) {
  if (l > r)
    return;
  int pos = parttion(nums, l, r);
  quicksort_(nums, l, pos - 1);
  quicksort_(nums, pos + 1, r);
}

void quicksort(vector<int> &nums) {
  srand(time(NULL));
  quicksort_(nums, 0, nums.size() - 1);
}

void print_vec(const vector<int> &nums) {
  for (auto i : nums) {
    cout << i << " ";
  }

  cout << endl;
}
int main() {
  vector<int> nums{3, 4, 2, 1, 5};
  quicksort(nums);
  print_vec(nums);

  return 0;
}