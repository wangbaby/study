#include <iostream>

using namespace std;

class Person {
 public:
  // 枚举常量
  typedef enum { Boy = 0, Girl } SexType;
};
int main() {
  {
    enum Color { Green, Blue };
    // enum Feeling { Excited, Blue };
  }
  { int a = Person::Boy; }
}