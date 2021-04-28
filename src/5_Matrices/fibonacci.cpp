#include <cassert>
#include <stdexcept>

long long fibonacci1(unsigned int n) {
  if (n <= 0)
    return 0;

  if (n == 1)
    return 1;

  return fibonacci1(n - 1) + fibonacci1(n - 2);
}

long long fibonacci2(unsigned int n) {
  if (n <= 0)
    return 0;

  if (n == 1)
    return 1;

  long long fibNMinusOne = 1;
  long long fibNMinusTwo = 0;
  long long fibN = 0;
  unsigned int i;

  for (i = 2; i <= n; ++i) {
    fibN = fibNMinusOne + fibNMinusTwo;

    fibNMinusTwo = fibNMinusOne;
    fibNMinusOne = fibN;
  }

  return fibN;
}

struct Matrix2By2 {
  long long m_00;
  long long m_01;
  long long m_10;
  long long m_11;
};

struct Matrix2By2 MatrixMultiply(const struct Matrix2By2 *matrix1,
                                 const struct Matrix2By2 *matrix2) {
  struct Matrix2By2 result;
  result.m_00 = matrix1->m_00 * matrix2->m_00 + matrix1->m_01 * matrix2->m_10;
  result.m_01 = matrix1->m_00 * matrix2->m_01 + matrix1->m_01 * matrix2->m_11;
  result.m_10 = matrix1->m_10 * matrix2->m_00 + matrix1->m_11 * matrix2->m_10;
  result.m_11 = matrix1->m_10 * matrix2->m_01 + matrix1->m_11 * matrix2->m_11;

  return result;
}

struct Matrix2By2 MatrixPower(unsigned int n) {
  struct Matrix2By2 result;
  struct Matrix2By2 unit = {1, 1, 1, 0};

  if (n < 0)
    throw std::runtime_error("Not defined for n <= 0.");

  if (n == 1) {
    result = unit;
  } else if (n % 2 == 0) {
    result = MatrixPower(n / 2);
    result = MatrixMultiply(&result, &result);
  } else if (n % 2 == 1) {
    result = MatrixPower((n - 1) / 2);
    result = MatrixMultiply(&result, &result);
    result = MatrixMultiply(&result, &unit);
  }

  return result;
}

long long fibonacci3(unsigned int n) {
  if (n <= 0)
    return 0;

  if (n == 1)
    return 1;

  struct Matrix2By2 PowerNMinus2;
  PowerNMinus2 = MatrixPower(n - 1);
  return PowerNMinus2.m_00;
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
