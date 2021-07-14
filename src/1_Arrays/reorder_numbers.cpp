#include <cassert>
#include <set>
#include <vector>

bool check(int num) {
  if ((num & 0x1) == 0)
    return true;
  return false;
}

std::vector<int> reorderOddEven1(std::vector<int> arr) {

  int begin = 0;
  int end = arr.size() - 1;

  while (begin < end) {
    while (begin < end && (arr[begin] & 0x1) != 0)
      begin++;

    while (begin < end && (arr[end] & 0x1) == 0)
      end--;

    if (begin < end)
      std::swap(arr[begin], arr[end]);
  }

  return arr;
}

std::vector<int> reorderOddEven2(std::vector<int> arr) {

  int begin = 0;
  int end = arr.size() - 1;

  while (begin < end) {
    while (begin < end && !check(arr[begin]))
      begin++;

    while (begin < end && check(arr[end]))
      end--;

    if (begin < end)
      std::swap(arr[begin], arr[end]);
  }

  return arr;
}

void test1() {
  std::vector<int> arr{1, 2, 3, 4, 5, 6, 7};
  std::set<int> result{1, 3, 5, 7, 2, 4, 6};
  auto ans = reorderOddEven1(arr);
  assert(std::set<int>(ans.begin(), ans.end()) == result);
}

void test2() {
  std::vector<int> arr{1, 2, 3, 4, 5, 6, 7};
  std::set<int> result{1, 3, 5, 7, 2, 4, 6};
  auto ans = reorderOddEven1(arr);
  assert(std::set<int>(ans.begin(), ans.end()) == result);
}

void test3() {
  std::vector<int> arr{1, 3, 5, 7, 2, 4, 6};
  std::set<int> result{1, 3, 5, 7, 2, 4, 6};
  auto ans = reorderOddEven1(arr);
  assert(std::set<int>(ans.begin(), ans.end()) == result);
}

void test4() {
  std::vector<int> arr{1, 3, 5, 7, 2, 4, 6};
  std::set<int> result{1, 3, 5, 7, 2, 4, 6};
  auto ans = reorderOddEven1(arr);
  assert(std::set<int>(ans.begin(), ans.end()) == result);
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
