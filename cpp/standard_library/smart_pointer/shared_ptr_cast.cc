#include <iostream>
#include <memory>

struct Base {
  Base() = default;
  virtual void print() const { std::cout << "this is Base" << std::endl; }

  virtual ~Base() {}
};

struct Derived : Base {
  Derived() = default;
  virtual void print() const override {
    std::cout << "this is Derived" << std::endl;
  }

  ~Derived() {}
};

int main() {
  auto bptr = std::make_shared<Base>();
  bptr->print();

  auto dptr = std::make_shared<Derived>();
  dptr->print();

  bptr = std::static_pointer_cast<Base>(dptr);
  bptr->print();

  auto downcastedPtr = std::dynamic_pointer_cast<Derived>(bptr);
  if (downcastedPtr) {
    downcastedPtr->print();
  }

  std::cout << dptr.use_count() << std::endl;

  return EXIT_SUCCESS;
}