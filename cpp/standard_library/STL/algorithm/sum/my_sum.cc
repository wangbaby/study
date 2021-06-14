template <typename T>
typename T::value_type sum(const T& c) {
  T::value_type sum(0);
  for (auto it = c.cbegin(); it != c.cend(); it++) sum += *it;
  return sum;
}

template <typename I>
typename I::value_type sum(I begin, I end) {
  I::value_type sum(0);
  for (I i = begin; i != end; i++) sum += *i;
  return sum;
}
// 统一数组和容器
template <typename I>
struct iterator_traits {
  typedef typename I::value_type value_type;
};

template <typename P>
struct iterator_traits<P*> {
  typedef P value_type;
};

template <typename I>
typename iterator_traits<I>::value_type sum(I begin, I end) {
  I::value_type sum(0);
  for (I i = begin; i != end; i++) sum += *i;
  return sum;
}