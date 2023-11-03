# Coding Interviews
This repository presents updated and modernized solutions to programming challenges found in Harry He's "Coding Interviews" book, which is a well-regarded resource for candidates preparing for coding interviews. The book can be purchased on Amazon [here](https://www.amazon.de/Coding-Interviews-Questions-Solutions-Programming/dp/1430247614).

![Capture](https://user-images.githubusercontent.com/37275728/186154277-b2ef19e7-1d07-4e4f-8bb6-ba6887e05519.PNG)

## Motivation

Here are some specific aspects I focused on while modernizing the solutions:

1. **Error Handling:** Replaced error codes with exceptions to handle errors more gracefully.
2. **Input/Output:** Used `iostream` instead of `stdlib.h` for standard input and output operations.
3. **Testing:** Swapped console tests with assertions to validate the solutions.
4. **Data Structures:** Preferred using vectors over bare arrays for flexibility.
5. **Looping:** Used iterators instead of integer counters for traversing collections.
6. **Class Implementation:** Implemented collections using classes to encapsulate data.
7. **References:** Used references instead of pointers where possible for safety and readability.
8. **Functional Programming:** Employed lambdas for implementing private functions.
9. **Simplifying Data:** Used STL pairs instead of creating custom structs.
10. **Type Deduction:** Utilized the `auto` keyword for cleaner code and type deduction.

## Scope and Limitations

While I've endeavored to improve the solutions, it is important to note that:

- This repository does not provide solutions to every problem mentioned in the book.
- Some solutions in this repository may not correspond to problems directly from the book but are inspired by similar challenges.

## Arrays

| #   | Title                | Solution                                                                                                     |
| --- | -------------------- | ------------------------------------------------------------------------------------------------------------ |
| 1   | Array rotation       | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/array_rotation.cpp)                |
| 2   | Duplicates           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/duplicates.cpp)                   |
| 3   | Majority element     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/majority_element.cpp)             |
| 4   | Merge arrays         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/merge_arrays.cpp)                |
| 5   | Min number           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/min_number.cpp)                  |
| 6   | Permutations         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/permutations.cpp)                |
| 7   | Reorder numbers      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/reorder_numbers.cpp)             |

## Strings

| #   | Title                    | Solution                                                                                                     |
| --- | ------------------------ | ------------------------------------------------------------------------------------------------------------ |
| 1   | Add numeric string       | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/add_numeric_string.cpp)       |
| 2   | Allocate string          | [C](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/allocate_str.c)                 |
| 3   | Anagram                  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/anagram.cpp)                   |
| 4   | Combinations             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/combinations.cpp)              |
| 5   | Delete char              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/delete_char.cpp)              |
| 6   | Delete duplicate chars   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/delete_duplicate_chars.cpp)    |
| 7   | Edit distance            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/edit_distance.cpp)            |
| 8   | First char appearing once| [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/first_char_appearing_once.cpp)|
| 9   | Numeric string           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/numeric_string.cpp)           |
| 10  | Palindrome number        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/palindrome_number.cpp)        |
| 11  | Permutations             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/permutations.cpp)             |
| 12  | Regex                    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/regex.cpp)                    |
| 13  | Replace blanks           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/replace_blanks.cpp)           |
| 14  | Reverse words in a sentence | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/reverse_words_in_sentence.cpp)|
| 15  | String path              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/string_path.cpp)              |


## Stack and Queue

| #   | Title             | Solution                                                                                              |
| --- | ----------------- | ----------------------------------------------------------------------------------------------------- |
| 1   | Min in stack      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/min_in_stack.cpp)   |
| 2   | Push pop order    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/stack_push_pop_order.cpp) |
| 3   | Stream median     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/stream_median.cpp) |

## Lists

| #   | Title                  | Solution                                                                                                   |
| --- | ---------------------- | ---------------------------------------------------------------------------------------------------------- |
| 1   | Clone complex list     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/clone_complex_list.cpp)         |
| 2   | Delete duplicates      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/delete_duplicates.cpp)           |
| 3   | Delete node            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/delete_node.cpp)                 |
| 4   | Kth node               | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/kth_node.cpp)                    |
| 5   | Loops                  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/loops.cpp)                       |
| 6   | Merge lists            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/merge.cpp)                       |
| 7   | Print reversely         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/print_reversely.cpp)             |
| 8   | Reverse list           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/reverse_list.cpp)               |
| 9   | Sort list              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/sort.cpp)                        |

## Matrices

| #   | Title                  | Solution                                                                                              |
| --- | ---------------------- | ----------------------------------------------------------------------------------------------------- |
| 1   | Fibonacci              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/fibonacci.cpp)          |
| 2   | Partially sorted matrix| [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/partially_sorted_matrix.cpp) |
| 3   | Sorted matrix          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/sorted_matrix.cpp)       |

## Classes

| #   | Title                | Solution                                                                                                     |
| --- | -------------------- | ------------------------------------------------------------------------------------------------------------ |
| 1   | Arrow and dot        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/arrow_and_dot.cpp)                |
| 2   | Assigment operator   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/assigment_operator.cpp)           |
| 3   | Objective C          | [C](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/objective_c.c)                      |

## Bit operations

| #   | Title                   | Solution                                                                                                     |
| --- | ----------------------- | ------------------------------------------------------------------------------------------------------------ |
| 1   | Count ones              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/count_ones.cpp)           |
| 2   | Modify numbers          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/modify_number.cpp)        |
| 3   | Two missing numbers     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/two_missing_numbers.cpp)  |
| 4   | Uniquely occuring numbers| [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/uniquely_occuring_numbers.cpp)|

## Trees

| #   | Title                    | Solution                                                                                                     |
| --- | ------------------------ | ------------------------------------------------------------------------------------------------------------ |
| 1   | Balance                  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/balance.cpp)                        |
| 2   | Construct binary tree    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/construct_binary_tree.cpp)          |
| 3   | Convert to list          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/convert_to_list.cpp)                |
| 4   | Depth                    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/depth.cpp)                          |
| 5   | Largest subtrees         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/largest_subtrees.cpp)               |
| 6   | Lowest ancestor          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/lowest_ancestor.cpp)               |
| 7   | Nodes at k distance      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/nodes_at_k_distance.cpp)           |
| 8   | Path                     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/path.cpp)                          |
| 9   | Print levels             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/print_levels.cpp)                  |
| 10  | Print zigzag             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/print_zigzag.cpp)                  |

## Other

| #   | Title                    | Solution                                                                                                        |
| --- | ------------------------ | --------------------------------------------------------------------------------------------------------------- |
| 1   | Coin change              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/coin_change.cpp)          |
| 2   | Eight queens             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/eight_queens.cpp)         |
| 3   | Greatest sum subarrays   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/greatest_sum_subarrays.cpp) |
| 4   | K least numbers          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/k_least_numbers.cpp)      |


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
