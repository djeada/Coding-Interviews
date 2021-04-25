#include <cassert>
#include <cstring>
#include <stack>

bool hasPathCore(char *matrix, int rows, int cols, int row, int col, char const *str,
                 int &pathLength, bool *visited) {
  if (str[pathLength] == '\0')
    return true;

  bool hasPath = false;
  if (row >= 0 && row < rows && col >= 0 && col < cols &&
      matrix[row * cols + col] == str[pathLength] &&
      !visited[row * cols + col]) {
    ++pathLength;
    visited[row * cols + col] = true;

    hasPath =
        hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength,
                    visited) ||
        hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength,
                    visited) ||
        hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength,
                    visited) ||
        hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited);

    if (!hasPath) {
      --pathLength;
      visited[row * cols + col] = false;
    }
  }

  return hasPath;
}

bool hasPath(char *matrix, int rows, int cols, char const *str) {
  if (matrix == NULL || rows < 1 || cols < 1 || str == NULL)
    return false;

  bool *visited = new bool[rows * cols];
  memset(visited, 0, rows * cols);

  int pathLength = 0;
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited))
        return true;
    }
  }

  delete[] visited;

  return false;
}

// ABCE
// SFCS
// ADEE

// ABCCED
void test1() {
  char matrix[] = "ABCESFCSADEE";
  char const *str = "ABCCED";
  int rows = 3;
  int cols = 4;
  assert(hasPath(matrix, rows, cols, str));
}

// ABCE
// SFCS
// ADEE

// SEE
void test2() {
  char matrix[] = "ABCESFCSADEE";
  char const *str = "SEE";
  int rows = 3;
  int cols = 4;
  assert(hasPath(matrix, rows, cols, str));
}

// ABCE
// SFCS
// ADEE

// ABCB
void test3() {
  char matrix[] = "ABCESFCSADEE";
  char const *str = "ABCB";
  int rows = 3;
  int cols = 4;
  assert(!hasPath(matrix, rows, cols, str));
}

// ABCEHJIG
// SFCSLOPQ
// ADEEMNOE
// ADIDEJFM
// VCEIFGGS

// SLHECCEIDEJFGGFIE
void test4() {
  char matrix[] = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
  char const *str = "SLHECCEIDEJFGGFIE";
  int rows = 5;
  int cols = 8;
  assert(hasPath(matrix, rows, cols, str));
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
