#include <iostream>
#include <mutex>
#include <thread>

int g_i = 0;
std::mutex g_i_mutex;

void increment() {
  // RAII-style
  std::lock_guard<std::mutex> lock(g_i_mutex);
  g_i++;

  std::cout << std::this_thread::get_id() << " : g_i = " << g_i << std::endl;
}

int main() {
  std::thread t1(increment);
  std::thread t2(increment);
  std::thread t3(increment);

  t1.join();
  t2.join();
  t3.join();

  return EXIT_SUCCESS;
}