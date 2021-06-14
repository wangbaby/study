# 02 prefer consts enums inlines to #defines

宁可以编译器替代预处理器

#define 不被视为语言的一部分，那正是它的问题所在。

```
#define ASPECT_RATIO 1.653
```

记号名称 ASPECT_RATIO 也许从未被编译器看见；也许在编译器开始处理源码之前它就被预处理器移走了。于是记号名称 ASPECT_RATIO 有可能没进入 symbol table.

于是当你应用此常量但获得一个编译错误信息时，可能会带来困惑，因为这个错误信息也许会提到 1.653 而不是 ASPECT_RATIO。

如果 ASPECT_RATIO 被定义在一个非你所写的头文件内，你肯定会对 1.653 以及它来自何处毫无概念，于是你将因为追踪它而浪费时间。

```
// 解决之道：以常量替代宏
const double Aspect_Ratio = 1.653;
```

此外对于浮点常量而言，使用常量可能比使用#define 导致较小量的码，因为预处理器盲目地将宏名称 ASPECT_RATIO 替换为 1.653 可能导致目标码出现多份 1.653，若改用常量 Aspect_Ratio 绝不会出现此种情况。

template inline 函数获得宏带来的效率以及一般函数的可预料行为和类型安全性

```
template <typename T>
inline T min(const T& a, const T& b){
  return a < b ? a : b;
}
```
