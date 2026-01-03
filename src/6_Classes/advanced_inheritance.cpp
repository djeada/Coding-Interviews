/*
 * Task: Demonstrate diamond inheritance, covariant returns, and object slicing.
 *
 * ADVANCED INHERITANCE IN C++: DIAMOND, COVARIANCE, AND OBJECT SLICING
 *
 * Demonstrate several tricky parts of inheritance in C++:
 *
 * 1. Diamond Inheritance with Virtual Inheritance:
 *    Shows how to solve the diamond problem by using virtual inheritance so
 * that the common base class appears only once in the derived hierarchy.
 *
 * 2. Covariant Return Types:
 *    Demonstrates how overridden methods in derived classes can have covariant
 * return types, allowing the derived version to return a pointer/reference to a
 * more specific type.
 *
 * 3. Avoiding Object Slicing:
 *    Highlights the slicing problem when copying derived objects into base
 * objects and shows how to avoid it using pointers or references.
 *
 * ASCII Illustration:
 *
 *              Base
 *             /    \
 *    Derived1        Derived2
 *             \    /
 *          FinalDerived
 *
 * Example:
 *   - Diamond Inheritance: Both Derived1 and Derived2 virtually inherit from
 * Base, and FinalDerived inherits from both ensuring only one Base instance
 * exists.
 *   - Covariant Return Type: FinalDerived::clone() returns a pointer to
 * FinalDerived, overriding Base::clone() which returns a pointer to Base.
 *   - Object Slicing: Demonstrates that copying by value from a derived to a
 * base object causes loss of derived-specific data; using pointers preserves
 * full object.
 *
 * Expected Console Output:
 *   Diamond inheritance test passed!
 *   Covariant return types test passed!
 *   Object slicing prevention test passed!
 */

#include <cassert>
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

void testDiamondInheritance() {
  FinalDerived fd;
  // Both Derived1 and Derived2 subobjects share a single Base subobject.
  // Calling show() will only print one Base value.
  fd.show();
  std::cout << "Diamond inheritance test passed!\n";
}

// ------------------- Covariant Return Types -------------------

// Demonstrate that FinalDerived::clone() returns FinalDerived*.
void testCovariantReturnTypes() {
  FinalDerived original;
  // Clone the object using base pointer.
  Base *clonedBase = original.clone();
  // Check if the returned pointer is actually of type FinalDerived.
  FinalDerived *clonedFinal = dynamic_cast<FinalDerived *>(clonedBase);
  assert(clonedFinal != nullptr);
  // Use the cloned object.
  clonedFinal->show();
  delete clonedBase;
  std::cout << "Covariant return types test passed!\n";
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

void testObjectSlicing() {
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

  std::cout << "Object slicing prevention test passed!\n";
}

// ------------------- Test Runner -------------------
void test() {
  testDiamondInheritance();
  testCovariantReturnTypes();
  testObjectSlicing();
}

int main() {
  test();
  return 0;
}
