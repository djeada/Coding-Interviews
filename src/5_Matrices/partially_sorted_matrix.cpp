#include <cassert>
#include <vector>

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

  int copyRow1 = row1, copyRow2 = row2;
  int copyCol1 = col1, copyCol2 = col2;

  int midRow = (row1 + row2) / 2;
  int midCol = (col1 + col2) / 2;

  while ((midRow != row1 || midCol != col1) &&
         (midRow != row2 || midCol != col2)) {

    if (value == matrix[midRow][midCol])
      return true;

    if (value < matrix[midRow][midCol]) {
      row2 = midRow;
      col2 = midCol;
    }

    else {
      row1 = midRow;
      col1 = midCol;
    }
    midRow = (row1 + row2) / 2;
    midCol = (col1 + col2) / 2;
  }

  bool found = false;
  if (midRow < rows - 1)
    found =
        findSolution1(matrix, value, midRow + 1, copyCol1, copyRow2, midCol);

  if (!found && midCol < cols - 1)
    found =
        findSolution1(matrix, value, copyRow1, midCol + 1, midRow, copyCol2);

  return found;
}

bool findSolution2(std::vector<std::vector<int>> &matrix, int value) {

  if (matrix.empty())
    return false;

  int rows = matrix.size();
  int cols = matrix[0].size();
  int row = 0;
  int col = cols - 1;
  bool found = false;

  while (row < rows && col >= 0) {
    if (matrix[row][col] == value) {
      found = true;
      break;
    }

    if (matrix[row][col] > value) {
      --col;
    } else {
      ++row;
    }
  }

  return found;
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
