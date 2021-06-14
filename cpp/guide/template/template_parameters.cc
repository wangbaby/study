// c++ 语言设计模板参数的用意在于，尽量将编译时可知的因素提取出来，从而进一步抽象代码

#include <iostream>
#include <stdexcept>
// 类型模板参数
// 非类型模板参数
// 模板型模板参数

// 整数模板参数
template <typename T, unsigned size>
class Array {
 private:
  T elems[size];

 public:
  T& operator[](unsigned i) {
    if (i >= size) throw std::out_of_range("out of range");

    return elems[i];
  }
};

// 函数指针模板参数
template <typename T, void (*f)(T&)>
void forEach(T arr[], unsigned size) {
  for (unsigned i = 0; i < size; i++) f(arr[i]);
}

template <typename T>
void print(T& v) {
  std::cout << v << " ";
}

template <typename T>
void inc(T& v) {
  v++;
}

// 指针/引用模板参数
// 只有指向全局变量以及外部变量(extern) 以及类静态变量的指针或者引用才可作为模板参数 -》 编译时可知

// 成员函数指针模板参数
class Template_1;

// c++ 允许在未完全声明的类上定义成员函数指针
typedef int (Template_1::*Func)(int);

class Template_1 {
 private:
  int value;

 public:
  Template_1(int v) : value(v) {}

  int add(int v) { return value + v; }
  int sub(int v) { return value - v; }
};

template <Func f>
int Handle(Template_1 tp, int v) {
  return (tp.*f)(v);
}

// 只有类模板能作为模板参数值，并且用class
template <typename T, template <typename TT0, typename TT1> class A>
class B {
  A<T, T> a;
};

int main() {
  {
    Array<int, 5> arr1;
    arr1[4] = 5;
    std::cout << arr1[4] << std::endl;
  }

  {
    int arr[]{1, 2, 3, 4};
    forEach<int, print>(arr, 4);
    std::cout << std::endl;

    forEach<int, inc>(arr, 4);

    forEach<int, print>(arr, 4);
    std::cout << std::endl;
  }

  {
    Template_1 tp1(0);
    // 声明具体成员函数指针值时必须使用&
    std::cout << Handle<&Template_1::add>(tp1, 1) << std::endl;
    std::cout << Handle<&Template_1::sub>(tp1, 1) << std::endl;
  }

  return EXIT_SUCCESS;
}