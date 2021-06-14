#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main() {
  {
    std::allocator<std::string> alloc;

    // allocate
    int n = 10;
    auto const p = alloc.allocate(n);

    // constructo
    auto q = p;
    alloc.construct(q++);
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++, "123");

    std::cout << p[0] << p[1] << std::endl;
    std::cout << *p << *(p + 1) << std::endl;

    // destory
    while (q != p) alloc.destroy(--q);

    // deallocate
    alloc.deallocate(p, n);
  }

  {
    // algorithm: uninitialized_copy uninitialized_fill_n
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    std::allocator<int> alloc;
    auto p = alloc.allocate(vec.size() * 2);

    auto q = std::uninitialized_copy(vec.cbegin(), vec.cend(), p);

    q = std::uninitialized_fill_n(q, vec.size(), 100);

    // destory
    while (q != p) alloc.destroy(--q);

    // deallocate
    alloc.deallocate(p, vec.size() * 2);

    return EXIT_SUCCESS;
  }
}