#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
 public:
  Vector(size_t s) : capacity(s) {
    arr = static_cast<T*>(malloc(sizeof(T) * capacity));
  }

  ~Vector() {
    if (arr) {
      free(arr);
      arr = nullptr;
    }
  }

  bool empty() const { return size == 0; }

  void push_back(const T& value) {
    if (size == capacity) {
      capacity *= 2;
      T* temp = static_cast<T*>(realloc(arr, sizeof(T) * capacity));
      if (temp)
        arr = temp;
      else {
        free(arr);
        arr = nullptr;
        throw std::runtime_error("out of memory");
      }
    }
    arr[size++] = value;
  }

  T& operator[](size_t s) {
    if (s >= size) throw std::out_of_range("out of range");

    return arr[s];
  }

  const T& operator[](size_t s) const {
    if (s >= size) throw std::out_of_range("out of range");

    return arr[s];
  }

  size_t get_size() const { return sizeof(T) * capacity; }

 private:
  T* arr = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};

template <>
class Vector<bool> {
 public:
  Vector(size_t s)
      : arr(static_cast<int*>(malloc(sizeof(int) * s))), size(0), capacity(s) {}
  ~Vector() {
    if (arr) free(arr);
  }

  bool operator[](size_t s) const {
    return (arr[s / seg_size] & (0x1 << (s % seg_size))) != 0;
  }

  void push_back(bool elem) {
    if (size == capacity * seg_size) {
      capacity *= 2;
      int* temp = static_cast<int*>(realloc(arr, sizeof(int) * capacity));
      if (temp)
        arr = temp;
      else {
        free(arr);
        arr = nullptr;
        throw std::runtime_error("out of memory");
      }
    }
    set(size++, elem);
  }

  size_t get_size() const { return sizeof(int) * capacity; }

 private:
  int* arr;
  size_t size;
  size_t capacity;
  const static size_t seg_size = 8;

  void set(size_t s, bool elem) {
    if (elem)
      arr[s / seg_size] |= (0x1 << (s % seg_size));
    else
      arr[s / seg_size] &= ~(0x1 << (s % seg_size));
  }
};

int main() {
  Vector<char> vc(2);
  Vector<bool> vb(2);
  for (int i = 0; i < 20; i++) {
    vc.push_back('a' + i);
    vb.push_back(i % 4 == 0);
  }

  std::cout << vc.get_size() << std::endl;
  std::cout << vb.get_size() << std::endl;

  return EXIT_SUCCESS;
}