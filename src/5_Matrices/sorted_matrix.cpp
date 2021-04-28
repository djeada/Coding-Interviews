#include <cassert>
#include <vector>

bool find(std::vector<std::vector<int>> &matrix, int value) {
  if (matrix.empty())
    return false;

  int rows = matrix.size();
  int cols = matrix.front().size();
  int start = 0;
  int end = rows * cols - 1;

  while (start <= end) {
    int mid = start + (end - start) / 2;
    int row = mid / cols;
    int col = mid % cols;
    int v = matrix[row][col];

    if (v == value) {
      return true;
    } else if (v > value) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }

  return false;
}

void test1() {
  std::vector<std::vector<int>> matrix{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
  int value = 7;
  assert(find(matrix, value));
}

void test2() {
  std::vector<std::vector<int>> matrix{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
  int value = 1;
  assert(find(matrix, value));
}

void test3() {
  std::vector<std::vector<int>> matrix{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
  int value = 17;
  assert(find(matrix, value));
}

void test4() {
  std::vector<std::vector<int>> matrix{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
  int value = 6;
  assert(!find(matrix, value));
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
