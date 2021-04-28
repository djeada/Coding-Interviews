#include <iostream>

int strlen(const char *ptr) {
  int len = 0;
  auto p = ptr;
  while (*p != '\0') {
    len++;
    p++;
  }
  return len;
}

void strncpy(char *ptr_dest, const char *ptr_src, int n) {
  for (int i = 0; i < n; i++) {
    ptr_dest[i] = ptr_src[i];
  }
}

class String {
  char *data;
  int length;

public:
  String() {
    data = new char[100];
    length = strlen(data);
  }

  String(const char *pData) {
    length = strlen(pData);
    data = new char[length];
    strncpy(data, pData, length);
  }

  String(const String &str) {
    length = str.length;
    data = new char[length];
    strncpy(data, str.data, length);
  }

  ~String() { delete[] data; }

  String &operator=(const String &str) {
    if (this != &str) {
      String strTemp(str);

      char *pTemp = strTemp.data;
      strTemp.data = data;
      data = pTemp;
      delete[] pTemp;
    }
    return *this;
  }

  int size() const { return length; }
  friend std::ostream &operator<<(std::ostream &os, const String &s) {
    int length = s.size();
    for (int i = 0; i < length; i++) {
      os.put(s.data[i]);
    }
    return os;
  }
};

int main() {
  String a("Hello");
  String b = a;
  String c;

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;

  return 0;
}
