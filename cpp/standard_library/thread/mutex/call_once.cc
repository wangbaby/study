#include <iostream>
#include <mutex>
#include <thread>

std::once_flag flg;

void func() {
  std::call_once(flg, [] { std::cout << "call once" << std::endl; });
}

int main() {
  std::thread t1(func);
  std::thread t2(func);
  std::thread t3(func);

  t1.join();
  t2.join();
  t3.join();

  return EXIT_SUCCESS;
}