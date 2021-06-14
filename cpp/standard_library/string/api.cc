#include <exception>
#include <iostream>
#include <string>

int main() {
  // append
  {
    std::string s("hello");
    s.append("world");
    std::cout << s << std::endl;
  }

  // substr
  {
    std::string s("hello");
    std::cout << s.substr(0, 2) << std::endl;
  }

  // find
  {
    std::string s("hello");
    size_t pos;
    if ((pos = s.find('e', 2)) != std::string::npos) {
      std::cout << pos << std::endl;
    }
    if ((pos = s.find("ll")) != std::string::npos) {
      std::cout << pos << std::endl;
    }
  }

  // replace
  {
    std::string s("hello");
    s.replace(s.find("ll"), 2, "abcd");
    std::cout << s << std::endl;

    s = "aa bb cc";
  }

  // erase
  {
    std::string s("aa bb cc");
    auto it = s.find(' ');
    while (it != std::string::npos) {
      s.erase(it, 1);
      it = s.find(' ');
    }

    std::cout << s << std::endl;
  }

  return 0;
}