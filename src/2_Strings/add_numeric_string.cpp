/**
 * This program adds two large positive numbers represented as strings.
 */
#include <algorithm> // For std::reverse
#include <cassert>
#include <string>

// Checks if the input strings are valid numbers and if the sum string is empty.
bool isValidInput(const std::string &num1, const std::string &num2,
                  const std::string &sum) {
  if (num1.empty() || num2.empty() || !sum.empty())
    return false;

  return all_of(num1.begin(), num1.end(), ::isdigit) &&
         all_of(num2.begin(), num2.end(), ::isdigit);
}

// Adds two numbers represented as strings.
bool addStrings(const std::string &num1, const std::string &num2,
                std::string &sum) {
  if (!isValidInput(num1, num2, sum))
    return false;

  int carry = 0, i = num1.size() - 1, j = num2.size() - 1;
  while (i >= 0 || j >= 0 || carry) {
    int digit1 = i >= 0 ? num1[i--] - '0' : 0;
    int digit2 = j >= 0 ? num2[j--] - '0' : 0;

    int sumDigit = digit1 + digit2 + carry;
    carry = sumDigit / 10;
    sumDigit %= 10;

    sum.push_back(sumDigit + '0');
  }

  std::reverse(sum.begin(), sum.end());
  return true;
}

void testAddStrings() {
  // Test Case 1
  {
    std::string num1 = "999", num2 = "3", sum, result = "1002";
    assert(addStrings(num1, num2, sum) && sum == result);
  }

  // Test Case 2
  {
    std::string num1 = "33", num2 = "9999", sum, result = "10032";
    assert(addStrings(num1, num2, sum) && sum == result);
  }

  // Test Case 3
  {
    std::string num1 = "3333333", num2 = "222", sum, result = "3333555";
    assert(addStrings(num1, num2, sum) && sum == result);
  }

  // Test Case 4 (Invalid Input)
  {
    std::string num1 = "33abc33", num2 = "222", sum, result = "";
    assert(!addStrings(num1, num2, sum) && sum == result);
  }
}

int main() {
  testAddStrings();
  return 0;
}
