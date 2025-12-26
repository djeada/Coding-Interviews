/*
 * STRING MEMORY ALLOCATION
 *
 * Demonstrate different approaches to allocate, manage, and return strings
 * in C and C++. Highlight both correct and incorrect techniques.
 *
 * Implement the following scenarios:
 *
 * 1. Traditional C-style allocation:
 *    - Use malloc + strcpy to allocate and return a string.
 *
 * 2. Modern C++ with RAII:
 *    - Use std::unique_ptr<char[]> to manage dynamic memory safely.
 *
 * 3. Standard C++ container:
 *    - Use std::string for safe and idiomatic memory management.
 *
 * 4. Incorrect usage (to illustrate a pitfall):
 *    - Return a pointer to a local stack-allocated buffer (leads to
 *      undefined behavior).
 *
 * Constraints:
 * - Focus on memory allocation and lifetime management, not algorithmic
 * complexity.
 * - Highlight why RAII (e.g., std::unique_ptr, std::string) should be
 *   preferred in modern C++.
 * - Demonstrate why returning pointers to stack memory is unsafe.
 *
 * Example Output:
 *   Hello my friend (C)
 *   Hello my friend (unique_ptr)
 *   Hello my friend (std::string)
 *   Undefined behavior (likely garbage or crash)
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

// Correct Traditional C Way - Manual memory management
char *allocateMemoryC(const char *str) {
  const char prefix[20] = "Greeting: ";
  char *ptr = (char *)malloc(sizeof(strlen(prefix) + strlen(str)) + 1);

  strcpy(ptr, prefix);
  strcpy(ptr, str);

  return ptr;
}

// Correct C++ Way using std::unique_ptr
std::unique_ptr<char[]> allocateMemoryUniquePtr(const std::string &str) {
  auto ptr = std::make_unique<char[]>(str.size() + 1);

  strcpy(ptr.get(), str.c_str());

  return ptr;
}

// Correct C++ Way using std::string
std::string allocateMemoryStdString(const std::string &str) { return str; }

// Incorrect Way - returning pointer to stack memory
char *allocateMemoryWrong() {
  char str[30] = "Hello from Wrong Approach!";
  std::cout << str << std::endl;
  return str;
}

int main() {
  // Correct Traditional C Way
  char *cPointer = allocateMemoryC("Hello my friend (C)");
  if (cPointer) {
    std::cout << "\n " << cPointer << " \n";
    free(cPointer); // Important: free manually allocated memory
  }

  // Correct C++ Way using std::unique_ptr
  auto uniquePointer = allocateMemoryUniquePtr("Hello my friend (unique_ptr)");
  std::cout << "\n " << uniquePointer.get() << " \n";
  // Memory automatically managed

  // Correct C++ Way using std::string
  std::string str = allocateMemoryStdString("Hello my friend (std::string)");
  std::cout << "\n " << str << " \n";

  // Incorrect usage demonstration
  char *wrongPointer = allocateMemoryWrong();
  std::cout << "\n " << wrongPointer << " \n"; // ❗ May crash or print garbage

  std::cout << "Hello!" << std::endl;
  return 0;
}
