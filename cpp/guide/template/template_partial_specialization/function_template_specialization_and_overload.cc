//c++ 标准规定 函数模板也可以重载，即定义多个同名的但不等价的函数模板

// 只允许函数模板特例为完全特例

#include <iostream>
#include <string>

template <typename T>
void print(T v) {
  std::cout << v << std::endl;
}

// 模板特例
template <>
void print<char>(char v) {
  std::cout << '\'' << v << '\'' << std::endl;
}

template <>
void print(const char* v) {
  std::cout << '"' << v << '"' << std::endl;
}
// 模板特例，模板参数依赖推导
// c++标准规定在声明模板特例时可以将可推导出的模板参数省略

// 函数重载
void print(const std::string& v) {
  std::cout << "'''" << v << "'''" << std::endl;
}

void print(bool b) { std::cout << (b ? "true" : "false") << std::endl; }

// 函数模板重载
template <typename T>
void print(T* v) {
  std::cout << '*';
  print(*v);
}

/**
 * 编译器发现有同名函数模板时，会将生成的对应函数模板实例加入候选 + 同名函数
 * 如果函数调用明确要求一个模板实例时，即函数名后面跟<>, 则不将普通函数列入候选
 * 
 * 
 * 分辨重载 overload resolution
 * 
 * 1. 两候选函数中如果一方其形参列表各类型与调用实参列表各类型更匹配，则淘汰另一方
 *    参数类型匹配遵循的一般原则是：匹配度由高到低依次是等价类型 标准类型转换 自定义类型转换
 *    等价类型如: char[] -> char *       char* -> const char *
 *    标准类型转换如: int -> long
 *    自定义类型转换如: int -> 自定义类型A 
 * 2. 两函数如果其形参列表类型同等匹配实参列表类型时，若一方为函数模板实例而另一方为非模板函数，则取非模板函数而淘汰模板实例
 * 3. 两函数如果其形参列表类型同等匹配实参列表类型时，若两者均为函数模板实例，则取更特殊的一方而淘汰另一方
 */

/**
 * 编译器的条件判断逻辑
 * 当模板参数满足某一匹配条件时采用特例实现，否则采用通例实现
 */
// 编译器递归 静态递归
template <int i>
void print() {
  std::cout << i << " ";
  print<i - 1>();
}

template <>
void print<1>() {
  std::cout << 1 << std::endl;
}

int main() {
  print('c');
  print(std::string("hello"));
  print("123");
  print(true);

  print<100>();

  return 0;
}