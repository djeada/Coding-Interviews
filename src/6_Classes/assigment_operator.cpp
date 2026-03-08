/*
 * Task: Implement a safe copy assignment operator for a custom string class.
 *
 * CUSTOM STRING COPY ASSIGNMENT
 *
 * Problem:
 * Implement a `String` class that manages a dynamic char buffer and supports
 * safe copy assignment. Assignment must correctly handle self-assignment and
 * prevent memory leaks or dangling pointers.
 *
 * Constraints:
 * - Manage memory manually using `new[]` and `delete[]`.
 * - Preserve value semantics for copy constructor and copy assignment.
 * - After assignment, both objects should hold independent copies.
 *
 * Example:
 * Input: a = "Hello", b = a, c = "", then c = a
 * Output: a == "Hello", b == "Hello", c == "Hello"
 */

#include <cstring> // For standard strlen and strncpy
#include <iostream>
#include <string>

class String {
  char *data;
  int length;

public:
  // Default Constructor
  String() : data(new char[1]{'\0'}), length(0) {}

  // Parameterized Constructor
  String(const char *pData) {
    length = std::strlen(pData);
    data = new char[length + 1]; // +1 for null terminator
    std::strncpy(data, pData, length);
    data[length] = '\0'; // Null-terminate the string
  }

  // Copy Constructor
  String(const String &str)
      : length(str.length), data(new char[str.length + 1]) {
    std::strncpy(data, str.data, length);
    data[length] = '\0'; // Null-terminate the string
  }

  // Destructor
  ~String() { delete[] data; }

  // Copy Assignment Operator
  String &operator=(const String &str) {
    if (this != &str) { // Check for self-assignment
      delete[] data;    // Deallocate existing memory
      length = str.length;
      data = new char[length + 1];
      std::strncpy(data, str.data, length);
      data[length] = '\0'; // Null-terminate the string
    }
    return *this;
  }

  // Function to return size of the string
  int size() const { return length; }

  const char *c_str() const { return data; }

  // Overloading stream insertion operator to print the String object
  friend std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.data;
    return os;
  }
};

namespace {
struct TestRunner {
  int total = 0;
  int failed = 0;

  void expectEqual(const std::string &got, const std::string &expected,
                   const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=\"" << expected << "\" got=\""
              << got << "\"\n";
  }

  void expectEqual(int got, int expected, const std::string &label) {
    ++total;
    if (got == expected) {
      std::cout << "[PASS] " << label << "\n";
      return;
    }
    ++failed;
    std::cout << "[FAIL] " << label << " expected=" << expected
              << " got=" << got << "\n";
  }

  void summary() const {
    std::cout << "Tests: " << total - failed << " passed, " << failed
              << " failed, " << total << " total\n";
  }
};
} // namespace

int main() {
  TestRunner runner;
  String a("Hello");
  String b = a; // Copy constructor
  String c;
  c = a; // Copy assignment operator
  c = c; // Self-assignment

  std::cout << "String a: " << a << std::endl;
  std::cout << "String b: " << b << std::endl;
  std::cout << "String c: " << c << std::endl;

  runner.expectEqual(std::string(a.c_str()), "Hello", "a content");
  runner.expectEqual(std::string(b.c_str()), "Hello", "b copy content");
  runner.expectEqual(std::string(c.c_str()), "Hello", "c assigned content");
  runner.expectEqual(a.size(), 5, "a size");
  runner.expectEqual(b.size(), 5, "b size");
  runner.expectEqual(c.size(), 5, "c size");
  runner.summary();
  return 0;
}
