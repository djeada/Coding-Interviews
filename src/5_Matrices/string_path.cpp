/*
 * PATH SEARCH IN MATRIX FOR A STRING
 *
 * This program determines whether there exists a path in a 2D matrix such that,
 * starting from any cell, moving horizontally or vertically (up, down, left, right)
 * and without revisiting cells, the characters along the path form a specified string.
 *
 * Three solutions are provided:
 *
 * 1. Simple Solution:
 *    - Uses a recursive Depth-First Search (DFS) with a helper function.
 *    - Explores every possible path and backtracks upon dead ends.
 *
 * 2. Optimal (Efficient) Solution:
 *    - Uses a lambda function to encapsulate the recursive DFS logic.
 *    - This version reduces the scope of helper functions and leverages modern C++ features.
 *
 * 3. Alternative Solution:
 *    - Implements DFS iteratively using an explicit stack.
 *    - Although less memory efficient due to copying the visited state, it demonstrates
 *      how recursion can be converted to an iterative process.
 *
 * ASCII Illustration:
 *
 *          Matrix:
 *        +---+---+---+
 *        | A | B | C |
 *        +---+---+---+
 *        | D | E | F |
 *        +---+---+---+
 *        | G | H | I |
 *        +---+---+---+
 *
 *      Target String: "ABE"
 *      One valid path: (0,0) -> (0,1) -> (1,1)
 *
 * Example Input/Output:
 * Input:  Matrix = {"ABC", "DEF", "GHI"}, Target = "ABE"
 * Output: true
 *
 * Explanation:
 * The path starting at 'A' at (0,0), moving right to 'B' at (0,1), and then down to 'E'
 * at (1,1) forms the target string "ABE".
 */

#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <functional>

// ---------------- Simple Solution ----------------
// Recursive DFS helper function.
bool dfsSimple(const std::vector<std::string>& matrix, int row, int col,
               const std::string& target, int index,
               std::vector<std::vector<bool>>& visited) {
    if (index == target.size()) return true;
    int rows = matrix.size();
    int cols = matrix[0].size();

    if (row < 0 || row >= rows || col < 0 || col >= cols ||
        visited[row][col] || matrix[row][col] != target[index])
        return false;

    visited[row][col] = true;
    bool found = dfsSimple(matrix, row, col - 1, target, index + 1, visited) ||
                 dfsSimple(matrix, row - 1, col, target, index + 1, visited) ||
                 dfsSimple(matrix, row, col + 1, target, index + 1, visited) ||
                 dfsSimple(matrix, row + 1, col, target, index + 1, visited);
    if (!found) {
        visited[row][col] = false;
    }
    return found;
}

bool simpleSolution(const std::vector<std::string>& matrix, const std::string& target) {
    if (matrix.empty() || matrix[0].empty() || target.empty())
        return false;
    int rows = matrix.size(), cols = matrix[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            if (dfsSimple(matrix, row, col, target, 0, visited))
                return true;
    return false;
}

// ---------------- Optimal (Efficient) Solution ----------------
// Uses a lambda for recursive DFS.
bool optimalSolution(const std::vector<std::string>& matrix, const std::string& target) {
    if (matrix.empty() || matrix[0].empty() || target.empty())
        return false;
    int rows = matrix.size(), cols = matrix[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // Lambda function for DFS.
    std::function<bool(int, int, int)> dfs = [&](int row, int col, int index) -> bool {
        if (index == target.size()) return true;
        if (row < 0 || row >= rows || col < 0 || col >= cols ||
            visited[row][col] || matrix[row][col] != target[index])
            return false;
        visited[row][col] = true;
        bool found = dfs(row, col - 1, index + 1) ||
                     dfs(row - 1, col, index + 1) ||
                     dfs(row, col + 1, index + 1) ||
                     dfs(row + 1, col, index + 1);
        if (!found)
            visited[row][col] = false;
        return found;
    };

    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            if (dfs(row, col, 0))
                return true;
    return false;
}

// ---------------- Alternative Solution ----------------
// Iterative DFS using an explicit stack. Note: This approach copies the visited state
// for each new path, which is less efficient but illustrates an iterative approach.
struct Node {
    int row, col, index;
    std::vector<std::vector<bool>> visited;
};

bool alternativeSolution(const std::vector<std::string>& matrix, const std::string& target) {
    if (matrix.empty() || matrix[0].empty() || target.empty())
        return false;
    int rows = matrix.size(), cols = matrix[0].size();

    for (int startRow = 0; startRow < rows; ++startRow) {
        for (int startCol = 0; startCol < cols; ++startCol) {
            if (matrix[startRow][startCol] != target[0])
                continue;
            std::stack<Node> stack;
            std::vector<std::vector<bool>> initVisited(rows, std::vector<bool>(cols, false));
            initVisited[startRow][startCol] = true;
            stack.push({startRow, startCol, 0, initVisited});

            while (!stack.empty()) {
                Node node = stack.top();
                stack.pop();

                if (node.index == target.size() - 1)
                    return true;

                int nextIndex = node.index + 1;
                // Directions: left, up, right, down.
                int dr[4] = {0, -1, 0, 1};
                int dc[4] = {-1, 0, 1, 0};

                for (int d = 0; d < 4; ++d) {
                    int newRow = node.row + dr[d];
                    int newCol = node.col + dc[d];

                    if (newRow >= 0 && newRow < rows &&
                        newCol >= 0 && newCol < cols &&
                        !node.visited[newRow][newCol] &&
                        matrix[newRow][newCol] == target[nextIndex]) {
                        auto newVisited = node.visited;
                        newVisited[newRow][newCol] = true;
                        stack.push({newRow, newCol, nextIndex, newVisited});
                    }
                }
            }
        }
    }
    return false;
}

// ---------------- Test Cases ----------------
void test() {
    {
        std::vector<std::string> matrix = {"ABCE", "SFCS", "ADEE"};
        assert(simpleSolution(matrix, "ABCCED"));
        assert(optimalSolution(matrix, "ABCCED"));
        assert(alternativeSolution(matrix, "ABCCED"));
    }
    {
        std::vector<std::string> matrix = {"ABCE", "SFCS", "ADEE"};
        assert(simpleSolution(matrix, "SEE"));
        assert(optimalSolution(matrix, "SEE"));
        assert(alternativeSolution(matrix, "SEE"));
    }
    {
        std::vector<std::string> matrix = {"ABCE", "SFCS", "ADEE"};
        assert(!simpleSolution(matrix, "ABCB"));
        assert(!optimalSolution(matrix, "ABCB"));
        assert(!alternativeSolution(matrix, "ABCB"));
    }
    {
        std::vector<std::string> matrix = {"ABCEHJIG", "SFCSLOPQ", "ADEEMNOE", "ADIDEJFM", "VCEIFGGS"};
        assert(simpleSolution(matrix, "SLHECCEIDEJFGGFIE"));
        assert(optimalSolution(matrix, "SLHECCEIDEJFGGFIE"));
        assert(alternativeSolution(matrix, "SLHECCEIDEJFGGFIE"));
    }
    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
