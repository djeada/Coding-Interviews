/*
 * Task: Compare runtime polymorphism, CRTP, and composition for shapes.
 *
 * POLYMORPHISM APPROACHES FOR SHAPES
 *
 * Problem:
 * Design shape-area calculation in three ways: runtime polymorphism (virtual
 * functions), compile-time polymorphism (CRTP), and composition (strategy
 * object). Verify that all approaches produce correct area results.
 *
 * Constraints:
 * - Circle area uses `pi * r^2`.
 * - Rectangle area uses `width * height`.
 * - Implement and test all three approaches in one file.
 *
 * Example:
 * Input: circle radius = 5, rectangle width = 4, height = 6
 * Output: circle area ~= 78.5398, rectangle area = 24
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

void testRuntimePolymorphism(TestRunner &runner) {
  std::unique_ptr<Shape> circle = std::make_unique<Circle>(5.0);
  std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(4.0, 6.0);

  double circleArea = circle->area();
  double rectangleArea = rectangle->area();

  // Allow for small floating point error.
  runner.expectNear(circleArea, M_PI * 25, 1e-6, "runtime circle area");
  runner.expectNear(rectangleArea, 24.0, 1e-6, "runtime rectangle area");
}

void testCompileTimePolymorphism(TestRunner &runner) {
  CircleCRTP circle(5.0);
  RectangleCRTP rectangle(4.0, 6.0);

  double circleArea = circle.area();
  double rectangleArea = rectangle.area();

  runner.expectNear(circleArea, M_PI * 25, 1e-6, "crtp circle area");
  runner.expectNear(rectangleArea, 24.0, 1e-6, "crtp rectangle area");
}

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
