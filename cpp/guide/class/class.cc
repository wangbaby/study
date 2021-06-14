
#include <vector>

class Widget {
 public:
  ~Widget() { throw 1; }
};

int main() {
  // effective c++ item 8 : prevent exceptions from leaving destructors
  {
    // std::vector<Widget> vw(10, Widget());

    // try{
    //     Widget w;
    // }catch(...){

    // }

    Widget *pw = new Widget;
    try {
      delete pw;
    } catch (...) {
    }
  }

  return 0;
}
#include <iostream>

/**
 * 实现不能在堆上分配的类
 */
class A {
 public:
  A() {}
  ~A() {}

 private:
  void* operator new(size_t) {}
};

class B {
 public:
  B() {}
  ~B() {}

  void* operator new(size_t) = delete;
};

int main() {
  auto p = new A();
  auto q = new B();

  return 0;
}
/**
 * 不能被继承的类
 */
class Base final {};

class Derived : public Base {};
#include <iostream>

class Base {
public:
  Base() { func(); }

  virtual void func() { std::cout << "base func" << std::endl; }
};

class Derived : public Base {
public:
  Derived() {}

  void func() override { std::cout << "derived func" << std::endl; }
};

int main() {

  Base *p = new Derived;
  return 0;
}