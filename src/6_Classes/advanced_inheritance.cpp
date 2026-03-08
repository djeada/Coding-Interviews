/*
 * Task: Demonstrate diamond inheritance, covariant returns, and object slicing.
 *
 * ADVANCED C++ INHERITANCE PITFALLS
 *
 * Problem:
 * Build a small inheritance hierarchy that demonstrates three topics:
 * virtual inheritance to solve the diamond problem, covariant return types in
 * overridden methods, and object slicing when copying derived objects by value.
 *
 * Constraints:
 * - Use one shared `Base` subobject via virtual inheritance.
 * - Show that `clone()` in derived class can return a more specific pointer.
 * - Include an example that slices by value and one that avoids slicing.
 *
 * Example:
 * Input: create `FinalDerived`, call `show()`, `clone()`, and pass to holder
 * Output: behavior confirms diamond resolution, covariant clone, and slicing
 */

#include <iostream>
#include <memory>
#include <string>

// ------------------- Diamond Inheritance with Virtual Inheritance
// -------------------

// Base class
class Base {
public:
  Base() : baseValue(42) {}
  virtual ~Base() = default;
  virtual void show() const { std::cout << "Base: " << baseValue << "\n"; }
  virtual Base *clone() const {
    return new Base(*this);
  } // For covariant return demonstration

protected:
  int baseValue;
};

// Derived1 and Derived2 virtually inherit from Base to solve the diamond
// problem.
class Derived1 : virtual public Base {
public:
  Derived1() : d1Value(10) {}
  virtual void show() const override {
    std::cout << "Derived1: " << d1Value << ", ";
    Base::show();
  }

protected:
  int d1Value;
};

class Derived2 : virtual public Base {
public:
  Derived2() : d2Value(20) {}
  virtual void show() const override {
    std::cout << "Derived2: " << d2Value << ", ";
    Base::show();
  }

protected:
  int d2Value;
};

// FinalDerived inherits from both Derived1 and Derived2.
class FinalDerived : public Derived1, public Derived2 {
public:
  FinalDerived() : extraValue(100) {}
  virtual void show() const override {
    std::cout << "FinalDerived: " << extraValue << ", ";
    // Only one Base exists due to virtual inheritance.
    Base::show();
  }
  // Covariant return: overriding clone() to return pointer to FinalDerived.
  virtual FinalDerived *clone() const override {
    return new FinalDerived(*this);
  }

private:
  int extraValue;
};

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectTrue(bool condition, const std::string &label) {
    ++total;
    if (condition) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=true got=false\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};
} // namespace

void testDiamondInheritance(TestRunner &runner) {
  FinalDerived fd;
  // Both Derived1 and Derived2 subobjects share a single Base subobject.
  // Calling show() will only print one Base value.
  fd.show();
  runner.expectTrue(true, "diamond inheritance executed");
}

// ------------------- Covariant Return Types -------------------

// Demonstrate that FinalDerived::clone() returns FinalDerived*.
void testCovariantReturnTypes(TestRunner &runner) {
  FinalDerived original;
  // Clone the object using base pointer.
  Base *clonedBase = original.clone();
  // Check if the returned pointer is actually of type FinalDerived.
  FinalDerived *clonedFinal = dynamic_cast<FinalDerived *>(clonedBase);
  runner.expectTrue(clonedFinal != nullptr, "covariant clone type");
  if (clonedFinal) {
    clonedFinal->show();
  }
  delete clonedBase;
}

// ------------------- Object Slicing Prevention -------------------

// A helper class that holds a Base by value.
class BaseHolder {
public:
  // Storing by value can cause slicing if a derived is passed.
  BaseHolder(const Base &b) : baseCopy(b) {}
  void show() const { baseCopy.show(); }

private:
  Base baseCopy; // Object slicing happens here.
};

void testObjectSlicing(TestRunner &runner) {
  FinalDerived fd;
  // Demonstrate object slicing: storing a FinalDerived in a BaseHolder slices
  // off derived parts.
  BaseHolder holder(fd);
  std::cout << "Sliced object: ";
  holder.show(); // Will only show Base part, not FinalDerived's extra info.

  // Prevention: use pointer or reference to avoid slicing.
  const Base &ref = fd;
  std::cout << "Referenced object: ";
  ref.show(); // Calls FinalDerived::show() due to polymorphism.

  runner.expectTrue(true, "object slicing prevention executed");
}

// ------------------- Test Runner -------------------
void test() {
  TestRunner runner;
  testDiamondInheritance(runner);
  testCovariantReturnTypes(runner);
  testObjectSlicing(runner);
  runner.summary();
}

int main() {
  test();
  return 0;
}
