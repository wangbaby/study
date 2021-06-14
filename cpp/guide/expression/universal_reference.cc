#include <iostream>
#include <vector>

/**
 * univeral reference必须被初始化，它是左值还是右值引用取决于它的初始化，如果&&被一个左值初始化，它就是一个左值；如果它被一个右值初始化，它就是一个右值
 * 需要注意的是，只有当发生自动类型推断时（如函数模板的类型自动推导，或auto关键字），&&才是一个universal references
 */

template <typename T>
void f(T&& value) {
  std::cout << value << std::endl;
  value++;
  std::cout << value << std::endl;
}

template <typename T>
class Test {
 public:
  Test(Test&&) {
    // 已经定义了一个特定的类型， 没有类型推断 ,Test&& 是一个右值引用
  }
};

void f(Test<int>&& param) {
  // 已经定义了一个确定的类型， 没有类型推断，Test &&是一个右值引用
}

template <typename T>
void f(std::vector<T>&& param) {
  // 右值引用类型，因为在调用这个函数之前，这个vector<T>中的推断类型已经确定了，所以到调用f时没有类型推断了
}

template <typename T>
void f(const T&& param) {
  // 仅仅在T&&下发生，任何一点附加条件都会使之失效，而变成一个普通的右值引用。因此，上面的T&&在被const修饰之后就成为右值引用了
}

void PrintValue(int& i) { std::cout << "lvalue : " << i << std::endl; }
void PrintValue(int&& i) { std::cout << "rvalue : " << i << std::endl; }
void Forward(int&& i) { PrintValue(i); }
void Forward2(int&& i) { PrintValue(std::forward<int&&>(i)); }

int main() {
  f(10);

  int num = 10;
  f(num);
  std::cout << num << std::endl;

  // 由于存在T&&这种未定的引用类型，当它作为参数时，有可能被一个左值引用或者右值引用的参数初始化，这时经过类型推导的T&&类型，相比右值引用（&&）会发生类型的变化，这种变化被称为引用折叠
  // C++11中的引用折叠规则如下：
  // 1）所有的右值引用叠加到右值引用上仍然还是一个右值引用。
  // 2）所有的其他引用类型之间的叠加都将变成左值引用。

  //左值或者右值是独立于它的类型的，右值引用可能是左值也可能是右值
  int&& var1 = 1;  // var1 的类型是 int&&

  /**
   * var2存在类型推导，因此是一个universal references
   * var1的类型是一个右值引用类型，但var1本身是一个左值；var1是一个左值，根据引用折叠规则，auto为int&,var2是一个int&
   */
  var1 = 2;
  std::cout << var1 << std::endl;
  auto&& var2 = var1;
  var2 = 3;
  std::cout << var1 << std::endl;

  int w1 = 1, w2 = 2;
  auto&& v1 = w1;
  v1 = 100;
  std::cout << w1 << std::endl;

  std::cout << w2 << std::endl;
  decltype(w1)&& v2 = std::move(w2);

  {
    int i = 0;
    PrintValue(i);
    PrintValue(1);
    Forward(2);
  }
  /**
   * 将输出如下结果：
   * lvalue : 0
   * rvalue : 1
   * lvalue : 2
   * Forward函数接收的是一个右值，但在转发给PrintValue时又变成了左值，因为在Forward中调用PrintValue时，右值i变成了一个命名的对象，编译器会将其当作左值处理
   */

  /**
   * 因此，我们需要一种方法能按照参数原来的类型转发到另一个函数，这种转发被称为完美转发。
   * 所谓完美转发（Perfect Forwarding），是指在函数模板中，完全依照模板的参数的value category（即保持参数的左值、右值特征），将参数传递给函数模板中调用的另外一个函数。
   * C++ 11中提供了这样的一个函数std::forward 它是为转发而生的，不管参数是T&&这种未定的引用还是明确的左值引用或者右值引用，它会按照参数本来的类型转发。
   */

  {
    int i = 0;
    PrintValue(i);
    PrintValue(1);
    Forward2(2);
  }

  return EXIT_SUCCESS;
}

/**
 * 有了右值引用和移动语义，在设计和实现类时，对于需要动态申请大量资源的类，应该设计右值引用的拷贝构造函数和赋值函数，以提高应用程序的效率
 * 需要注意的是，我们一般在提供右值引用的构造函数的同时，也会提供常量左值引用的拷贝构造函数，以保证移动不成还可以使用拷贝构造。
 */