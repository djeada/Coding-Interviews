#include <cstring>
#include <iostream>
#include <memory>
#include <string>

/**
 * This program demonstrates multiple ways of allocating memory for strings and
 * returning them.
 */

// Correct Traditional C Way
char *allocateMemoryC(const char *str) {
  char *pointer = (char *)malloc(strlen(str) + 1);
  strcpy(pointer, str);
  return pointer;
}

// Correct C++ Way using std::unique_ptr
std::unique_ptr<char[]> allocateMemoryUniquePtr(const std::string &str) {
  auto pointer = std::make_unique<char[]>(str.length() + 1);
  strcpy(pointer.get(), str.c_str());
  return pointer;
}

// Correct C++ Way using std::string
std::string allocateMemoryStdString(const std::string &str) { return str; }

// Incorrect Way - returning a pointer to a local array
char *allocateMemoryWrong() {
  char str[20] = "Hello world";
  return str; // This is wrong and leads to undefined behavior
}

int main() {
  // Correct Traditional C Way
  char *cPointer = allocateMemoryC("Hello my friend (C)");
  std::cout << "\n " << cPointer << " \n";
  free(cPointer); // Don't forget to free the memory

  // Correct C++ Way using std::unique_ptr
  auto uniquePointer = allocateMemoryUniquePtr("Hello my friend (unique_ptr)");
  std::cout << "\n " << uniquePointer.get() << " \n";
  // No need to free, unique_ptr will take care of it

  // Correct C++ Way using std::string
  auto str = allocateMemoryStdString("Hello my friend (std::string)");
  std::cout << "\n " << str << " \n";
  // No need to free, std::string manages memory automatically

  // Incorrect Way - demonstrating undefined behavior
  char *wrongPointer = allocateMemoryWrong();
  std::cout << "\n " << wrongPointer
            << " \n"; // This may print garbage or crash
  // No need to free, but this is still wrong and should not be done

  return 0;
}
