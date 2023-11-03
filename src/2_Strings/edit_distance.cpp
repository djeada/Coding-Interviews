/**
 * This program calculates the Levenshtein distance (edit distance) between two
 * strings. The edit distance is the minimum number of operations (insertions,
 * deletions, substitutions) required to transform one string into another.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

/**
 * Helper function to compute the Levenshtein distance.
 * @param str1: The first string.
 * @param str2: The second string.
 * @param distances: A 2D vector to store intermediate distances.
 * @param len1: The length of the first string.
 * @param len2: The length of the second string.
 * @return: The Levenshtein distance between str1 and str2.
 */
int computeEditDistance(const std::string &str1, const std::string &str2,
                        std::vector<std::vector<int>> &distances, int len1,
                        int len2) {
  for (int i = 0; i <= len2; ++i)
    distances[i][0] = i;

  for (int j = 0; j <= len1; ++j)
    distances[0][j] = j;

  for (int i = 1; i <= len2; ++i) {
    for (int j = 1; j <= len1; ++j) {
      if (str1[j - 1] == str2[i - 1])
        distances[i][j] = distances[i - 1][j - 1];
      else {
        distances[i][j] =
            std::min({distances[i][j - 1] + 1, distances[i - 1][j] + 1,
                      distances[i - 1][j - 1] + 1});
      }
    }
  }
  return distances[len2][len1];
}

/**
 * Calculates the Levenshtein distance between two strings.
 * @param str1: The first string.
 * @param str2: The second string.
 * @return: The Levenshtein distance between str1 and str2.
 */
int getEditDistance(const std::string &str1, const std::string &str2) {
  int len1 = str1.length();
  int len2 = str2.length();
  std::vector<std::vector<int>> distances(len2 + 1,
                                          std::vector<int>(len1 + 1, 0));
  return computeEditDistance(str1, str2, distances, len1, len2);
}

/**
 * Run tests to validate the getEditDistance function.
 */
void runTests() {
  // Test Case 1
  assert(getEditDistance("kitten", "kitten") == 0);

  // Test Case 2
  assert(getEditDistance("bob", "bub") == 1);

  // Test Case 3
  assert(getEditDistance("ROBOT", "robot") == 5);

  // Test Case 4
  assert(getEditDistance("church", "ChUrCh") == 3);

  std::cout << "All tests passed!\n";
}

int main() {
  runTests();
  return 0;
}
