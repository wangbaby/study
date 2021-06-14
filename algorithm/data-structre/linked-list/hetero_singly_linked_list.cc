#include <iostream>
#include <string>

template <typename T, typename N>
struct herto_node {
  T value;
  N* next;
  herto_node(const T& v, N* n) : value(v), next(n) {}
};

template <typename T, typename N>
herto_node<T, N>* push(const T& v, N* n) {
  return new herto_node(v, n);
}

template <typename T, typename N>
N* pop(herto_node<T, N>* head) {
  N* next = head->next;
  delete head;
  return next;
}

int main() {
  typedef herto_node<int, void> node_0;
  typedef herto_node<char, node_0> node_1;
  typedef herto_node<std::string, node_1> node_2;

  auto* p2 = push(std::string("awesome"), push('a', push(1, (void*)0)));

  std::cout << p2->value << " " << p2->next->value << " "
            << p2->next->next->value << std::endl;

  pop(pop(pop(p2)));

  return 0;
}