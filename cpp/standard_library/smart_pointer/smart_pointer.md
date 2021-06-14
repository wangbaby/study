C++11提供了3种智能指针：std：：shared_ptr、std：：unique_ptr和std：：weak_ptr，使用时需要引用头文件<memory>

*********************** shared_ptr ******************************
#include <iostream>
#include <memory>

using namespace std;

void DeleteIntPtr(int *p) { delete p; }

int main() {
  // 初始化
  {
    shared_ptr<int> p(new int(1));
    // shared_ptr<int> p = new int(1); error 不允许直接赋值

    shared_ptr<int> p1 = p;

    // 对于一个未初始化的智能指针，可以通过reset方法来初始化，当智能指针中有值的时候，调用reset会使引用计数减1
    shared_ptr<int> p2;
    p2.reset(new int(1));
    if (p2)
      cout << "p2 is not null" << endl;

    shared_ptr<int> p3 = make_shared<int>(1);
  }

  // 获取原始指针
  {
    shared_ptr<int> p(new int(1));
    int *op = p.get();
  }

  //指定删除器
  {
    shared_ptr<int> p1(new int, DeleteIntPtr);
    shared_ptr<int> p2(new int, [](int *p) { delete p; });

    // shared_ptr的默认删除器不支持数组对象
    shared_ptr<int> p3(new int[10], [](int *p) { delete[] p; });
    // 可以将std：：default_delete作为删除器。default_delete的内部是通过调用delete来实现功能的
    std::shared_ptr<int> p7(new int[10], std::default_delete<int[]>());
  }

  // 常见问题
  {
    // 1.不要用一个原始指针初始化多个shared_ptr

    // 2.不要在函数实参中创建shared_ptr。对于下面的用写法：
    // function (shared_ptr<int>(new int), g( ) ); // 有缺陷
    // 因为C++的函数参数的计算顺序在不同的编译器不同的调用约定下可能是不一样的
    // 所以，可能的过程是先new
    // int，然后调g（），如果恰好g（）发生异常，而shared_ptr<int>还没有创建，则int内存泄露了
    // 正确的写法应该是先创建智能指针

    // 3. 通过shared_from_this（）返回this指针。
    // 不要将this指针作为shared_ptr返回出来，因为this指针本质上是一个裸指针，因此这样可能会导致重复析构
    // struct A {
    //  shared_ptr<A> GetSelf() {
    //    return shared_ptr<A>(this); // don't do this!
    //  }
    //};
    // shared_ptr<A> sp1(new A);
    // shared_ptr<A> sp2 = sp1->GetSelf();
    // 在这个例子中，由于用同一个指针（this）构造了两个智能指针sp1和sp2，而它们之间是没有任何关系的
    // 在离开作用域之后this将会被构造的两个智能指针各自析构，导致重复析构的错误。

    // 4.要避免循环引用。智能指针最大的一个陷阱是循环引用，循环引用会导致内存泄露。下例是一个典型的循环引用的场景。
    // struct A;
    // struct B;
    // struct A {
    //     std::shared_ptr<B> bptr;
    //     ~A() { cout << "A is deleted!" << endl; }
    // };
    // struct B {
    //     std::shared_ptr<A> aptr;
    //     ~B() { cout << "B is deleted!" << endl; }
    // };
    // void TestPtr() {
    //     {
    //         std::shared_ptr<A> ap(new A);
    //         std::shared_ptr<B> bp(new B);
    //         ap->bptr = bp;
    //         bp->aptr = ap;
    //     }// Objects should be destroyed.
    // }
    // 测试结果是两个指针A和B都不会被删除，存在内存泄露。
    // 循环引用导致ap和bp的引用计数为2，在离开作用域之后，ap和bp的引用计数减为1，并不会减为0，导致两个指针都不会被析构，产生了内存泄露。
    // 解决办法是把A和B任何一个成员变量改为weak_ptr
  }
  return 0;
}

*********************** unique_ptr ******************************
#include <functional>
#include <memory>

using namespace std;

int main() {
  {
    // unique_ptr是一个独占型的智能指针，它不允许其他的智能指针共享其内部的指针，不允许通过赋值将一个unique_ptr赋值给另外一个unique_ptr
    // unique_ptr不允许复制，但可以通过函数返回给其他的unique_ptr，还可以通过std：：move来转移到其他的unique_ptr，这样它本身就不再拥有原来指针的所有权了
    // unique_ptr不像shared_ptr可以通过make_shared方法来创建智能指针，C++11目前还没有提供make_unique方法，在C++14中会提供和make_shared类似的make_unique来创建unique_ptr。

    unique_ptr<int> myPtr(new int);                // Okay
    unique_ptr<int> myOtherPtr = std::move(myPtr); // Okay,
    // unique_ptr<int> ptr = myPtr;
  }

  {
    // unique_ptr和shared_ptr相比，unique_ptr除了独占性这个特点之外，还可以指向一个数组，代码如下：
    std::unique_ptr<int[]> ptr(new int[10]);
    ptr[9] = 9; // 设置最后一个元素值为9
    // 而std：：shared_ptr<int[]>ptr（new int[10]）；是不合法的。
  }
  {
    // unique_ptr指定删除器和std：：shared_ptr是有差别的，比如下面的写法：
    std::shared_ptr<int> sptr(new int(1), [](int *p) { delete p; }); // 正确
    // std::unique_ptr<int> ptr(new int(1), [](int*p){delete p;});       // 错误
    // std：：unique_ptr指定删除器的时候需要确定删除器的类型，所以不能像shared_ptr那样直接指定删除器，可以这样写：
    std::unique_ptr<int, void (*)(int *)> uptr(new int(1),
                                               [](int *p) { delete p; });
    // 上面这种写法在lambda没有捕获变量的情况下是正确的，如果捕获了变量，则会编译报错：
    // std::unique_ptr<int, void(*)(int*)> ptr(new int(1), [&](int*p){delete
    // p;});
    // 这是因为lambda在没有捕获变量的情况下是可以直接转换为函数指针的，一旦捕获了就无法转换了。

    // 如果希望unique_ptr的删除器支持lambda，可以这样写：
    std::unique_ptr<int, std::function<void(int *)>> ptr(
        new int(1), [&](int *p) { delete p; });
    // 关于shared_ptr和unique_ptr的使用场景要根据实际应用需求来选
    // 如果希望只有一个智能指针管理资源或者管理数组就用unique_ptr，如果希望多个智能指针管理同一个资源就用shared_ptr。
  }

  return 0;
}
*********************** weak_ptr ******************************

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

*********************** 通过智能指针管理第三库分配的内存 ******************************

void *p = GetHandle()->create();
shared_ptr<void> sp(p, [this](void *p){
    GetHandle()->release();
});