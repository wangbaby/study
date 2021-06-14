#include <iostream>
#include <string>

/**
 * 类中的静态变量应由用户使用类外的类名和范围解析运算符显式初始化
 * 
 * 允许使用对象和'.'来调用静态成员函数,但建议使用类名和范围解析运算符调用静态成员
 * 静态成员函数仅访问静态数据成员或其他静态成员函数，它们无法访问类的非静态数据成员或成员函数。
 */

class Widget {
 public:
  static const int num_1 = 1;  // 声明式非定义式
  int arr_1[num_1];

  static int num_2;

  static const int num_3;
  // int arr_3[num_3]; // error

  static void PrintMsg() { std::cout << msg << std::endl; }

 private:
  static std::string msg;
};

// 只要不取num_1地址，则无需此定义式；并且定义时不可以再设初值
const int Widget::num_1;

int Widget::num_2 = 2;
const int Widget::num_3 = 3;
std::string Widget::msg = "hello world";

int main() {
  std::cout << &(Widget::num_1) << std::endl;

  std::cout << Widget::num_1 << " " << Widget::num_2 << std::endl;

  Widget::PrintMsg();

  return 0;
}