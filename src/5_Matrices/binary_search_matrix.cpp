/*
 * Matrix Binary Search
 *
 * This program searches for a specified value within a 2D matrix, where it is assumed
 * that each row and each column are sorted in ascending order. The function `contains`
 * treats the matrix as a flattened sorted array and performs a binary search to locate
 * the target value. It returns true if the value is found and false otherwise.
 *
 * ASCII Illustration of the Matrix:
 *       +----+----+----+
 *       |  1 |  3 |  5 |
 *       +----+----+----+
 *       |  7 |  9 | 11 |
 *       +----+----+----+
 *       | 13 | 15 | 17 |
 *       +----+----+----+
 *
 * Example:
 * Input: Matrix = {{1,3,5}, {7,9,11}, {13,15,17}}, Target = 7
 * Output: true
 * Explanation: The value 7 is found in the matrix.
 */

#include <cassert>
#include <vector>

// Binary search by treating the 2D matrix as a flattened sorted array.
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

// Test cases for correctness
void test() {
    std::vector<std::vector<int>> matrix{{1, 3, 5},
                                           {7, 9, 11},
                                           {13, 15, 17}};
    
    // Value exists in the matrix
    assert(contains(matrix, 7) == true);
    // Value at the beginning of the matrix
    assert(contains(matrix, 1) == true);
    // Value at the end of the matrix
    assert(contains(matrix, 17) == true);
    // Value does not exist in the matrix
    assert(contains(matrix, 6) == false);
}

int main() {
    test();
    return 0;
}
