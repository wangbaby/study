#include <iostream>
#include <memory>

using namespace std;
struct A : public std::enable_shared_from_this<A> {
  std::shared_ptr<A> GetSelf() { return shared_from_this(); }
  ~A() { cout << "A is deleted" << endl; }
};

struct B;
struct C {
  std::shared_ptr<B> bptr;
  ~C() { cout << "C is deleted!" << endl; }
};

struct B {
  std::weak_ptr<C> aptr; // 改为weak_ptr
  ~B() { cout << "B is deleted!" << endl; }
};

void TestPtr() {
  std::shared_ptr<C> ap(new C);
  std::shared_ptr<B> bp(new B);
  ap->bptr = bp;
  bp->aptr = ap;
}

int main() {
  // 基础用法
  {
    // 弱引用指针weak_ptr是用来监视shared_ptr的，不会使引用计数加1
    // 它不管理shared_ptr内部的指针，主要是为了监视shared_ptr的生命周期，更像是shared_ptr的一个助手。

    // weak_ptr没有重载操作符*和->，因为它不共享指针，不能操作资源，主要是为了通过shared_ptr获得资源的监测权
    // 它的构造不会增加引用计数，它的析构也不会减少引用计数，纯粹只是作为一个旁观者来监视shared_ptr中管理的资源是否存在。

    // weak_ptr还可以用来返回this指针和解决循环引用的问题。

    shared_ptr<int> sp(new int(10));
    weak_ptr<int> wp(sp);

    //通过use_count（）方法来获得当前观测资源的引用计数，代码如下：
    cout << wp.use_count() << endl; // 结果将输出1

    // 通过expired（）方法来判断所观测的资源是否已经被释放，代码如下：
    if (wp.expired())
      std::cout << "weak_ptr无效，所监视的智能指针已被释放\n";
    else
      std::cout << "weak_ptr有效\n";
    // 结果将输出:weak_ptr有效

    // 通过lock方法来获取所监视的shared_ptr
  }

  // 返回this
  {
    // 不能直接将this指针返回为shared_ptr，需要通过派生std：：enable_shared_from_this类，并通过其方法shared_from_this来返回智能指针，
    // 原因是std：：enable_shared_from_this类中有一个weak_ptr，这个weak_ptr用来观测this智能指针，调用shared_from_this（）方法时，会调用内部这个weak_ptr的lock（）方法，将所观测的shared_ptr返回

    std::shared_ptr<A> spy(new A);
    std::shared_ptr<A> p = spy->GetSelf(); // OK
    // 在外面创建A对象的智能指针和通过该对象返回this的智能指针都是安全的，因为shared_from_this（）是内部的weak_ptr调用lock（）方法之后返回的智能指针，在离开作用域之后，spy的引用计数减为0，A对象会被析构，不会出现A对象被析构两次的问题。
    // 需要注意的是，获取自身智能指针的函数仅在shared_ptr<T>的构造函数被调用之后才能使用，因为enable_shared_from_this内部的weak_ptr只有通过shared_ptr才能构造。
  }

  // weak_ptr解决循环引用问题
  {
    TestPtr();
    // 执行bp->aptr=ap；时，由于aptr是weak_ptr，它并不会增加引用计数，所以ap的引用计数仍然会是1，在离开作用域之后，ap的引用计数会减为0，A指针会被析构
    // 析构后其内部的bptr的引用计数会减为1，然后在离开作用域后bp引用计数又从1减为0，B对象也将被析构，不会发生内存泄露。
  }
}
