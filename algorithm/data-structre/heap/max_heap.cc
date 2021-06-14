#include <cassert>
#include <iostream>

template <class Item>
class MaxHeap {
 private:
  Item *data;
  int capacity;
  int count;

  void shift_up() {
    int pos = count;
    while (pos / 2 >= 1) {
      if (data[pos] > data[pos / 2]) {
        std::swap(data[pos], data[pos / 2]);
        pos /= 2;
      } else
        break;
    }
  }
  void shift_down(int start) {
    int pos = start;
    while (pos * 2 <= count) {
      int temp = pos * 2;
      if (pos * 2 + 1 <= count)
        temp = data[pos * 2] < data[pos * 2 + 1] ? pos * 2 + 1 : temp;
      if (data[pos] < data[temp]) {
        std::swap(data[pos], data[temp]);
      }
      pos = temp;
    }
  }

 public:
  MaxHeap(int capacity)
      : capacity(capacity), data(new Item[capacity + 1]), count(0) {}

  MaxHeap(Item *arr, int n)
      : capacity(n + 1), count(n), data(new Item[capacity]) {
    std::copy(arr, arr + n, data + 1);
    heapify();
  }

  int size() { return count; }

  bool empty() { return count; }

  void insert(Item item) {
    assert(capacity > count);

    data[++count] = item;
    shift_up();
  }

  Item extractMax() {
    auto res = data[1];
    data[1] = data[count--];
    shift_down(1);
    return res;
  }

  void heapify() {
    int pos = count / 2;
    while (pos >= 1) {
      shift_down(pos);
      pos--;
    }
  }
};

template <class T>
void PrintArray(T *arr, size_t n) {
  for (size_t i = 0; i < n; i++) std::cout << arr[i] << " ";

  std::cout << std::endl;
}

int main() {
  // 排序 [ 7,8,6,1,5,3,2,4]
  // 堆排序1 将数组元素逐个insert到堆中，然后依次extractMax
  int arr[] = {7, 8, 6, 1, 5, 3, 2, 4};
  int n = 8;
  MaxHeap<int> mh(8);
  for (auto i : arr) mh.insert(i);
  for (int i = n - 1; i >= 0; i--) arr[i] = mh.extractMax();
  PrintArray(arr, n);

  // 堆排序2
  // 增加构造函数，参数为数组和个数，初始化堆中data，然后调用heapify进行初始堆构造
  int arr2[] = {7, 8, 6, 1, 5, 3, 2, 4};
  int n2 = 8;

  MaxHeap<int> mh2(arr2, n2);
  for (int i = n2 - 1; i >= 0; i--) arr2[i] = mh2.extractMax();
  PrintArray(arr2, n2);
  // 比较：将n个元素插入到一个空堆中，复杂度为nlogn; heapify的过程，复杂度为n

  return 0;
}