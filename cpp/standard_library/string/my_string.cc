#include <cstring>
#include <iostream>

class MyString {
 public:
  MyString() : m_data(nullptr), m_len(0) {}

  MyString(const char *str) {
    m_len = strlen(str);
    copy_data(str);
  }

  MyString(const MyString &ms) {
    m_len = ms.m_len;
    copy_data(ms.m_data);
    std::cout << "Copy Constructor is called! source: " << ms.m_data
              << std::endl;
  }

  MyString(MyString &&ms) {
    std::cout << "Move Constructor is called! source: " << ms.m_data
              << std::endl;
    m_data = ms.m_data;
    m_len = ms.m_len;
    ms.m_data = nullptr;
    ms.m_len = 0;
  }

  MyString &operator=(const MyString &ms) {
    if (this != &ms) {
      m_len = ms.m_len;
      copy_data(ms.m_data);
    }
    std::cout << "Copy Assignment is called! source: " << ms.m_data
              << std::endl;

    return *this;
  }

  MyString &operator=(MyString &&ms) {
    std::cout << "Move Assignment is called! source: " << ms.m_data
              << std::endl;
    if (this != &ms) {
      m_len = ms.m_len;
      m_data = ms.m_data;
      ms.m_len = 0;
      ms.m_data = nullptr;
    }
    return *this;
  }

  virtual ~MyString() {
    if (m_data) free(m_data);
  }

 private:
  char *m_data;
  size_t m_len;

  void copy_data(const char *str) {
    m_data = new char(m_len + 1);
    memcpy(m_data, str, m_len);
    m_data[m_len] = '\0';
  }
};

int main() {
  MyString ms("123");

  return 0;
}
