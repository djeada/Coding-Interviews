#include <iostream>

class A {
private:
  int val;

public:
  A(int n) { val = n; }
  A(const A &other) { val = other.val; }
  void Print() { std::cout << val << std::endl; }
};

int main() {
  A a = 10;
  A b = a;
  b.Print();

  A c(30);
  c.Print();
  c = a;
  c.Print();

  return 0;
}
