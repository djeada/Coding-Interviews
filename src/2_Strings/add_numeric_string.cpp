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
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Helper: Check if a string contains only digits
bool isDigitString(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), [](unsigned char c) {
        return std::isdigit(c);
    });
}

// Adds two non-negative integers represented as strings
std::string addStrings(const std::string& num1, const std::string& num2) {
    if (!isDigitString(num1) || !isDigitString(num2)) {
        throw std::invalid_argument("Inputs must be digit strings.");
    }

    std::string result;
    result.reserve(std::max(num1.size(), num2.size()) + 1); // preallocate

    int carry = 0;
    int i = static_cast<int>(num1.size()) - 1;
    int j = static_cast<int>(num2.size()) - 1;

    while (i >= 0 || j >= 0 || carry) {
        int d1 = (i >= 0) ? num1[i--] - '0' : 0;
        int d2 = (j >= 0) ? num2[j--] - '0' : 0;

        int sum = d1 + d2 + carry;
        carry = sum / 10;

        result.push_back(static_cast<char>('0' + (sum % 10)));
    }

    std::reverse(result.begin(), result.end());
    return result;
}

struct TestCase {
    std::string name;
    std::string num1, num2;
    bool expectException;
    std::string expected;
};

void testOptimalSolution(const std::vector<TestCase>& cases) {
    std::cout << "=== Testing optimalSolution ===\n";
    for (const auto& tc : cases) {
        bool passed = false;
        try {
            std::string got = optimalSolution(tc.num1, tc.num2);
            if (!tc.expectException && got == tc.expected) {
                passed = true;
            }
        } catch (const std::invalid_argument&) {
            if (tc.expectException) passed = true;
        }
        std::cout << tc.name
                  << " -> " << (passed ? "PASS" : "FAIL") << "\n";
        assert(passed);
    }
    std::cout << "\n";
}

int main() {
    std::vector<TestCase> cases = {
        { "Simple carry",      "999",   "3",     false, "1002"   },
        { "Different lengths", "33",    "9999",  false, "10032"  },
        { "No carry",          "123",   "456",   false, "579"    },
        { "Zero + Zero",       "0",     "0",     false, "0"      },
        { "Leading zeros",     "001",   "099",   false, "100"    },
        { "Invalid char num1", "12a3",  "456",   true,  ""       },
        { "Invalid char num2", "123",   "4b6",   true,  ""       }
    };

    testOptimalSolution(cases);
    std::cout << "All tests passed successfully!\n";
    return 0;
}
