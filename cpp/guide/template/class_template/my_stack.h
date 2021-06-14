#include <stdexcept>

template <typename T>
class MyStack;

template <typename T>
class ListNode {
 private:
  T value;
  ListNode* next;

  ListNode(const T& v, ListNode* n) : value(v), next(n) {}

  friend class MyStack<T>;
};

template <typename T = int>
class MyStack {
 private:
  typedef ListNode<T> node_type;
  node_type* head;
  MyStack(const MyStack&) = delete;
  MyStack& operator=(const MyStack&) = delete;

 public:
  MyStack() : head(nullptr){};
  ~MyStack() {}

  bool empty() const { return head == nullptr; }

  const T& top() {
    if (empty()) throw std::runtime_error("stack is empty");

    return head->value;
  }

  void push(const T& v) { head = new node_type(v, head); }

  void pop() {
    if (head) {
      node_type* temp = head;
      head = head->next;
      delete temp;
    }
  }
};