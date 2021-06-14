
#include <cassert>
#include <iostream>

template <class Item> class MaxHeap {
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

template <class T> void PrintArray(T *arr, size_t n) {
  for (size_t i = 0; i < n; i++)
    std::cout << arr[i] << " ";

  std::cout << std::endl;
}

int main() {
  // 排序 [ 7,8,6,1,5,3,2,4]
  // 堆排序1 将数组元素逐个insert到堆中，然后依次extractMax
  int arr[] = {7, 8, 6, 1, 5, 3, 2, 4};
  int n = 8;
  MaxHeap<int> mh(8);
  for (auto i : arr)
    mh.insert(i);
  for (int i = n - 1; i >= 0; i--)
    arr[i] = mh.extractMax();
  PrintArray(arr, n);

  // 堆排序2
  // 增加构造函数，参数为数组和个数，初始化堆中data，然后调用heapify进行初始堆构造
  int arr2[] = {7, 8, 6, 1, 5, 3, 2, 4};
  int n2 = 8;

  MaxHeap<int> mh2(arr2, n2);
  for (int i = n2 - 1; i >= 0; i--)
    arr2[i] = mh2.extractMax();
  PrintArray(arr2, n2);
  // 比较：将n个元素插入到一个空堆中，复杂度为nlogn; heapify的过程，复杂度为n

  return 0;
}


创建堆

用来创建堆的函数定义在头文件 <algorithm> 中。make_heap() 对随机访问迭代器指定的一段元素重新排列，生成一个堆。默认使用的是 < 运算符，可以生成一个大顶堆。
vector<double> numbers{2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0};
make_heap(numbers.begin(), numbers.end()); //{12 10 3.5 6.5 8 2.5 1.5 6}
调用 make_heap() 后，vector 中的元素如下所示




既然如此，为什么 STL 有 priority_queue (它是一个堆)，却还需要创建堆，特别是还需要将堆作为优先级队列？

这是因为 priority_queue 可以提供堆没有的优势，它可以自动保持元素的顺序；但我们不能打乱 priority_queue 的有序状态，因为除了第一个元素，我们无法直接访问它的其他元素。如果需要的是一个优先级队列，这一点非常有用。

从另一方面来说，使用 make_heap() 创建的堆可以提供一些 priority_queue 没有的优势：
可以访问堆中的任意元素，而不限于最大的元素，因为元素被存储在一个容器中，就像是我们自己的 vector。这也提供了偶然破坏元素顺序的可能，但是总可以调用 make_heap() 来还原堆。
可以在任何提供随机访问迭代器的序列容器中创建堆。这些序列容器包括普通数组、string 对象、自定义容器。这意味着无论什么时候需要，都可以用这些序列容器的元素创建堆，必要时，可以反复创建。甚至还可以为元素的子集创建堆。

这里有另一个版本的 make_heap()，它有第 3 个参数，可以用来指定一个比较函数用于堆的排序。通过定义一个大于运算符函数，可以生成一个小顶堆。这里可以使用 functional 中的断言。例如：
 make_heap(numbers.begin(), numbers.end(), greater<double>());
可以将模板类型参数指定为 greater。

堆操作

添加元素

push_back() 会在序列末尾添加元素，然后使用 push_heap() 恢复堆的排序。通过调用 push_heap()，释放了一个信号，指出我们向堆中添加了一个元素，这可能会导致堆排序的混乱。push_heap() 会因此认为最后一个元素是新元素，为了保持堆结构，会重新排列序列。

numbers.push_back(20.5);
push_heap(numbers.begin(), numbers.end());

当然，也可以用自己的比较函数来创建堆，但是必须和 push_heap() 使用相同的比较函数

删除元素

pop_heap() 函数将第一个元素移到最后，并保证剩下的元素仍然是一个堆。然后就可以使用 vector 的成员函数 pop_back() 移除最后一个元素。如果 make_heap() 中用的是自己的比较函数，那么 pop_heap() 的第 3 个参数也需要是这个函数。

pop_heap(numbers.begin(), numbers.end());
numbers.pop_back();


检查是否是堆

因为可能会打乱容器中的堆，所以 STL 提供了一个检查序列是否仍然是堆的方法：is_heap

cout << boolalpha << is_heap(numbers.begin(), numbers.end()) << endl;

如果元素段是堆，那么 is_heap() 会返回 true。这里是用默认的比较断言 less<> 来检查元素顺序。如果这里使用的是用 greater<> 创建的堆，就会产生错误的结果。


检查元素中是否有部分元素为堆

is_heap_until() 函数返回一个迭代器，指向第一个不在堆内的元素。


排序

STL 提供的最后一个操作是 sort_heap()，它会将元素段作为堆来排序。如果元素段不是堆，程序会在运行时崩溃。
第 2 个版本的 sort_heap() 有第 3 个参数，可以指定一个用来创建堆的断言。如果用断言 greater() 来创建堆，会生成一个小顶堆，对它进行排序会生成一个降序序列。


定义一个堆：这个堆是一个完全二叉树，每个节点与其子节点位置相对。父节点总是大于或等于子节点，这种情况下被叫作大顶堆，或者父节点总是小于或等于子节点，这种情况下叫作小顶堆。注意，给定父节点的子节点不一定按顺序排列。
