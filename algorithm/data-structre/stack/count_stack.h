#include "my_stack.h"

template <typename T>
class count_stack : public my_stack<T> {
  typedef my_stack<T> base_type;

  unsigned size;

 public:
  count_stack() : base_type(), size(0) {}

  void push(const T& v) {
    base_type::push(v);
    size++;
  }

  void pop() {
    base_type::pop();
    size--;
  }

  unsigned getSize() const { return size; }
};