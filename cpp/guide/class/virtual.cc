#include <stdio.h>

class Base {
 public:
  Base() { doPrivate(); }
  void virtual doPublic() {
    printf("Base::doPublic\n");
    doPrivate();
  }

  virtual ~Base() = default;

 private:
  void virtual doPrivate() { printf("Base::doPrivate\n"); }
};

class Derived : public Base {
 public:
  Derived() { doPrivate(); }

 private:
  void doPrivate() { printf("Derived::doPrivate\n"); }
};

int main() {
  Base *b = new Derived();
  b->doPublic();
}