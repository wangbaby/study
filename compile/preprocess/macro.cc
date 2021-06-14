#include <iostream>
#include <string>

// 一旦宏被定义，它在其后的编译过程中有效，除非在某处被undef
#define ASPECT_RATIO 1.653

/**
 * 必须为宏中的实参加上小括号
 * 即使加上小括号，也可能发生不可思议的事情
   int a = 5, b = 0;
   min(++a, b);
   min(++a, b + 10);
 */
#define min(a, b) ((a) < (b) ? (a) : (b))

const int num = 1;
const std::string Author_Name("wangwang");

int main() {
  std::cout << ASPECT_RATIO << std::endl;

  std::cout << num << std::endl;
  std::cout << Author_Name << std::endl;

  return EXIT_SUCCESS;
}