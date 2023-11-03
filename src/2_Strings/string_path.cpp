/**
 * This program checks if a path exists in a matrix such that,
 * traversing from an initial point, the characters along the path form a given
 * string. It uses Depth First Search to explore the matrix for the path.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

bool isPathPresent(const std::vector<std::string> &matrix, int row, int col,
                   const std::string &str, int pathLength,
                   std::vector<std::vector<bool>> &visited) {
  if (pathLength == str.length())
    return true;

  bool pathExists = false;
  int rows = matrix.size();
  int cols = matrix[0].size();

  if (row >= 0 && row < rows && col >= 0 && col < cols &&
      matrix[row][col] == str[pathLength] && !visited[row][col]) {
    pathLength++;
    visited[row][col] = true;

    pathExists =
        isPathPresent(matrix, row, col - 1, str, pathLength, visited) ||
        isPathPresent(matrix, row - 1, col, str, pathLength, visited) ||
        isPathPresent(matrix, row, col + 1, str, pathLength, visited) ||
        isPathPresent(matrix, row + 1, col, str, pathLength, visited);

    if (!pathExists) {
      pathLength--;
      visited[row][col] = false;
    }
  }

  return pathExists;
}

bool hasPath(const std::vector<std::string> &matrix, const std::string &str) {
  if (matrix.empty() || matrix[0].empty() || str.empty())
    return false;

  int rows = matrix.size();
  int cols = matrix[0].size();
  std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
  int pathLength = 0;

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      if (isPathPresent(matrix, row, col, str, pathLength, visited))
        return true;
    }
  }

  return false;
}

void runTests() {
  assert(hasPath({"ABCE", "SFCS", "ADEE"}, "ABCCED"));
  assert(hasPath({"ABCE", "SFCS", "ADEE"}, "SEE"));
  assert(!hasPath({"ABCE", "SFCS", "ADEE"}, "ABCB"));
  assert(hasPath({"ABCEHJIG", "SFCSLOPQ", "ADEEMNOE", "ADIDEJFM", "VCEIFGGS"},
                 "SLHECCEIDEJFGGFIE"));

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
