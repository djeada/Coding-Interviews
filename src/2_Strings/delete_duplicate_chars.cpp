/*
* REMOVE DUPLICATE CHARACTERS FROM STRING
*
* Given a string s, remove all duplicate characters while preserving 
* the order of their first occurrences.
*
* Return the resulting string.
*
* Constraints:
* - 0 <= s.length <= 10^5
* - s may consist of letters, digits, spaces, or special characters.
* - Try to achieve an efficient solution with O(n) time complexity 
*   and minimal extra space.
*
* Example 1:
* Input:  
*   s = "google"
* Output:  
*   "gole"
* Explanation:  
*   The duplicates 'o' and 'g' are removed. Only the first appearance 
*   of each character is kept.
*
* Example 2:
* Input:  
*   s = "abcabc"
* Output:  
*   "abc"
*
* Example 3:
* Input:  
*   s = "aaaa"
* Output:  
*   "a"
*/

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

// 1) Simple (Brute-force) Solution
// Time Complexity: O(n²)
std::string simpleSolution(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (result.find(c) == std::string::npos) {
            result.push_back(c);
        }
    }
    return result;
}

// 2) Optimal (Efficient) Solution using unordered_set
// Time Complexity: Average O(n)
std::string optimalSolution(const std::string& input) {
    std::string result;
    result.reserve(input.size());
    std::unordered_set<char> seen;
    for (char c : input) {
        if (seen.insert(c).second) {
            result.push_back(c);
        }
    }
    return result;
}

// 3) Alternative Solution using std::remove_if
std::string alternativeSolution(const std::string& input) {
    std::string result = input;
    std::unordered_set<char> seen;
    auto new_end = std::remove_if(result.begin(), result.end(),
        [&seen](char c) {
            if (seen.count(c)) return true;
            seen.insert(c);
            return false;
        });
    result.erase(new_end, result.end());
    return result;
}

// 4) In-place, iterator-based; O(n) time, O(1) extra space (32-byte bitmap).
// Mutates the input string directly.
void inplaceSolution(std::string& s) {
    std::bitset<256> seen;   // tracks byte values 0..255
    auto writer = s.begin(); // where we write the next unique char

    for (auto it = s.begin(); it != s.end(); ++it) {
        unsigned char uc = static_cast<unsigned char>(*it); // avoid signed-char issues
        if (!seen.test(uc)) {
            seen.set(uc);
            *writer++ = *it;
        }
    }

    // Trim the leftover duplicate tail
    s.erase(writer, s.end());
}


// -------------------- Tests --------------------

std::string inplaceAdapter(const std::string& input) {
    std::string s = input;
    inplaceSolution(s);
    return s;
}

struct TestCase {
    std::string name;
    std::string input;
    std::string expected;
};

using SolverFn = std::string(*)(const std::string&);

// Reference expected: byte-wise first-occurrence keeping (ASCII/byte-oriented)
std::string referenceExpected(const std::string& s) {
    std::bitset<256> seen;
    std::string out;
    out.reserve(s.size());
    for (unsigned char uc : s) {
        if (!seen.test(uc)) {
            seen.set(uc);
            out.push_back(static_cast<char>(uc));
        }
    }
    return out;
}

struct SuiteResult {
    std::string solverName;
    size_t total = 0;
    size_t passed = 0;
};

void runSuite(const std::string& solverName, SolverFn solver,
              const std::vector<TestCase>& cases,
              SuiteResult& outResult) {
    std::cout << "=== Testing " << solverName << " ===\n";
    outResult.solverName = solverName;
    size_t passed = 0;
    size_t total = 0;

    for (const auto& tc : cases) {
        ++total;

        const std::string expected =
            tc.expected.empty() ? referenceExpected(tc.input) : tc.expected;

        auto t0 = std::chrono::high_resolution_clock::now();
        std::string got = solver(tc.input);
        auto t1 = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

        bool pass = (got == expected);
        if (pass) ++passed;

        std::cout
            << "  [" << (pass ? "PASS" : "FAIL") << "] "
            << std::left << std::setw(24) << tc.name
            << " expected=\"" << expected << "\""
            << ", got=\"" << got << "\""
            << " (" << us << " µs)\n";
    }

    outResult.total = total;
    outResult.passed = passed;

    std::cout << "Summary for " << solverName << ": "
              << passed << "/" << total << " passed\n\n";
}

// Build a long stress string of length ~100k with repeating alphabet
std::string makeLongStressInput(size_t n = 100000) {
    std::string s;
    s.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        s.push_back(static_cast<char>('a' + (i % 26)));
    }
    return s;
}

// Randomized cases (deterministic seed). Alphabet is bytes 32..126 to keep printable.
std::vector<TestCase> makeRandomCases(size_t count, size_t minLen, size_t maxLen, uint32_t seed = 123456789) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<size_t> lenDist(minLen, maxLen);
    std::uniform_int_distribution<int> chDist(32, 126);

    std::vector<TestCase> v;
    v.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        size_t L = lenDist(rng);
        std::string s;
        s.resize(L);
        for (size_t j = 0; j < L; ++j) {
            s[j] = static_cast<char>(chDist(rng));
        }
        v.push_back({ "Random #" + std::to_string(i+1), s, "" }); // expected computed via reference
    }
    return v;
}

// -------------------- Main --------------------

int main() {
    // Curated deterministic cases
    std::vector<TestCase> coreCases = {
        { "Basic repeat",        "google",                     "gole" },
        { "All same",            "aaaaaaaaaaaaaaaaaaaaa",      "a"    },
        { "Empty string",        "",                            ""    },
        { "Mixed repeats",       "abcacbbacbcacabcba",         "abc" },
        { "All unique",          "abcdef",                     "abcdef" },
        { "Digits mixed",        "1122334455",                 "12345" },
        { "Spaces kept",         "a a a  b b   c",             "a bc" }, // first space kept
        { "Punctuation",         "!!!??!!??..,,",              "!?.,," }, // first of each punctuation
        { "Case sensitive",      "AaAaBbBb",                   "AaBb" },
        { "Symbols",             "@@##$$%%^^&&**(()))",        "@#$%^&*()" },
        { "Long stress (100k)",  makeLongStressInput(),        "abcdefghijklmnopqrstuvwxyz" }
    };

    // Random property tests (expected computed via reference)
    auto randomSmall  = makeRandomCases(10, 0,   32, 0xBEEF1234);
    auto randomMedium = makeRandomCases(10, 33, 256, 0xDEADBEEF);

    std::vector<TestCase> allCases = coreCases;
    allCases.insert(allCases.end(), randomSmall.begin(), randomSmall.end());
    allCases.insert(allCases.end(), randomMedium.begin(), randomMedium.end());

    // Solutions under test
    struct SolverEntry { const char* name; SolverFn fn; } solvers[] = {
        { "simpleSolution (O(n^2))",    &simpleSolution    },
        { "optimalSolution (hash)",     &optimalSolution   },
        { "alternativeSolution (erase)",&alternativeSolution },
        { "inplaceSolution (iterator)", &inplaceAdapter    }, // adapter wraps the in-place ref version
    };

    std::vector<SuiteResult> results;
    results.reserve(std::size(solvers));

    // Run suites
    for (const auto& s : solvers) {
        SuiteResult r;
        runSuite(s.name, s.fn, allCases, r);
        results.push_back(r);
    }

    // Final summary (and return non-zero if any failures)
    bool allPassed = true;
    std::cout << "=== Overall Summary ===\n";
    for (const auto& r : results) {
        std::cout << "  " << std::left << std::setw(28) << r.solverName
                  << " -> " << r.passed << "/" << r.total << " passed\n";
        allPassed = allPassed && (r.passed == r.total);
    }

    if (!allPassed) {
        std::cerr << "\nOne or more tests failed.\n";
        return 1;
    }

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
