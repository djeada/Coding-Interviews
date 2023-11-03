#include <cstring> // For standard strlen and strncpy
#include <iostream>

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
    if (this != &str) {
      delete[] data; // Deallocate existing memory
      length = str.length;
      data = new char[length + 1];
      std::strncpy(data, str.data, length);
      data[length] = '\0'; // Null-terminate the string
    }
    return *this;
  }

  // Function to return size of the string
  int size() const { return length; }

  // Overloading stream insertion operator to print the String object
  friend std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.data;
    return os;
  }
};

int main() {
  String a("Hello");
  String b = a;
  String c;

  std::cout << "String a: " << a << std::endl;
  std::cout << "String b: " << b << std::endl;
  std::cout << "String c: " << c << std::endl;

  return 0;
}
