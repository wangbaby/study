#pragma once

template <typename N>
class list_iterator {
  N* pos;

  template <typename N>
  friend class list;

 public:
  typedef typename N::value_type value_type;
  typedef typename N::reference_type reference_type;
  typedef typename N::const_reference_type const_reference_type;
  typedef list_iterator<N> self_type;

  list_iterator() : pos(nullptr) {}
  list_iterator(N* pos) : pos(pos) {}

  self_type& operator++() {
    if (pos) pos = pos->next;
    return *this;
  }

  bool operator!=(const self_type& right) const { return pos != right.pos; }

  bool operator==(const self_type& right) const { return pos == right.pos; }

  reference_type operator*() {
    if (pos) return pos->value;
  }
};