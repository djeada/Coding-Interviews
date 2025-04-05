/*
 * ADDITION OF LARGE NUMBERS REPRESENTED AS STRINGS
 *
 * Given two large positive numbers represented as strings, add them together and
 * return their sum, also as a string. Numbers are too large to fit into standard integer types.
 *
 * Constraints:
 * - Each string represents a non-negative integer.
 * - Each string length can be from 1 to 10^5.
 * - Strings will contain digits only (0-9).
 *
 * Example Input/Output:
 * Input: num1 = "999", num2 = "3"
 * Output: "1002"
 * Explanation: 999 + 3 = 1002.
 */

#include <algorithm>
#include <cassert>
#include <string>
#include <iostream>

// Helper function to check if a string contains only digits
bool isDigitString(const std::string& s) {
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

// Optimal Solution
// Adds two numbers represented as strings, O(n) complexity
std::string optimalSolution(const std::string& num1, const std::string& num2) {
    std::string result;
    int carry = 0, i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Test cases for correctness
void test() {
    assert(optimalSolution("999", "3") == "1002");
    assert(optimalSolution("33", "9999") == "10032");
    assert(optimalSolution("3333333", "222") == "3333555");
    assert(optimalSolution("0", "0") == "0");

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
