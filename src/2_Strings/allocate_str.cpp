/*
 * STRING MEMORY ALLOCATION - C & C++ COMPATIBLE TECHNIQUES
 *
 * This program demonstrates various correct (and one incorrect) ways to allocate and manage
 * memory for strings in a C/C++ environment. These methods showcase how strings can be
 * handled safely across C and C++ paradigms.
 *
 * Scenarios covered:
 * 1. Traditional C-style allocation using malloc + strcpy
 * 2. Modern C++ using std::unique_ptr for RAII
 * 3. Using std::string (C++ standard container)
 * 4. Incorrect usage: returning a pointer to local stack memory
 *
 * Example Output:
 * Hello my friend (C)
 * Hello my friend (unique_ptr)
 * Hello my friend (std::string)
 * Undefined behavior (likely garbage or crash)
 */

#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>

// Correct Traditional C Way - Manual memory management
char* allocateMemoryC(const char* str) {
    char* pointer = static_cast<char*>(malloc(strlen(str) + 1));
    if (pointer) {
        strcpy(pointer, str);
    }
    return pointer;
}

// Correct C++ Way using std::unique_ptr
std::unique_ptr<char[]> allocateMemoryUniquePtr(const std::string& str) {
    auto pointer = std::make_unique<char[]>(str.length() + 1);
    strcpy(pointer.get(), str.c_str());
    return pointer;
}

// Correct C++ Way using std::string
std::string allocateMemoryStdString(const std::string& str) {
    return str; // Simple copy constructor
}

// Incorrect Way - returning pointer to stack memory
char* allocateMemoryWrong() {
    char str[20] = "Hello world";
    return str; // ❌ Undefined behavior: stack-allocated memory
}

int main() {
    // Correct Traditional C Way
    char* cPointer = allocateMemoryC("Hello my friend (C)");
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
    // char* wrongPointer = allocateMemoryWrong();
    // std::cout << "\n " << wrongPointer << " \n"; // ❗ May crash or print garbage

    return 0;
}
