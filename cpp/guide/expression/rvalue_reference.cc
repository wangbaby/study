#include <iostream>
#include <list>
#include <string>

int g_constructor_count = 0;
int g_copy_constructor_count = 0;
int g_destructor_count = 0;

struct A {
  A() { std::cout << "constructor:" << ++g_constructor_count << std::endl; }

  A(const A& a) {
    std::cout << "copy constructor:" << ++g_copy_constructor_count << std::endl;
  }

  ~A() { std::cout << "destructor:" << ++g_destructor_count << std::endl; }
};

A getA() { return A(); }

int main() {
  /**
   * 关闭函数返回值优化
   * g++ --std=c++11 -fno-elide-constructors -o build/a.out
   * cpp/guide/expression/prvalue_and_xvalue.cc
   *
   * constructor:1
   * copy constructor:2
   * destructor:1
   * copy constructor:2
   * destructor:2
   * destructor:3
   *
   * A a = getA();
   */

  /**
   * 开启返回值优化
   *
   * g++ --std=c++11  -o build/a.out cpp/guide/expression/prvalue_and_xvalue.cc
   *
   * constructor:1
   * destructor:1
   *
   * 返回值优化将会把临时对象优化掉，但这不是C++标准，是各编译器的优化规则
   *
   * A a = getA();
   */

  /**
   * 关闭函数返回值优化
   * g++ --std=c++11 -fno-elide-constructors -o build/a.out
   * cpp/guide/expression/prvalue_and_xvalue.cc
   *
   * constructor:1
   * copy constructor:2
   * destructor:1
   * destructor:2
   *
   * A&& a = getA();
   *
   * 通过右值引用，比之前少了一次拷贝构造和一次析构，原因在于右值引用绑定了右值，让临时右值的生命周期延长了
   *
   * 我们可以利用这个特点做一些性能优化，即避免临时对象的拷贝构造和析构
   * 事实上，在C++98/03中，通过常量左值引用也经常用来做性能优化。将上面的代码改成：
   * const A& a = GetA();
   * 输出的结果和右值引用一样，因为常量左值引用是一个“万能”的引用类型，可以接受左值、右值、常量左值和常量右值。
   * 需要注意的是普通的左值引用不能接受右值，比如这样的写法是不对的：
   * A& a = GetA();
   * 上面的代码会报一个编译错误，因为非常量左值引用只能接受左值
   */

  /**
   * std::move方法来将左值转换为右值，从而方便应用移动语义。move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存拷贝。
   * move实际上并不能移动任何东西，它唯一的功能是将一个左值强制转换为一个右值引用，使我们可以通过右值引用使用该值，以用于移动语义。
   * 这种move语义是很有用的，比如一个对象中有一些指针资源或者动态数组，在对象的赋值或者拷贝时就不需要拷贝这些资源了。
   */

  std::list<std::string> tokens;
  std::list<std::string> t = std::move(tokens);
  /**
   * 如果不用std::move，拷贝的代价很大，性能较低。使用move几乎没有任何代价，只是转换了资源的所有权。
   * 当一个对象内部有较大的堆内存或者动态数组时，很有必要写move语义的拷贝构造函数和赋值函数，避免无谓的深拷贝，以提高性能。
   * 事实上，C++中所有的容器都实现了move语义，方便我们实现性能优化。
   * 这里也要注意对move语义的误解，move只是转移了资源的控制权，本质上是将左值强制转换为右值引用，以用于move语义，避免含有资源的对象发生无谓的拷贝。
   * move对于拥有形如对内存、文件句柄等资源的成员的对象有效。
   * 如果是一些基本类型，比如int和char[10]数组等，如果使用move，仍然会发生拷贝（因为没有对应的移动构造函数），所以说move对于含资源的对象来说更有意义。
   */

  return EXIT_SUCCESS;
}
