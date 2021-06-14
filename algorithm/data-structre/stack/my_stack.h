#include <stdexcept>

template <typename T>
class my_stack;

template <typename T>
class list_node {
  T value;
  list_node* next;

  list_node(const T& v, list_node* n) : value(v), next(n) {}

  friend class my_stack<T>;
};

template <typename T = int>
class my_stack {
  using node_type = list_node<T>;

  node_type* head = nullptr;
  my_stack(const my_stack&) = delete;
  my_stack& operate = (const my_stack&) = delete;

 public:
  my_stack() {}
  ~my_stack() {
    while (!empty()) pop();
  }

  bool empty() { return !head; }

  const T& top() const throw(std::runtime_error) {
    if (empty()) throw std::runtime_error("stack is empty");

    return head->value;
  }

  void push(const T& v) { head = new node_type(v, head); }

  void pop();
};

template <typename T>
void my_stack<T>::pop() {
  if (head) {
    node_type* temp = head;
    head = head->next;
    delete temp;
  }
}