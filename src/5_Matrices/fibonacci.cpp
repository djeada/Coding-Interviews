#include <cassert>
#include <stdexcept>
#include <vector>

/**
 * @brief Computes the nth Fibonacci number using recursion.
 * @param n The position of the Fibonacci number to be calculated.
 * @return The nth Fibonacci number.
 */
long long fibonacci1(unsigned int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  return fibonacci1(n - 1) + fibonacci1(n - 2);
}

/**
 * @brief Computes the nth Fibonacci number using iterative dynamic programming.
 * @param n The position of the Fibonacci number to be calculated.
 * @return The nth Fibonacci number.
 */
long long fibonacci2(unsigned int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;

  long long fibNMinusOne = 1;
  long long fibNMinusTwo = 0;
  long long fibN = 0;

  for (unsigned int i = 2; i <= n; ++i) {
    fibN = fibNMinusOne + fibNMinusTwo;
    fibNMinusTwo = fibNMinusOne;
    fibNMinusOne = fibN;
  }

  return fibN;
}

class Matrix2By2 {
public:
  long long m_00, m_01, m_10, m_11;

  Matrix2By2() : m_00(1), m_01(1), m_10(1), m_11(0) {}

  /**
   * @brief Multiplies two 2x2 matrices.
   * @param matrix Another 2x2 matrix to multiply with.
   * @return The resulting 2x2 matrix.
   */
  Matrix2By2 multiply(const Matrix2By2 &matrix) const {
    Matrix2By2 result;
    result.m_00 = m_00 * matrix.m_00 + m_01 * matrix.m_10;
    result.m_01 = m_00 * matrix.m_01 + m_01 * matrix.m_11;
    result.m_10 = m_10 * matrix.m_00 + m_11 * matrix.m_10;
    result.m_11 = m_10 * matrix.m_01 + m_11 * matrix.m_11;
    return result;
  }

  /**
   * @brief Computes the power of the matrix to the n.
   * @param n The exponent.
   * @return The matrix raised to the power of n.
   */
  Matrix2By2 power(unsigned int n) const {
    if (n == 1) {
      return *this;
    } else if (n % 2 == 0) {
      Matrix2By2 halfPower = power(n / 2);
      return halfPower.multiply(halfPower);
    } else {
      Matrix2By2 halfPower = power((n - 1) / 2);
      return halfPower.multiply(halfPower).multiply(*this);
    }
  }
};

/**
 * @brief Computes the nth Fibonacci number using matrix exponentiation.
 * @param n The position of the Fibonacci number to be calculated.
 * @return The nth Fibonacci number.
 */
long long fibonacci3(unsigned int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;

  Matrix2By2 matrix;
  return matrix.power(n - 1).m_00;
}

void test1() {
  unsigned int n = 0;
  long long result = 0;
  assert(fibonacci1(n) == result);
  assert(fibonacci2(n) == result);
  assert(fibonacci3(n) == result);
}

void test2() {
  unsigned int n = 1;
  long long result = 1;
  assert(fibonacci1(n) == result);
  assert(fibonacci2(n) == result);
  assert(fibonacci3(n) == result);
}

void test3() {
  unsigned int n = 6;
  long long result = 8;
  assert(fibonacci1(n) == result);
  assert(fibonacci2(n) == result);
  assert(fibonacci3(n) == result);
}

void test4() {
  unsigned int n = 10;
  long long result = 55;
  assert(fibonacci1(n) == result);
  assert(fibonacci2(n) == result);
  assert(fibonacci3(n) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 0;
}
