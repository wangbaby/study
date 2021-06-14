#include <iostream>

/**
 * enum hack
 * 
 * enum hack的行为某方面来说有点像#define而不像const,有时候这正是你想要的；例如取一个const的地址是合法的，但是取一个enum或者#define的地址不合法
 * enum hack是template metaprogramming的基础
 */
class Widget {
  enum { Count = 10 };

  int arr[Count];
};

enum Fruit { Apple, Banana, Orange };

int main() {
  std::cout << Apple << " " << Banana << " " << Orange << std::endl;

  Fruit f1 = Banana;
  std::cout << f1 << std::endl;

  return EXIT_SUCCESS;
}
