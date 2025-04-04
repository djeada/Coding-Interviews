# My Personal Notes on "Coding Interviews"

This repository contains **my personal notes, remarks, and attempts** at solving challenges inspired by (and sometimes directly taken from) Harry He's book, *Coding Interviews*. **These are not official or authoritative solutions**. Instead, they represent what I tried on my own while learning, and I encourage everyone to also attempt these or similar problems independently.

> **Important**: Some of the problems here do not appear in the book but felt related in scope, so I included them in my study process.

If you’re interested in the book itself, you can find it on Amazon [here](https://amzn.to/43AFzBh).

![Capture](https://user-images.githubusercontent.com/37275728/186154277-b2ef19e7-1d07-4e4f-8bb6-ba6887e05519.PNG)

## Why These Notes?

I aimed to modernize or expand on certain approaches while keeping these notes for my personal review:

1. **Error Handling:** Switched from error codes to exceptions for clarity.
2. **Input/Output:** Used `iostream` in C++ instead of `stdlib.h`.
3. **Testing:** Replaced traditional console testing with assertions.
4. **Data Structures:** Utilized vectors (instead of raw arrays) for more flexibility.
5. **Looping:** Preferred iterators over integer indexing where it made sense.
6. **Class Implementation:** Employed classes to encapsulate data, improving code organization.
7. **References:** Used references in place of pointers when possible.
8. **Functional Programming:** Incorporated lambdas for small, focused functionalities.
9. **Simplifying Data:** Leveraged STL pairs for quick two-value grouping.
10. **Type Deduction:** Used `auto` for cleaner, more modern C++ code.

## Scope and Limitations

- **Not all** book problems are covered.
- **Some** problems are my own or from similar resources (not found in the book).
- The solutions are **my personal attempts** and may not reflect the book’s exact methods.

---

## Arrays

| #   | Title                | Notes/Solution                                                                                                     |
| --- | -------------------- | ------------------------------------------------------------------------------------------------------------------- |
| 1   | Array rotation       | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/array_rotation.cpp)                      |
| 2   | Duplicates           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/duplicates.cpp)                         |
| 3   | Majority element     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/majority_element.cpp)                   |
| 4   | Merge arrays         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/merge_arrays.cpp)                       |
| 5   | Min number           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/min_number.cpp)                        |
| 6   | Permutations         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/permutations.cpp)                      |
| 7   | Reorder numbers      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/reorder_numbers.cpp)                   |

## Strings

| #   | Title                    | Notes/Solution                                                                                                     |
| --- | ------------------------ | ------------------------------------------------------------------------------------------------------------------- |
| 1   | Add numeric string       | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/add_numeric_string.cpp)                 |
| 2   | Allocate string          | [C](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/allocate_str.c)                           |
| 3   | Anagram                  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/anagram.cpp)                           |
| 4   | Combinations             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/combinations.cpp)                      |
| 5   | Delete char              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/delete_char.cpp)                       |
| 6   | Delete duplicate chars   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/delete_duplicate_chars.cpp)            |
| 7   | Edit distance            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/edit_distance.cpp)                     |
| 8   | First char appearing once | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/first_char_appearing_once.cpp)        |
| 9   | Numeric string           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/numeric_string.cpp)                    |
| 10  | Palindrome number        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/palindrome_number.cpp)                 |
| 11  | Permutations             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/permutations.cpp)                     |
| 12  | Regex                    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/regex.cpp)                             |
| 13  | Replace blanks           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/replace_blanks.cpp)                    |
| 14  | Reverse words in sentence| [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/reverse_words_in_sentence.cpp)         |
| 15  | String path              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/string_path.cpp)                       |

## Stack and Queue

| #   | Title             | Notes/Solution                                                                                                   |
| --- | ----------------- | ----------------------------------------------------------------------------------------------------------------- |
| 1   | Min in stack      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/min_in_stack.cpp)                 |
| 2   | Push pop order    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/stack_push_pop_order.cpp)         |
| 3   | Stream median     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/stream_median.cpp)                |

## Lists

| #   | Title                  | Notes/Solution                                                                                                   |
| --- | ---------------------- | ----------------------------------------------------------------------------------------------------------------- |
| 1   | Clone complex list     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/clone_complex_list.cpp)                |
| 2   | Delete duplicates      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/delete_duplicates.cpp)                 |
| 3   | Delete node            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/delete_node.cpp)                       |
| 4   | Kth node               | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/kth_node.cpp)                          |
| 5   | Loops                  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/loops.cpp)                             |
| 6   | Merge lists            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/merge.cpp)                             |
| 7   | Print reversely        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/print_reversely.cpp)                  |
| 8   | Reverse list           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/reverse_list.cpp)                     |
| 9   | Sort list              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/sort.cpp)                              |

## Matrices

| #   | Title                   | Notes/Solution                                                                                                         |
| --- | ----------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| 1   | Fibonacci               | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/fibonacci.cpp)                             |
| 2   | Partially sorted matrix | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/partially_sorted_matrix.cpp)              |
| 3   | Sorted matrix           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/sorted_matrix.cpp)                        |

## Classes

| #   | Title                | Notes/Solution                                                                                                    |
| --- | -------------------- | ------------------------------------------------------------------------------------------------------------------ |
| 1   | Arrow and dot        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/arrow_and_dot.cpp)                     |
| 2   | Assignment operator  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/assigment_operator.cpp)                |
| 3   | Objective C          | [C](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/objective_c.c)                           |

## Bit Operations

| #   | Title                    | Notes/Solution                                                                                                          |
| --- | ------------------------ | ------------------------------------------------------------------------------------------------------------------------ |
| 1   | Count ones              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/count_ones.cpp)                      |
| 2   | Modify numbers          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/modify_number.cpp)                   |
| 3   | Two missing numbers     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/two_missing_numbers.cpp)             |
| 4   | Uniquely occurring numbers | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/uniquely_occuring_numbers.cpp)   |

## Trees

| #   | Title                   | Notes/Solution                                                                                                     |
| --- | ----------------------- | ------------------------------------------------------------------------------------------------------------------- |
| 1   | Balance                 | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/balance.cpp)                             |
| 2   | Construct binary tree   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/construct_binary_tree.cpp)               |
| 3   | Convert to list         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/convert_to_list.cpp)                     |
| 4   | Depth                   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/depth.cpp)                               |
| 5   | Largest subtrees        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/largest_subtrees.cpp)                    |
| 6   | Lowest ancestor         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/lowest_ancestor.cpp)                     |
| 7   | Nodes at k distance     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/nodes_at_k_distance.cpp)                 |
| 8   | Path                    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/path.cpp)                                |
| 9   | Print levels            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/print_levels.cpp)                       |
| 10  | Print zigzag            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/print_zigzag.cpp)                       |

## Other

| #   | Title                    | Notes/Solution                                                                                                          |
| --- | ------------------------ | ------------------------------------------------------------------------------------------------------------------------ |
| 1   | Coin change              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/coin_change.cpp)                 |
| 2   | Eight queens             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/eight_queens.cpp)                |
| 3   | Greatest sum subarrays   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/greatest_sum_subarrays.cpp)      |
| 4   | K least numbers          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/k_least_numbers.cpp)             |

---

## Contributing

Feel free to open a pull request or an issue if you spot something that can be improved. Please remember:

- These notes are **personal remarks** and **not** a definitive guide.
- I strongly recommend practicing and testing your own approaches.

## License

[MIT](https://choosealicense.com/licenses/mit/)

---

> **Disclaimer**: These notes are solely **my personal study aids** and should not be treated as an official or comprehensive guide to *Coding Interviews*. Purchase the book for the full experience and complete problem statements. Happy coding and learning!
