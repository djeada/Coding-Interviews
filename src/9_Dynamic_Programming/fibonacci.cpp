/*
 * Task: Compute the nth Fibonacci number.
 *
 * COMPUTING THE N-TH FIBONACCI NUMBER
 *
 * Given a non-negative integer n, compute the nth Fibonacci number.
 * The Fibonacci sequence is defined by the recurrence relation:
 *
 *    F(0) = 0, F(1) = 1,
 *    F(n) = F(n-1) + F(n-2) for n > 1.
 *
 * Constraints:
 *    - 0 <= n <= 90 (to avoid overflow with long long)
 *
 * Visual illustration (Fibonacci sequence):
 *
 *    n: 0  1  2  3  4  5  6  7  8  9  10
 * F(n): 0  1  1  2  3  5  8 13 21 34  55
 *
 * Example Input/Output:
 * Input:  7
 * Output: 13
 * Explanation: The 7th Fibonacci number (0-indexed) is 13.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(long long got, long long expected,
                   const std::string &label) {
    ++total;
    if (got == expected) {
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

// Simple Recursive Solution
// Complexity: Exponential time O(2^n), suitable for educational purposes and
// small inputs.
long long simpleSolution(unsigned int n) {
  if (n <= 1)
    return n;
  return simpleSolution(n - 1) + simpleSolution(n - 2);
}

// Optimal Iterative Solution
// Complexity: Linear time O(n), space O(1). Efficient for large inputs.
long long optimalSolution(unsigned int n) {
  if (n <= 1)
    return n;
  long long a = 0, b = 1;
  for (unsigned int i = 2; i <= n; ++i) {
    long long next = a + b;
    a = b;
    b = next;
  }
  return b;
}

// Alternative Solution using Matrix Exponentiation
// Complexity: Logarithmic time O(log n), demonstrates efficient exponentiation
// method.
struct Matrix {
  long long a, b, c, d;

  Matrix operator*(const Matrix &other) const {
    return {a * other.a + b * other.c, a * other.b + b * other.d,
            c * other.a + d * other.c, c * other.b + d * other.d};
  }
};

Matrix matrixPow(Matrix base, unsigned int power) {
  Matrix result = {1, 0, 0, 1}; // Identity matrix
  while (power > 0) {
    if (power % 2 == 1)
      result = result * base;
    base = base * base;
    power /= 2;
  }
  return result;
}

long long alternativeSolution(unsigned int n) {
  if (n == 0)
    return 0;
  Matrix fibMatrix = {1, 1, 1, 0};
  Matrix result = matrixPow(fibMatrix, n - 1);
  return result.a;
}

// Test cases for correctness
void test() {
  std::vector<unsigned int> testInputs = {0, 1, 2, 3, 10, 50, 90};
  TestRunner runner;

  for (unsigned int n : testInputs) {
    long long simple =
        (n <= 30)
            ? simpleSolution(n)
            : -1; // Simple solution limited to n<=30 to avoid long computation
    long long optimal = optimalSolution(n);
    long long alternative = alternativeSolution(n);

    if (n <= 30)
      runner.expectEqual(simple, optimal,
                         "simple == optimal n=" + std::to_string(n));
    runner.expectEqual(optimal, alternative,
                       "optimal == alternative n=" + std::to_string(n));

    std::cout << "Fibonacci(" << n << ") = " << optimal << std::endl;
  }

  runner.summary();
}

int main() {
  test();
  return 0;
}
