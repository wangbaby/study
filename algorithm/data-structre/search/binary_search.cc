/**
 * 二分查找法在1946年提出，第一个没有bug的方法在1962年才完成
 */

template <class T> int BinarySearch(T arr[], int n, T target) {
  int l = 0, r = n - 1; // [l, r] 范围内寻找 target
  while (l <= r) { // 当l == r 时， 区间还有元素，此时应该继续查找下去
    int mid = l + (r - l) / 2;
    if (arr[mid] == target)
      return mid;
    else if (arr[mid] < target) {
      l = mid + 1;
    } else
      r = mid - 1;
  }

  return -1;
}
