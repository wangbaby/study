#include <iostream>
#include <string>

template <typename T, typename N>
class ListNode {
 public:
  T value;
  N* next;

  ListNode(const T& v, N* n) : value(v), next(n) {}
};

template <typename T, typename N>
ListNode<T, N>* Push(const T& v, N* n) {
  return new ListNode<T, N>(v, n);
}

template <typename T, typename N>
N* Pop(ListNode<T, N>* head) {
  N* next = head->next;
  delete head;
  return next;
}

int main() {
  {
      // typedef ListNode<int, void> node_type_1;
      // node_type_1* p0 = Push(1, (void*)(0));

      // typedef ListNode<char, node_type_1> node_type_2;
      // node_type_2* p1 = Push('c', p0);

      // typedef ListNode<std::string, node_type_2> node_type_3;
      // node_type_3* p2 = Push(std::string("123"), p1);

      // std::cout << p2->value << std::endl;

      // node_type_2* head = Pop(p2);
      // std::cout << head->value << std::endl;

      // Pop(Pop(head));
  }

  {
    auto p0 = Push(1, (void*)(0));
    auto p1 = Push(2, p0);
    auto p2 = Push(3, p1);

    std::cout << p2->value << std::endl;
    Pop(Pop(Pop(p2)));
  }

  return EXIT_SUCCESS;
}