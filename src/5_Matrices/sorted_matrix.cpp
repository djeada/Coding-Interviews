/**
 * This program searches for a specified value within a 2D matrix,
 * which is assumed to be sorted such that each row and each column
 * are in ascending order. The program provides a function `contains`
 * which implements a binary search algorithm to efficiently locate
 * the value, returning true if found and false otherwise. The program
 * also includes a set of test cases to validate the correctness of
 * the `contains` function.
 */

#include <cassert>
#include <vector>

bool contains(const std::vector<std::vector<int>> &matrix, int value) {
  if (matrix.empty() || matrix.front().empty())
    return false;

  const int rows = static_cast<int>(matrix.size());
  const int cols = static_cast<int>(matrix.front().size());
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
  assert(contains(matrix, value));
}

void test2() {
  std::vector<std::vector<int>> matrix{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
  int value = 1;
  assert(contains(matrix, value));
}

void test3() {
  std::vector<std::vector<int>> matrix{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
  int value = 17;
  assert(contains(matrix, value));
}

void test4() {
  std::vector<std::vector<int>> matrix{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
  int value = 6;
  assert(!contains(matrix, value));
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}
