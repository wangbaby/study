再表示存储类型指示符
通过一个表达式在编译时确定待定义的变量类型，auto所修饰的变量必须被初始化，编译器需要通过初始化来确定auto所代表
        的类型，即必须要定义变量。 可以同指针 /
    引用结合起来使用，还可以带上CV限定符
        两面性，会带来代码可读性和维护性的严重下降 auto x =
    5;  // auto->int, 字面量5为const int 类型，const被丢弃
auto pi = new auto(1);      // auto->int*
const auto *v = &x, u = 6;  // 不能使编译器推导出现二义性, auto->int
static auto y = 0.0;        // auto->double
auto int r;                 // error,  auto 不再表示存储类型指示符
auto s;                     // error, 无法推导s的类型
         // ，auto不能代表实际的类型，只是一个类型声明的占位符

auto的推导规则 b的推导结果表明： auto不声明为指针，也可以推导出指针类型
        d的推导结果表明：
            当表达式是一个引用类型时，auto会把引用类型抛弃，直接推导成原始类型int
                f的推导结果表明：
                    当表达式带有const属性时，auto会把const属性抛弃掉，推导成non -
    const类型 g.h的推导结果表明 : 当auto和引用 /
        指针结合时， auto的推导结果将保留表达式的const属性 int x = 0;
auto *a = &x;        // auto->int, a->int *
auto b = &x;         // auto->int *, b->int *
auto &c = x;         // auto->int ,x ->int &
auto d = c;          // auto->int, d->int
const auto e = x;    // auto->int, e->const int
auto f = e;          // auto->int , f->int
const auto &g = x;   // auto->int, g->const auto &
auto &h = g;         // auto->const int, h->const int &
const auto *i = &x;  // auto->int, i ->const int *
auto *j = i;         // auto->const int, j->const int *

auto的限制 1.不能用于函数参数 void func(auto a = 1) {}
2.不能用于非静态成员变量,
    仅能用于推导static const的整型或者枚举成员 struct Foo {
  auto a = 1;
};
3. 不能用于声明数组 auto a[] = {1, 2, 3};
4. 不能用于模板参数 template <class T>
struct Bar {};
Bar<int> bar;
Bar<auto> bb = bar;

auto 使用 避免冗长的类型声明 std::map<double, double> resultMap;
for (auto it = resultMap.begin(); it != resultMap.end(); it++) {
  // do something
}
简化函数定义
泛型函数func对所有具有静态get方法的类型T,
    在得到get的结果后做统一的处理。若不使用auto,
    就不得不对func再增加一个
        模板参数，并在外部调用时手动指定get的返回值类型。 class Foo {
 public:
  static int get() { return 0; }
};

class Bar {
 public:
  static const char *get() { return "0"; }
};

template <class T>
void func() {
  auto res = T::get();
}

func<Foo>();
func<Bar>();