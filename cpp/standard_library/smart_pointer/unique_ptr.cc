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
