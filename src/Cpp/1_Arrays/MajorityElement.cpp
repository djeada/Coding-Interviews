#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

using namespace std;
bool checkMajorityExistence(vector<int> numbers, int number);
int randomInRange(int start, int end);
int partition(vector<int> numbers, int start, int end);

int getMajority_1(vector<int> numbers) {
  int length = numbers.size();
  int middle = length >> 1;
  int start = 0;
  int end = length - 1;

  int index = partition(numbers, start, end);
  while (index != middle) {
    if (index > middle) {
      end = index - 1;
      index = partition(numbers, start, end);
    } else {
      start = index + 1;
      index = partition(numbers, start, end);
    }
  }
  int result = numbers[middle];
  if (!checkMajorityExistence(numbers, result))
    throw invalid_argument("No majority exisits.");

  return result;
}

int partition(vector<int> numbers, int start, int end) {
  int index = randomInRange(start, end);
  swap(numbers[index], numbers[end]);

  int small = start - 1;
  for (index = start; index < end; ++index) {
    if (numbers[index] < numbers[end]) {
      ++small;
      if (small != index)
        swap(numbers[index], numbers[small]);
    }
  }
  ++small;
  swap(numbers[index], numbers[end]);

  return small;
}

int randomInRange(int start, int end) {
  random_device rd;  // obtain a random number from hardware
  mt19937 eng(rd()); // seed the generator
  uniform_int_distribution<> distr(start, end);
  return distr(eng);
}

int getMajority_2(vector<int> numbers) {
  int result = numbers[0];
  int times = 1;
  for (int i = 1; i < numbers.size(); ++i) {
    if (times == 0) {
      result = numbers[i];
      times = 1;
    } else if (numbers[i] == result)
      times++;
    else
      times--;
  }
  if (!checkMajorityExistence(numbers, result))
    throw invalid_argument("No majority exisits.");

  return result;
}

//================= Common methods =================
bool checkMajorityExistence(vector<int> numbers, int number) {
  int times = 0;
  for (int i = 0; i < numbers.size(); ++i) {
    if (numbers[i] == number)
      times++;
  }
  return (times * 2 > numbers.size());
}

//================= Test Code =================
void test(const string &testName, vector<int> numbers, int expected,
          bool invalidArgument) {
  cout << testName << " begins: ";

  try {
    int majority = getMajority_1(numbers);

    if (!invalidArgument && majority == expected)
      cout << "Solution1 Passed; ";
    else
      cout << "Solution1 FAILED; ";
  } catch (const invalid_argument &ia) {
    if (invalidArgument)
      cout << "Solution1 Passed; ";
    else
      cout << "Solution1 FAILED; ";
  }
  try {
    int majority = getMajority_2(numbers);

    if (!invalidArgument && majority == expected)
      cout << "Solution2 Passed.\n";
    else
      cout << "Solution2 FAILED.\n";
  } catch (const invalid_argument &ia) {
    if (invalidArgument)
      cout << "Solution2 Passed.\n";
    else
      cout << "Solution2 FAILED.\n";
  }
}

void test1() {
  vector<int> numbers{1, 2, 3, 2, 2, 2, 5, 4, 2};
  test("Test1", numbers, 2, false);
}

void test2() {
  vector<int> numbers{1, 2, 3, 2, 4, 2, 5, 2, 3};
  test("test2", numbers, 0, true);
}

void test3() {
  vector<int> numbers{2, 2, 2, 2, 2, 1, 3, 4, 5};
  test("test3", numbers, 2, false);
}

void test4() {
  vector<int> numbers{1, 3, 4, 5, 2, 2, 2, 2, 2};
  test("test4", numbers, 2, false);
}

void test5() {
  vector<int> numbers{1};
  test("test4", numbers, 1, false);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();

  return 0;
}
