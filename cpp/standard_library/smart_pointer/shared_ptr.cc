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
    if (p2) cout << "p2 is not null" << endl;

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