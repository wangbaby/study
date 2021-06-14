#include <iostream>
// 专注于数据存取方式，以及数据之间的关联方式

// struct ListNode {
//   int val;
//   ListNode *next;
//   ListNode(int x = 0, ListNode *next = nullptr) : val(x), next(next) {}
// };

// 在一个类模板内出现的自身模板名，等价于该模板被调用时所生成的实例
// 没有模板参数自动推导，因为使用类不需要参数
template <typename T = int>
struct ListNode {
  T val;
  ListNode *next;
  ListNode(T x = 0, ListNode *next = nullptr) : val(x), next(next) {}
};

// 成员函数模板
class Template_1 {
 private:
  int value;

 public:
  template <typename T>
  void set(const T &v) {
    value = static_cast<int>(v);
  }

  template <typename T>
  T get() {
    return static_cast<T>(value);
  }
};

// 类模板的成员函数还可以有额外的模板参数
template <typename T0>
class Template_2 {
 private:
  T0 value;

 public:
  template <typename T1>
  void set(const T1 &v) {
    value = static_cast<T0>(v);
  }

  template <typename T1>
  T1 get();
};

template <typename T0>
template <typename T1>
T1 Template_2<T0>::get() {
  return static_cast<T1>(value);
}

// 声明友元类模板和友元函数模板
template <typename T>
class FBI {};

class Citizen {
  friend class FBI;

  template <typename T>
  friend T duty(const Citizen &) {}
};

int main() {
  ListNode node_1;
  std::cout << node_1.val << std::endl;
  ListNode node_2(2);
  std::cout << node_2.val << std::endl;
  ListNode node_3(3, &node_2);
  std::cout << node_3.val << std::endl;

  return EXIT_SUCCESS;
}