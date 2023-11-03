/**
 * This program finds all the solutions to the N-Queens puzzle for N=8 using
 * permutations. The N-Queens puzzle is the problem of placing eight chess
 * queens on an 8×8 chessboard so that no two queens threaten each other. The
 * solution requires that no two queens share the same row, column, or diagonal.
 * The program returns the total number of valid solutions.
 */

#include <cassert>
#include <functional>
#include <vector>

int countEightQueensSolutions() {
  std::vector<int> columnIndices{0, 1, 2, 3, 4, 5, 6, 7};
  int solutionCount = 0;

  // Lambda function to check if the current board arrangement is a valid
  // solution
  auto isValidBoard = [](const std::vector<int> &columnIndices, int length) {
    for (int i = 0; i < length; ++i) {
      for (int j = i + 1; j < length; ++j) {
        if ((i - j == columnIndices[i] - columnIndices[j]) ||
            (j - i == columnIndices[i] - columnIndices[j])) {
          return false;
        }
      }
    }
    return true;
  };

  // Recursive function to generate all permutations of the board arrangement
  // and check for valid solutions
  std::function<void(std::vector<int> &, int, int, int &)> generatePermutations;
  generatePermutations = [&](std::vector<int> &columnIndices, int length,
                             int index, int &solutionCount) -> void {
    if (index == length) {
      if (isValidBoard(columnIndices, length)) {
        solutionCount++;
      }
    } else {
      for (int i = index; i < length; ++i) {
        std::swap(columnIndices[i], columnIndices[index]);
        generatePermutations(columnIndices, length, index + 1, solutionCount);
        std::swap(columnIndices[index], columnIndices[i]);
      }
    }
  };

  generatePermutations(columnIndices, 8, 0, solutionCount);
  return solutionCount;
}

void testEightQueens() { assert(countEightQueensSolutions() == 92); }

int main() {
  testEightQueens();
  return 0;
}
