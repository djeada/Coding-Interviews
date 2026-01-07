/*
 * Task: Compare runtime polymorphism, CRTP, and composition for shapes.
 *
 * SHAPE INHERITANCE DEMONSTRATION
 *
 * Illustrate different approaches to using inheritance and polymorphism in
 * C++.
 *
 * Three solutions are provided:
 *
 * 1. Simple (Runtime Polymorphism):
 *    Uses a base class `Shape` with a virtual method `area()`. Derived classes
 *    `Circle` and `Rectangle` override the method to compute their respective
 *    areas. This is the classic example of runtime polymorphism.
 *
 * 2. Optimal (Compile-time Polymorphism using CRTP):
 *    Uses the Curiously Recurring Template Pattern (CRTP) to achieve
 * polymorphic behavior at compile time. This method avoids the overhead of
 * virtual functions.
 *
 * 3. Alternative (Using Composition):
 *    Demonstrates an alternative design where a shape object holds a pointer to
 *    a strategy object that defines its area calculation. This approach shows
 *    the flexibility of composition over inheritance.
 *
 * ASCII Illustration:
 *
 *             Runtime Polymorphism
 *                   Shape
 *                    / \
 *              Circle   Rectangle
 *
 *             Compile-time Polymorphism (CRTP)
 *                   ShapeCRTP
 *                    /   \
 *          CircleCRTP   RectangleCRTP
 *
 *             Composition
 *                 ShapeComposition
 *                    |
 *             +-----------------+
 *             |  AreaStrategy   |
 *             +-----------------+
 *                /          \
 *      CircleAreaStrategy   RectangleAreaStrategy
 *
 * Example:
 *   Create a Circle with radius 5 and a Rectangle with width 4 and height 6.
 *
 *   Expected output (areas):
 *     Circle area: approximately 78.5398
 *     Rectangle area: 24
 *
 *   Explanation:
 *     - Circle area is computed as π * r^2.
 *     - Rectangle area is computed as width * height.
 */

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

// --------------------- Simple (Runtime Polymorphism) Solution
// ---------------------
class Shape {
public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
};

class Circle : public Shape {
public:
  explicit Circle(double r) : radius(r) {}
  double area() const override { return M_PI * radius * radius; }

private:
  double radius;
};

class Rectangle : public Shape {
public:
  Rectangle(double w, double h) : width(w), height(h) {}
  double area() const override { return width * height; }

private:
  double width, height;
};

void testRuntimePolymorphism(TestRunner &runner) {
  std::unique_ptr<Shape> circle = std::make_unique<Circle>(5.0);
  std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(4.0, 6.0);

  double circleArea = circle->area();
  double rectangleArea = rectangle->area();

  // Allow for small floating point error.
  runner.expectNear(circleArea, M_PI * 25, 1e-6, "runtime circle area");
  runner.expectNear(rectangleArea, 24.0, 1e-6, "runtime rectangle area");
}

// ---------------- Optimal (Compile-time Polymorphism using CRTP) Solution
// ----------------
template <typename Derived> class ShapeCRTP {
public:
  double area() const { return static_cast<const Derived *>(this)->area(); }
};

class CircleCRTP : public ShapeCRTP<CircleCRTP> {
public:
  explicit CircleCRTP(double r) : radius(r) {}
  double area() const { return M_PI * radius * radius; }

private:
  double radius;
};

class RectangleCRTP : public ShapeCRTP<RectangleCRTP> {
public:
  RectangleCRTP(double w, double h) : width(w), height(h) {}
  double area() const { return width * height; }

private:
  double width, height;
};

void testCompileTimePolymorphism(TestRunner &runner) {
  CircleCRTP circle(5.0);
  RectangleCRTP rectangle(4.0, 6.0);

  double circleArea = circle.area();
  double rectangleArea = rectangle.area();

  runner.expectNear(circleArea, M_PI * 25, 1e-6, "crtp circle area");
  runner.expectNear(rectangleArea, 24.0, 1e-6, "crtp rectangle area");
}

// ---------------- Alternative (Using Composition) Solution ----------------
class AreaStrategy {
public:
  virtual ~AreaStrategy() = default;
  virtual double area() const = 0;
};

class CircleAreaStrategy : public AreaStrategy {
public:
  explicit CircleAreaStrategy(double r) : radius(r) {}
  double area() const override { return M_PI * radius * radius; }

private:
  double radius;
};

class RectangleAreaStrategy : public AreaStrategy {
public:
  RectangleAreaStrategy(double w, double h) : width(w), height(h) {}
  double area() const override { return width * height; }

private:
  double width, height;
};

class ShapeComposition {
public:
  explicit ShapeComposition(std::unique_ptr<AreaStrategy> strategy)
      : strategy_(std::move(strategy)) {}

  double area() const { return strategy_->area(); }

private:
  std::unique_ptr<AreaStrategy> strategy_;
};

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectNear(double got, double expected, double tol,
                  const std::string &label) {
    ++total;
    if (std::abs(got - expected) <= tol) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << expected
              << " got=" << got << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};
} // namespace

void testComposition(TestRunner &runner) {
  ShapeComposition circleShape(std::make_unique<CircleAreaStrategy>(5.0));
  ShapeComposition rectangleShape(
      std::make_unique<RectangleAreaStrategy>(4.0, 6.0));

  double circleArea = circleShape.area();
  double rectangleArea = rectangleShape.area();

  runner.expectNear(circleArea, M_PI * 25, 1e-6, "composition circle area");
  runner.expectNear(rectangleArea, 24.0, 1e-6, "composition rectangle area");
}

// ---------------- Test Runner ----------------
void test() {
  TestRunner runner;
  testRuntimePolymorphism(runner);
  testCompileTimePolymorphism(runner);
  testComposition(runner);
  runner.summary();
}

int main() {
  test();
  return 0;
}
