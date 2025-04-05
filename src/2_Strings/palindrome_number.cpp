/*
 * PALINDROME INTEGER CHECK
 *
 * Given an integer, determine whether it is a palindrome. An integer is a palindrome if it reads
 * the same backward as forward.
 *
 * This task provides two approaches:
 * 1. Convert the integer to a string and compare characters.
 * 2. Reverse the integer mathematically and compare with the original.
 *
 * Constraints:
 * - The integer can be positive, zero, or negative.
 * - Negative integers are not considered palindromes.
 *
 * Example Input/Output:
 * Input: 121
 * Output: true
 *
 * Input: -121
 * Output: false
 * Explanation: Negative numbers are not palindromes.
 */

#include <cassert>
#include <iostream>
#include <string>

// Simple Solution (Convert integer to string)
// Complexity: O(N), where N is the number of digits.
bool simpleSolution(int x) {
    if (x < 0) return false;

    std::string s = std::to_string(x);
    int n = s.size();
    for (int i = 0; i < n / 2; ++i)
        if (s[i] != s[n - i - 1])
            return false;

    return true;
}

// Optimal Solution (Reverse integer mathematically)
// Complexity: O(N), avoids extra space for string conversion.
bool optimalSolution(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;

    int reversed = 0;
    int original = x;

    while (x > 0) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }

    return reversed == original;
}

// Test cases for correctness
void test() {
    assert(simpleSolution(121) && optimalSolution(121));
    assert(!simpleSolution(-121) && !optimalSolution(-121));
    assert(!simpleSolution(1234) && !optimalSolution(1234));
    assert(simpleSolution(1331) && optimalSolution(1331));
    assert(simpleSolution(0) && optimalSolution(0));

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
