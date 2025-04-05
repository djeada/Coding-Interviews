/*
 * FIND NUMBER COMPLEMENT
 *
 * Given a positive integer, this program finds its complement by flipping all bits
 * in its binary representation (ignoring leading zeros). For example, the complement
 * of 5 (binary: 101) is 2 (binary: 010).
 *
 * Three modern C++ solutions are provided:
 *
 * 1. Simple (Brute-force) Solution using string conversion:
 *    - Converts the integer to its binary string representation, flips each bit,
 *      then converts the flipped string back to an integer.
 *    - Complexity: O(b) where b is the number of bits.
 *
 * 2. Optimal (Efficient) Solution using Bitwise Manipulation:
 *    - Finds a mask with bits set to 1 for all positions of the original number.
 *    - Returns the complement using bitwise XOR.
 *    - Complexity: O(b) with constant extra space.
 *
 * 3. Additional Modern Alternative using std::bitset:
 *    - Uses std::bitset to represent the number in binary, flips the bits, and converts back.
 *    - Useful for educational purposes and clarity.
 *
 * ASCII Illustration:
 *
 *   Consider the number: 5
 *       Binary representation: 101
 *       Complement: 010
 *
 * Example Input/Output:
 * Input:  5
 * Output: 2
 * Explanation:
 * The binary representation of 5 is "101". Flipping the bits gives "010", which is 2 in decimal.
 */

#include <cassert>
#include <bitset>
#include <iostream>
#include <sstream>
#include <string>

// Simple (Brute-force) Solution using string conversion
int simpleSolution(int num) {
    std::string binary;
    int n = num;
    // Convert integer to binary string (least significant digit last)
    while (n > 0) {
        binary.insert(binary.begin(), (n & 1) ? '1' : '0');
        n >>= 1;
    }
    // Flip each bit in the binary string
    for (char &c : binary) {
        c = (c == '1') ? '0' : '1';
    }
    // Convert flipped binary string back to integer
    int complement = 0;
    for (char c : binary) {
        complement = (complement << 1) | (c - '0');
    }
    return complement;
}

// Optimal (Efficient) Solution using Bitwise Manipulation
int optimalSolution(int num) {
    // Create mask with the same number of bits as num
    int mask = 0;
    int temp = num;
    while (temp > 0) {
        mask = (mask << 1) | 1;
        temp >>= 1;
    }
    // XOR with mask flips the bits
    return num ^ mask;
}

// Additional Modern Alternative using std::bitset
int alternativeSolution(int num) {
    // Determine the number of bits in num
    int bits = 0;
    int temp = num;
    while (temp > 0) {
        ++bits;
        temp >>= 1;
    }
    std::bitset<32> bs(num);
    // Flip only the lower 'bits' bits
    for (int i = 0; i < bits; ++i)
        bs.flip(i);
    // Convert the flipped bits back to integer
    return static_cast<int>(bs.to_ulong() & ((1 << bits) - 1));
}

// Test cases for correctness
void test() {
    struct TestCase {
        int input;
        int expected;
    };
    TestCase testCases[] = {
        {5, 2},       // 5 (101) -> 2 (010)
        {1, 0},       // 1 (1) -> 0 (0)
        {10, 5},      // 10 (1010) -> 5 (0101)
        {0, 0},       // Edge case: 0 returns 0 (by definition)
        {7, 0}        // 7 (111) -> 0 (000)
    };

    for (const auto &tc : testCases) {
        int resSimple = simpleSolution(tc.input);
        int resOptimal = optimalSolution(tc.input);
        int resAlternative = alternativeSolution(tc.input);
        assert(resSimple == tc.expected);
        assert(resOptimal == tc.expected);
        assert(resAlternative == tc.expected);
    }
    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
