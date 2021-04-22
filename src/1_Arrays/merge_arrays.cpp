#include <cassert>
#include <vector>

void merge(std::vector<int> &arr1, std::vector<int> &arr2) {
  int idx1, idx2, idxMerged;

  if (arr1.empty() || arr2.empty()) {
    return;
  }

  idx1 = arr1.size() - 1;
  idx2 = arr2.size() - 1;
  idxMerged = arr1.size() + arr2.size() - 1;

  arr1.resize(idxMerged + 1);

  while (idx1 >= 0 && idx2 >= 0) {
    if (arr1[idx1] >= arr2[idx2]) {
      arr1[idxMerged--] = arr1[idx1--];
    } else {
      arr1[idxMerged--] = arr2[idx2--];
    }
  }

  while (idx2 >= 0) {
    arr1[idxMerged--] = arr2[idx2--];
  }
}

void test1() {
  std::vector<int> arr1{1, 3, 5, 7, 9};
  std::vector<int> arr2{2, 4, 6, 8, 10};

  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  merge(arr1, arr2);
  assert(arr1 == expected);
}

void test2() {
  std::vector<int> arr1{2, 4, 6, 8, 10};
  std::vector<int> arr2{1, 3, 5, 7, 9};

  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  merge(arr1, arr2);
  assert(arr1 == expected);
}

void test3() {
  std::vector<int> arr1{2, 4, 6, 8, 10};
  std::vector<int> arr2{2, 4, 6, 8, 10};

  std::vector<int> expected{2, 2, 4, 4, 6, 6, 8, 8, 10, 10};

  merge(arr1, arr2);
  assert(arr1 == expected);
}

void test4() {
  std::vector<int> arr1{1, 2, 3, 4, 5};
  std::vector<int> arr2{6, 7, 8, 9, 10};

  std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  merge(arr1, arr2);
  assert(arr1 == expected);
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 1;
}
