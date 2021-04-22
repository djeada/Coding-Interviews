#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int duplicate(int numbers[], int length) {
  int sum1 = 0;

  for (int i = 0; i < length; ++i) {
    if (numbers[i] < 0 || numbers[i] > length - 2) {
      cout << "Invalid numbers." << endl;
      throw; // Just re-throw the exception
    }
    sum1 += numbers[i];
  }

  int sum2 = ((length - 1) * (length - 2)) >> 1;

  return sum1 - sum2;
}

void test(const std::string &testName, int numbers[], int n, int expected,
          bool invalidArgument) {
  cout << testName << " begins: ";

  try {
    int duplication = duplicate(numbers, n);
    if (!invalidArgument && duplication == expected)
      cout << "Passed.\n";
    else
      cout << "FAILED.\n";
  } catch (const invalid_argument &ia) {
    if (invalidArgument)
      cout << "Passed.\n";
    else
      cout << "FAILED.\n";
  }
}

void test1() {
  int numbers[] = {2, 1, 3, 1, 0};
  test("Test1", numbers, 5, 1, false);
}

void test2() {
  int numbers[] = {2, 0, 3, 1, 0};
  test("Test2", numbers, 5, 0, false);
}

void test3() {
  int numbers[] = {2, 0, 4, 3, 1, 4};
  test("Test3", numbers, 5, 4, false);
}

void test4() {
  int numbers[] = {2, 1, 3, 0, 4};
  test("Test4", numbers, 5, 0, true);
}

void test5() {
  int numbers[] = {2, 1, 3, 0, -1};
  test("Test5", numbers, 5, 0, true);
}

void test6() {
  int numbers[] = {0};
  test("Test6", numbers, 1, 0, true);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();

  return 0;
}
