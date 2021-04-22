#include <cassert>
#include <vector>

int getMinSequentially(std::vector<int> &arr, int idx1, int idx2) {
  int result = arr[idx1];
  for (int i = idx1 + 1; i <= idx2; ++i) {
    if (result > arr[i])
      result = arr[i];
  }

  return result;
}

int getMin(std::vector<int> &arr) {
  int idx1 = 0;
  int idx2 = arr.size() - 1;
  int idxMid = idx1;

  while (arr[idx1] >= arr[idx2]) {
    if (idx2 - idx1 == 1) {
      idxMid = idx2;
      break;
    }

    idxMid = (idx1 + idx2) / 2;

    if (arr[idx1] == arr[idx2] && arr[idxMid] == arr[idx1])
      return getMinSequentially(arr, idx1, idx2);

    if (arr[idxMid] >= arr[idx1])
      idx1 = idxMid;

    else if (arr[idxMid] <= arr[idx2])
      idx2 = idxMid;
  }

  return arr[idxMid];
}

void test1() {
  std::vector<int> arr{3, 4, 5, 1, 2};
  int result = 1;
  assert(getMin(arr) == result);
}

void test2() {
  std::vector<int> arr{10, 10, 2, 5, 5, 9, 9, 9};
  int result = 2;
  assert(getMin(arr) == result);
}

void test3() {
  std::vector<int> arr{-1, -1, 5, -1, -1};
  int result = -1;
  assert(getMin(arr) == result);
}

void test4() {
  std::vector<int> arr{0, 0, 0, 0, 0, 0};
  int result = 0;
  assert(getMin(arr) == result);
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
