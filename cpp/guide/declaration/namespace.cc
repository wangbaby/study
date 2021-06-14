#include <cstdlib>
#include <iostream>

// namespace alias

namespace foo {
namespace bar {
namespace baz {
int qux = 1;
}
}  // namespace bar
}  // namespace foo

namespace fbz = foo::bar::baz;

int main() {
  std::cout << fbz::qux << std::endl;

  return EXIT_SUCCESS;
}