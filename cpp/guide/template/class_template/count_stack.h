#include "my_stack.h"

// 类模板的基类必须是某个类型
// 如果是普通类以类模板实例为基类，需要为基类模板给定明确的模板参数值
template <typename T = int>
class CountStack<T> : class MyStack<T> {
  typedef MyStack<T> base_type;
  size_t size;

 public:
  CountStack() : base_type(), size(0) {}

  size_t size() const { return size; }

  void push(const T& v) {
    base_type::push(v);
    size++;
  }

  void pop() {
    if (size > 0) {
      base_type::pop();
      size--;
    }
  }
};