括号不可少
编译时推导表达式的类型，并且不会真正计算表达式的值
j的推导结果表明：可以保留住表达式的引用以及const限定符，实际上对于一般的标记符表达式，decltype将精确推导出
    表达式定义本身的类型，不会像auto那样在某些情况下丢弃掉引用和cv限定符 p,
    pi的结果表明decltype可以跟auto一样，加上引用 / 指针，以及cv限定符 指针 /
        引用属于声明符declarators,
    在定义的时候是和变量名，而不是类型说明符type -
        specifiers相结合的，因此 const decltype(z)*p推导出来的是
            *p的类型，进而推导出p的类型 int x = 0;
decltype(x) y = 1;      // y->int
decltype(x + y) z = 0;  // z->int
const int& i = x;
decltype(i) j = y;          // j->const int &
const decltype(z)* p = &z;  // *p->const int, p->const int *
decltype(z)* pi = &z;       // *pi->int, pi->int *
decltype(pi)* pp = &pi;     // *pp->int *, pp->int**

推导规则
推导规则1，exp是标识符、类访问表达式，decltype（exp）和exp的类型一致。 推导规则2，exp是函数调用，decltype（exp）和返回值的类型一致
    其他情况，若exp是一个左值，则decltype（exp）是exp类型的左值引用，否则和exp类型一致

    class Foo {
 public:
  static const int Number = 0;
  int x;
};
int n = 0;
volatile const int& x = n;
decltype(n) a = n;            // a->int
decltype(x) b = n;            // b->volatile const int &
decltype(Foo::Number) c = 0;  // c->const int
Foo foo;
decltype(foo.x) d = 0;  // d->int, 类访问表达式

这里需要注意的是，c2是int而不是const int。这是因为函数返回的int是一个纯右值（prvalue）。对于纯右值而言，只有类类型可以携带cv限定符，此外则一般忽略掉cv限定 int&
func_int_r(void);
int&& func_int_rr(void);
int func_int(void);
const int& func_cint_r(void);
const int&& func_cint_rr(void);
const int func_cint(void);
const Foo func_cfoo(void);
int x = 0;
decltype(func_int_r()) a1 = x;     // a1 -> int &
decltype(func_int_rr()) b1 = 0;    // b1 -> int &&
decltype(func_int()) c1 = 0;       // c1 -> int
decltype(func_cint_r()) a2 = x;    // a2 -> const int &
decltype(func_cint_rr()) b2 = 0;   // b2 -> const int &&
decltype(func_cint()) c2 = 0;      // c2 -> int
decltype(func_cfoo()) ff = Foo();  // ff -> const Foo

a和b的结果：仅仅多加了一对括号，它们得到的类型却是不同的。 a的结果是很直接的，根据推导规则1，a的类型就是foo
        .x的定义类型。 b的结果并不适用于推导规则1和2。根据foo
        .x是一个左值，可知括号表达式也是一个左值。因此可以按照推导规则3，知道decltype的结果将是一个左值引用。 foo的定义是const
            Foo，所以foo.x是一个const
                int类型左值，因此decltype的推导结果是const int&。 同样，n +
    m返回一个右值，按照推导规则3，decltype的结果为int。 最后，n +=
    m返回一个左值，按照推导规则3，decltype的结果为int &。 struct Foo {
  int x;
};
const Foo foo = Foo();
decltype(foo.x) a = 0;    // a->int
decltype((foo.x)) b = a;  // b->const int &
int n = 0, m = 0;
decltype(n + m) c = 0;   // c->int
decltype(n += m) d = c;  // d->int &

decltype的应用多出现在泛型编程中 泛型类型定义可能存在问题的示例
#include <vector>
    template <class ContainerT>
    class Foo {
 private:
  ContainerT::iterator it_;  // 类型定义可能有问题
 public:
  void func(ContainerT& container) { it_ = container.begin(); }
  // ...
};
typedef const std::vector<int> container_t;
container_t arr;
Foo<container_t> foo;
foo.func(arr);
单独看类Foo中的it_成员定义，很难看出会有什么错误，但在使用时，若上下文要求传入一个const容器类型，编译器马上会弹出一大堆错误信息。 原因就在于，ContainerT::
        iterator并不能包括所有的迭代器类型， 要想解决这个问题，在C++ 98 /
    03下只能想办法把const类型的容器用模板特化单独处理，比如增加一个像下面这样的模板特化： template <
        class ContainerT>
    class Foo<const ContainerT> {
 private:
  ContainerT::const_iterator it_;

 public:
  void func(const ContainerT& container) { it_ = container.begin(); }
  // ...
};
这实在不能说是一个好的解决办法。若const类型的特化只是为了配合迭代器的类型限制，Foo的其他代码也不得不重新写一次。 有了decltype以后，就可以直接这样写： template <
    class ContainerT>
class Foo {
 private:
  decltype(ContainerT().begin()) it_;

 public:
  void func(ContainerT& container) { it_ = container.begin(); }
};
是不是舒服很多了？

decltype也经常用在通过变量表达式抽取变量类型上，如下面的这种用法： vector<int>
    v;
decltype(v)::value_type i = 0;
在冗长的代码中，人们往往只会关心变量本身，而并不关心它的具体类型。比如在上例中，只要知道v是一个容器就够了（可以提取value_type），
    后面的所有算法内容只需要出现v，而不需要出现像vector<int>
        这种精确的类型名称。这对理解一些变量类型复杂但操作统一的代码片段有很大好处。 实际上，标准库中有些类型都是通过decltype来定义的： typedef decltype(nullptr)
            nullptr_t;  // 通过编译器关键字nullptr定义类型nullptr_t
typedef decltype(sizeof(0)) size_t;
这种定义方法的好处是，从类型的定义过程上就可以看出来这个类型的含义

== == == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == 返回类型后置语法：auto 和 decltype的结合使用 == == == == == ==
    == == == == == == == == == == == == == == == == == == == == == == == == ==

    在泛型编程中，可能需要通过参数的运算来得到返回值的类型。 考虑下面这个场景： template <
        typename R, typename T, typename U>
    R add(T t, U u) {
  return t + u;
}
int a = 1;
float b = 2.0;
auto c = add<decltype(a + b)>(a, b);
我们并不关心a + b的类型是什么，因此，只需要通过decltype（a +
    b）直接得到返回值类型即可。 但是像上面这样使用十分不方便，因为外部其实并不知道参数之间应该如何运算，只有add函数才知道返回值应当如何推导。那么，在add函数的定义上能不能直接通过decltype拿到返回值呢？ template <
        typename T, typename U>
    decltype(t + u) add(T t, U u) {
  return t + u;
}
当然，直接像上面这样写是编译不过的。因为t、u在参数列表中，而C++ 的返回值是前置语法，在返回值定义的时候参数变量还不存在
    可行的写法如下： template <typename T, typename U>
    decltype(T() + U()) add(T t, U u) {
  return t + u;
}
考虑到T、U可能是没有无参构造函数的类，正确的写法应该是这样： template <
    typename T, typename U>
decltype((*(T*)0) + (*(U*)0)) add(T t, U u) {
  return t + u;
}
虽然成功地使用decltype完成了返回值的推导，但写法过于晦涩，会大大增加decltype在返回值类型推导上的使用难度并降低代码的可读性。

    因此，在C++ 11中增加了返回类型后置（trailing -
    return -type，又称跟踪返回类型）语法，将decltype和auto结合起来完成返回值类型的推导。 返回类型后置语法是通过auto和decltype结合起来使用的。上面的add函数，使用新的语法可以写成： template <
                class T, class U>
            auto add(T t, U u) -> decltype(t + u) {
  return t + u;
}
为了进一步说明这个语法，再看另一个例子：
int& foo(int& i);
float foo(float& f);
template <typename T>
auto func(T& val) -> decltype(foo(val)) {
  return foo(val);
}
如果说前一个例子中的add使用C++ 98 /
    03的返回值写法还勉强可以完成，那么这个例子对于C ++98 /
    03而言就是不可能完成的任务了。 在这个例子中，使用decltype结合返回值后置语法很容易推导出了foo（val）可能出现的返回值类型，并将其用到了func上。

    返回值类型后置语法，是为了解决函数返回值类型依赖于参数而导致难以确定返回值类型的问题。 有了这种语法以后，对返回值类型的推导就可以用清晰的方式（直接通过参数做运算）描述出来，而不需要像C++ 98 /
    03那样使用晦涩难懂的写法。

    ```c++
using size_t = decltype(sizeof(0));//sizeof(a)的返回值为size_t类型
using ptrdiff_t = decltype((int*)0 - (int*)0);
using nullptr_t = decltype(nullptr);
vector<int >vec;
typedef decltype(vec.begin()) vectype;
for (vectype i = vec.begin; i != vec.end(); i++)
{
//...
}

### 1.3 重用匿名类型

在C++中，我们有时候会遇上一些匿名类型，如:

```c++
struct 
{
    int d ;
    double b;
}anon_s;
```

而借助decltype，我们可以重新使用这个匿名的结构体：

```c++
decltype(anon_s) as ;//定义了一个上面匿名的结构体
```

### 1.4 泛型编程中结合auto，用于追踪函数的返回值类型

这也是decltype最大的用途了。

```c++
template <typename T>
auto multiply(T x, T y)->decltype(x*y)
{
   return x*y;
}
```

## 2.判别规则

对于decltype(e)而言，其判别结果受以下条件的影响：

如果e是一个没有带括号的标记符表达式或者类成员访问表达式，那么的decltype（e）就是e所命名的实体的类型。此外，如果e是一个被重载的函数，则会导致编译错误。
否则 ，假设e的类型是T，如果e是一个将亡值，那么decltype（e）为T&&
否则，假设e的类型是T，如果e是一个左值，那么decltype（e）为T&。
否则，假设e的类型是T，则decltype（e）为T。

标记符指的是除去关键字、字面量等编译器需要使用的标记之外的程序员自己定义的标记，而单个标记符对应的表达式即为标记符表达式。例如：
```c++
int arr[4]
```
则arr为一个标记符表达式，而arr[3]+0不是。

举例如下：

```c++
int i = 4;
int arr[5] = { 0 };
int *ptr = arr;
struct S{ double d; }s ;
void Overloaded(int);
void Overloaded(char);//重载的函数
int && RvalRef();
const bool Func(int);

//规则一：推导为其类型
decltype (arr) var1; //int 标记符表达式

decltype (ptr) var2;//int *  标记符表达式

decltype(s.d) var3;//doubel 成员访问表达式

//decltype(Overloaded) var4;//重载函数。编译错误。

//规则二：将亡值。推导为类型的右值引用。

decltype (RvalRef()) var5 = 1;

//规则三：左值，推导为类型的引用。

decltype ((i))var6 = i;     //int&

decltype (true ? i : i) var7 = i; //int&  条件表达式返回左值。

decltype (++i) var8 = i; //int&  ++i返回i的左值。

decltype(arr[5]) var9 = i;//int&. []操作返回左值

decltype(*ptr)var10 = i;//int& *操作返回左值

decltype("hello")var11 = "hello"; //const char(&)[9]  字符串字面常量为左值，且为const左值。


//规则四：以上都不是，则推导为本类型

decltype(1) var12;//const int

decltype(Func(1)) var13=true;//const bool

decltype(i++) var14 = i;//int i++返回右值