#include <cassert>
#include <vector>

/**
 * @brief Searches for a value in a row and column sorted 2D matrix using
 * recursive binary search.
 * @param matrix The 2D matrix to search in.
 * @param value The value to search for.
 * @param row1 The start row index.
 * @param col1 The start column index.
 * @param row2 The end row index.
 * @param col2 The end column index.
 * @return True if the value is found, otherwise false.
 */
bool findSolution1(std::vector<std::vector<int>> &matrix, int value,
                   int row1 = 0, int col1 = 0, int row2 = -1, int col2 = -1) {
  if (matrix.empty())
    return false;

  int rows = matrix.size();
  int cols = matrix.front().size();

  if (row2 == -1 && col2 == -1) {
    row2 = rows - 1;
    col2 = cols - 1;
  }

  if (value < matrix[row1][col1] || value > matrix[row2][col2])
    return false;
  if (value == matrix[row1][col1] || value == matrix[row2][col2])
    return true;

  int midRow = (row1 + row2) / 2;
  int midCol = (col1 + col2) / 2;

  while ((midRow != row1 || midCol != col1) &&
         (midRow != row2 || midCol != col2)) {
    if (value == matrix[midRow][midCol])
      return true;

    auto [newRow, newCol] = value < matrix[midRow][midCol]
                                ? std::pair{midRow, midCol}
                                : std::pair{row1, col1};
    row2 = newRow;
    col2 = newCol;

    midRow = (row1 + row2) / 2;
    midCol = (col1 + col2) / 2;
  }

  bool found = midRow < rows - 1 &&
               findSolution1(matrix, value, midRow + 1, col1, row2, midCol);
  if (!found && midCol < cols - 1)
    found = findSolution1(matrix, value, row1, midCol + 1, midRow, col2);

  return found;
}

/**
 * @brief Searches for a value in a row and column sorted 2D matrix using a
 * stepwise linear search.
 * @param matrix The 2D matrix to search in.
 * @param value The value to search for.
 * @return True if the value is found, otherwise false.
 */
bool findSolution2(const std::vector<std::vector<int>> &matrix, int value) {
  if (matrix.empty())
    return false;

  int rows = matrix.size();
  int cols = matrix[0].size();
  int row = 0;
  int col = cols - 1;

  while (row < rows && col >= 0) {
    if (matrix[row][col] == value) {
      return true;
    }
    matrix[row][col] > value ? --col : ++row;
  }

  return false;
}

void test1() {
  std::vector<std::vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  int value = 7;
  assert(findSolution1(matrix, value));
  assert(findSolution2(matrix, value));
}

void test2() {
  std::vector<std::vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  int value = 5;
  assert(!findSolution1(matrix, value));
  assert(!findSolution2(matrix, value));
}

void test3() {
  std::vector<std::vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  int value = 1;
  assert(findSolution1(matrix, value));
  assert(findSolution2(matrix, value));
}

void test4() {
  std::vector<std::vector<int>> matrix{
      {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
  int value = 15;
  assert(findSolution1(matrix, value));
  assert(findSolution2(matrix, value));
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
