template <typename T, typename N>
struct tuple {
  T value;
  N next;
  tuple(const T& v, const N& n) : value(v), next(n) {}
};

template <typename T, typename N>
tuple<T, N> push(const T& v, const N& n) {
  return tuple<T, N>(v, n);
}