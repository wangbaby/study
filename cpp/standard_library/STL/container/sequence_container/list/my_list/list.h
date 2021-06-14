#pragma once

#include "list_iterator.h"

// 双向队列 list
template <typename T>
struct list_node {
  typedef T value_type;
  typedef T& reference_type;
  typedef const T& const_reference_type;

  T value;
  list_node* prev;
  list_node* next;

  list_node(const T& value, list_node* prev = nullptr,
            list_node* next = nullptr)
      : value(value), prev(prev), next(next) {}
};

template <typename T>
class list {
  typedef T value_type;
  typedef list_iterator<node_type> iterator;
  typedef size_t size_type;

 public:
  list() = default;
  ~list() {
    while (head) {
      node_type* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push_front(const T& value) {
    head = new node_type(value, nullptr, head);
    if (head->next) head->next->prev = head;
  }

  void pop_front() {
    if (head) {
      node_type* temp = head;
      head->next->prev = nullptr;
      head = head->next;
      delete temp;
      temp = nullptr;
    }
  }

  void insert(iterator it, const T& v) {
    node_type* temp = it.pos;
    if (temp) {
      node_type* node = new node_type(v, temp, temp->next);
      temp->next = node;
      node->next->prev = node;
    }
  }

  void erase(iterator& it) {
    node_type* temp = it.pos;
    if (temp) {
      if (temp->prev) temp->prev->next = temp->next;
      if (temp->next) temp->next->prev = temp->prev;
      if (head == n) head = head->next;
      delete temp;
      temp = nullptr;
    }
  }

  iterator begin() { return iterator(head); }
  iterator end() { return iterator(); }

  bool empty() const { return head == nullptr; }

 private:
  typedef list_node<T> node_type;
  node_type* head = nullptr;
};