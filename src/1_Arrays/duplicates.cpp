#include <cassert>
#include <vector>

int howManyDuplicates(std::vector<int> &arr) {
  int count = 0;
  for (unsigned int i = 0; i < arr.size(); i++) {
    for (unsigned int j = i + 1; j < arr.size(); j++) {
      if (arr[i] == arr[j])
        count++;
    }
  }

  return count;
}

std::vector<int> getDuplicates(std::vector<int> &arr) {

  std::vector<int> duplicates;

  int count = 0;
  for (unsigned int i = 0; i < arr.size(); i++) {
    for (unsigned int j = i + 1; j < arr.size(); j++) {
      if (arr[i] == arr[j]) {
        duplicates.push_back(arr[i]);
        count++;
      }
    }
  }

  return duplicates;
}

void test1() {
  std::vector<int> arr{1, 2, 3, 4, 5};
  int result = 0;
  assert(howManyDuplicates(arr) == result);
}

void test2() {
  std::vector<int> arr{5, 10, 15, 5, 3, 3};
  int result = 2;
  assert(howManyDuplicates(arr) == result);
}

void test3() {
  std::vector<int> arr{1, 2, 3, 4, 5};
  std::vector<int> result;
  assert(getDuplicates(arr) == result);
}

void test4() {
  std::vector<int> arr{3, 9, 9, 7, 3};
  std::vector<int> result{3, 9};
  assert(getDuplicates(arr) == result);
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
