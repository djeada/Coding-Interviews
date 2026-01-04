/*
 * Task: Implement a safe copy assignment operator for a custom string class.
 *
 * Custom String Class with Assignment Operator
 *
 * Define a simple custom String class that manages its own dynamic memory.
 * It demonstrates the implementation of the copy assignment operator to
 * correctly handle resource management and avoid memory leaks. The class
 * includes:
 *   - Default, parameterized, and copy constructors.
 *   - Destructor to clean up allocated memory.
 *   - Copy assignment operator to enable safe assignment between String
 * objects.
 *
 * ASCII Illustration:
 *
 *      +---------------+
 *      |    String     |
 *      +---------------+
 *      | - data        |  ---> char array
 *      | - length      |  ---> length of the string
 *      +---------------+
 *
 * Example:
 *   String a("Hello");
 *   String b = a;  // Uses copy constructor.
 *   String c;
 *   c = a;         // Uses copy assignment operator.
 *
 * Expected Output:
 *   String a: Hello
 *   String b: Hello
 *   String c: Hello
 */

#include <cstring> // For standard strlen and strncpy
#include <iostream>
#include <string>

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
    std::cout << "[FAIL] " << label << " expected=\"" << expected
              << "\" got=\"" << got << "\"\n";
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
