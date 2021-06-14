/**
 * sort 稳定排序 O(nlogn) GNU实现为merge sort
 * sort()
 * sort(cmp)
 * 
 * splice: 将另一链表的数据加入本链表
 * splice(i, x) 将链表x的所有数据添加到迭代器i之后
 * splice(i, x, j) 将x的迭代器j 之后的所有数据移入到迭代器i之前
 * 
 * push_front()
 * pop_front()
 * 
 * remove(v)
 * remove_if(cond)
 * 
 * unique 删除与前一数据等价的数据
 * unique(pred)
 * 
 * merge(x) 合并有序列表
 * merge(x, comp) 
 * 
 * reverse()
 */

#include <iostream>
#include <list>

template <typename T>
void print(const T& C) {
  for (const auto& i : C) std::cout << i << " ";
  std::cout << std::endl;
}

int main() {
  std::list<int> li{1, 3, 4, 2, 5};

  print(li);
  li.sort();
  print(li);

  std::list<int> li2{10, 12, 14, 16};
  li.splice(li.begin(), li2);
  print(li);

  li.remove(12);
  print(li);

  li.reverse();
  print(li);

  return EXIT_SUCCESS;
}