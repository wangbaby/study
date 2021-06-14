/**
 * 变长数组 vector
 * 
 * 可提供快速随机访问:
 * []
 * at(i) at会做边界检查 std::out_of_range
 * 
 * 适用于数据增删不频繁但需要高效随机存取的场合，而不适合于需要频繁在序列中增删数据的场合
 * 
 * reserve
 * capacity
 * 
 * 
 * 
 * 
 * 
 */

#include <iostream>
#include <vector>

int main() {
  {
    // constructor
    std::vector<int> vi(10, 100);
    for (const auto& i : vi) std::cout << i << " ";
    std::cout << std::endl;
  }

  {
    /**
     * reserve: 用于让容器预留空间，避免再次内存分配,新元素还没有分配，不能用[]访问 
     * resize :用元素的默认构造函数构造元素，可以用[]操作元素
     * capacity: 返回std::vector未重复分配前可以分配的大小
     */
    std::vector<int> vi;
    std::cout << vi.capacity() << std::endl;
    std::cout << vi.size() << std::endl;

    vi.push_back(100);
    std::cout << vi.capacity() << std::endl;
    std::cout << vi.size() << std::endl;

    vi.reserve(1000);
    std::cout << vi.capacity() << std::endl;
    std::cout << vi.size() << std::endl;

    {
      std::vector<int> vi;
      vi.reserve(10);
      for (int i = 0; i < 10; i++) {
        vi.push_back(i);
        std::cout << vi.size() << " , " << vi.capacity() << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}