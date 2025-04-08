# My Notes on "Coding Interviews"

This repository contains **my personal notes, remarks, and attempts** at solving challenges inspired by (and sometimes directly taken from) Harry He's book, *Coding Interviews*. **These are not official or authoritative solutions**. Instead, they represent what I tried on my own while learning, and I encourage everyone to also attempt these or similar problems independently.

> **Important**: Some of the problems here do not appear in the book but felt related in scope, so I included them in my study process.

If you’re interested in the book itself, you can find it on Amazon [here](https://amzn.to/43AFzBh).

![Capture](https://user-images.githubusercontent.com/37275728/186154277-b2ef19e7-1d07-4e4f-8bb6-ba6887e05519.PNG)

## Why These Notes?

I aimed to modernize or expand on certain approaches while keeping these notes for my personal review:

- The error handling approach was updated by replacing traditional error codes with *exceptions* to improve clarity.  
- The input/output system was modernized by using *iostream* rather than the legacy `stdlib.h` for better consistency.  
- The testing methodology was enhanced by substituting traditional console tests with *assertions* to simplify validation.  
- The data management strategy was refined by adopting *vectors* instead of raw arrays for increased flexibility.  
- The looping mechanism was optimized by favoring *iterators* over integer indexing for smoother code traversal.  
- The organization of code was improved by employing *classes* to encapsulate related data effectively.  
- The practice of accessing variables was updated by using *references* in place of pointers where applicable.  
- The programming style was made more concise by integrating *lambdas* for compact and focused functionality.  
- The process of grouping data was simplified by leveraging *STL pairs* for combining two values efficiently.  
- The readability of the code was enhanced by implementing the *auto* keyword to facilitate cleaner type deduction.

## Scope and Limitations

- **Not all** book problems are covered.
- **Some** problems are my own or from similar resources (not found in the book).
- The solutions are **my personal attempts** and may not reflect the book’s exact methods.

---

## Arrays

| # | Title               | Notes/Solution                                                                                                                  |
| - | ------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| 1 | Array rotation      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/array_rotation.cpp)                                   |
| 2 | Duplicates          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/duplicates.cpp)                                      |
| 3 | Majority element    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/majority_element.cpp)                                |
| 4 | Merge arrays        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/merge_arrays.cpp)                                    |
| 5 | Min number          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/min_number.cpp)                                      |
| 6 | Permutations        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/permutations.cpp)                                    |
| 7 | Reorder numbers     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/reorder_numbers.cpp)                                 |

## Strings

| # | Title                       | Notes/Solution                                                                                                                       |
| - | --------------------------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| 1 | Add numeric string          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/add_numeric_string.cpp)                                      |
| 2 | Allocate string             | [C](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/allocate_str.cpp)                                               |
| 3 | Anagram                     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/anagram.cpp)                                                  |
| 4 | Combinations                | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/combinations.cpp)                                             |
| 5 | Delete char                 | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/delete_char.cpp)                                              |
| 6 | Delete duplicate chars      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/delete_duplicate_chars.cpp)                                   |
| 7 | First char appearing once   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/first_char_appearing_once.cpp)                              |
| 8 | Numeric string              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/numeric_string.cpp)                                           |
| 9 | Palindrome number           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/palindrome_number.cpp)                                        |
| 10| Permutations                | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/permutations.cpp)                                             |
| 11| Regex                       | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/regex.cpp)                                                  |
| 12| Replace blanks              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/replace_blanks.cpp)                                           |
| 13| Reverse words in sentence   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/reverse_words_in_sentence.cpp)                                |

## Stack and Queue

| # | Title                 | Notes/Solution                                                                                                                         |
| - | --------------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| 1 | Circular queue        | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/circular_queue.cpp)                                      |
| 2 | Max queue             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/max_queue.cpp)                                           |
| 3 | Min in stack          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/min_in_stack.cpp)                                        |
| 4 | Stack push pop order  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/stack_push_pop_order.cpp)                                |
| 5 | Stream median         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/stream_median.cpp)                                       |

## Lists

| #  | Title                | Notes/Solution                                                                                                                        |
| -- | -------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| 1  | Clone complex list   | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/clone_complex_list.cpp)                                          |
| 2  | Delete duplicates    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/delete_duplicates.cpp)                                           |
| 3  | Delete node          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/delete_node.cpp)                                                 |
| 4  | Kth node             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/kth_node.cpp)                                                    |
| 5  | List implementation  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/list.cpp) *(accompanied by list.h)*                              |
| 6  | Loops                | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/loops.cpp)                                                       |
| 7  | Merge lists          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/merge.cpp)                                                       |
| 8  | Print reversely      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/print_reversely.cpp)                                               |
| 9  | Reverse list         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/reverse_list.cpp)                                                  |
| 10 | Sort list            | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/sort.cpp)                                                        |

## Matrices

| # | Title                    | Notes/Solution                                                                                                                     |
| - | ------------------------ | ----------------------------------------------------------------------------------------------------------------------------------- |
| 1 | Binary search matrix     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/binary_search_matrix.cpp)                                  |
| 2 | Magic square             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/magic_square.cpp)                                          |
| 3 | Partially sorted matrix  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/partially_sorted_matrix.cpp)                               |
| 4 | String path              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/string_path.cpp)                                           |

## Classes

| # | Title                   | Notes/Solution                                                                                                                      |
| - | ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| 1 | Advanced inheritance    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/advanced_inheritance.cpp)                                    |
| 2 | Arrow and dot           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/arrow_and_dot.cpp)                                           |
| 3 | Assignment operator     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/assigment_operator.cpp)                                      |
| 4 | Objective C             | [C](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/objective_c.c)                                                 |
| 5 | Shape inheritance       | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/shape_inheritance.cpp)                                       |

## Bit Operations

| # | Title                         | Notes/Solution                                                                                                                        |
| - | ----------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| 1 | Count ones                    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/count_ones.cpp)                                         |
| 2 | Hamming distance              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/hamming_distance.cpp)                                   |
| 3 | Modify number                 | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/modify_number.cpp)                                      |
| 4 | Number complement             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/number_complement.cpp)                                  |
| 5 | Two missing numbers           | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/two_missing_numbers.cpp)                                |
| 6 | Uniquely occurring numbers    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/uniquely_occuring_numbers.cpp)                           |

## Trees

| # | Title                    | Notes/Solution                                                                                                                        |
| - | ------------------------ | -------------------------------------------------------------------------------------------------------------------------------------- |
| 1 | Balance                  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/balance.cpp)                                                    |
| 2 | Binary tree              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/binary_tree.cpp) *(uses binary_tree.h)*                           |
| 3 | Construct binary tree    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/construct_binary_tree.cpp)                                      |
| 4 | Convert to list          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/convert_to_list.cpp)                                            |
| 5 | Depth                    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/depth.cpp)                                                      |
| 6 | Largest subtrees         | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/largest_subtrees.cpp)                                           |
| 7 | Lowest ancestor          | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/lowest_ancestor.cpp)                                            |
| 8 | Nodes at k distance      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/nodes_at_k_distance.cpp)                                        |
| 9 | Path                     | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/path.cpp)                                                       |
| 10| Print levels             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/print_levels.cpp)                                               |
| 11| Print zigzag             | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/print_zigzag.cpp)                                               |

## Dynamic Programming

| # | Title                        | Notes/Solution                                                                                                                         |
| - | ---------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| 1 | Climbing stairs              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/climbing_stairs.cpp)                                  |
| 2 | Coin change                  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/coin_change.cpp)                                      |
| 3 | Edit distance                | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/edit_distance.cpp)                                    |
| 4 | Eight queens                 | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/eight_queens.cpp)                                     |
| 5 | Fibonacci                    | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/fibonacci.cpp)                                        |
| 6 | Greatest sum subarrays       | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/greatest_sum_subarrays.cpp)                               |
| 7 | K least numbers              | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/k_least_numbers.cpp)                                    |
| 8 | Longest increasing path      | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/longest_increasing_path.cpp)                            |
| 9 | Matrix chain multiplication  | [C++](https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/matrix_chain_multiplication.cpp)                          |

---

## Book Review

I’ve been a software engineer for a few years now, mostly working on full-stack projects—designing APIs, optimizing databases, and occasionally dabbling in front-end frameworks. While I’m comfortable solving day-to-day problems at work, I realized I needed a solid refresher on the classic algorithmic challenges often asked in big tech interviews. 

So, when I started hearing buzz about *Coding Interviews* by Harry He, I decided to give it a shot. I’d heard it covers many of the typical interview questions you might face at larger tech companies: from common data structures to algorithmic puzzles that test not just coding ability but also problem-solving and critical thinking.

---

### Why I Picked Up the Book
- Even though I code daily, I don’t always get to practice the kind of purely algorithmic exercises that come up in interviews. It seemed like a good way to brush up on fundamentals.
- Several colleagues and friends mentioned it helped them feel confident going into their interviews. 
- I’m a big fan of books that get to the point—especially for busy professionals who want quick coverage of diverse problems.

---

### What Surprised Me
1. The book manages to pack a wide range of topics (arrays, strings, trees, etc.) in a relatively short space. As someone who’s short on time, I appreciated not having to wade through hundreds of pages to find the essential parts.
2. Most examples feel grounded in real-world-ish scenarios (though simplified). This was good for me because purely abstract puzzles can sometimes feel disconnected from actual coding work. 
3. It touches on a lot of the categories big tech recruiters typically ask about—like reversing linked lists, string manipulations, or finding the “maximum something” in subarrays. It was a well-rounded refresher.

---

### What I Didn’t Love
1. As a visual learner, I’d have liked more diagrams—especially for tree or graph-related problems. A quick tree or flowchart can do wonders for understanding an algorithm’s logic.
2. The coverage of topics like dynamic programming and graph algorithms felt a bit too brief. It included some references to DP but didn’t delve deeply into more complex variations. If you’re looking for advanced DP problems (like those involving multiple constraints or multi-dimensional optimization), you might be left wanting more.
3. The explanations are often concise, which can be a double-edged sword. While it’s great that the book doesn’t ramble, I occasionally wished the theoretical background had been fleshed out just a little more. If you’re new to a certain data structure or algorithm, you might need to supplement your reading with online resources.

---

### How I Used the Book
- I’d read a chapter, jot down my own notes, and attempt the problems. For tricky ones, I wrote mini solutions on my own first, then cross-checked with the book’s approach to see where I could improve.
- Before a technical interview, I revisited certain chapters (like “Strings” or “Trees”) to make sure I remembered the classic pitfalls and corner cases. 
- Whenever I felt something was underexplained, I’d look up articles or videos online to fill in the gaps. This was especially true for more advanced dynamic programming or graph algorithms not deeply covered.

---

## Testing

Our testing workflow runs automatically on every push and pull request, giving you peace of mind that your code is continuously checked. It starts by checking out your repository and then smartly separates your source files into two groups: one for library code (files without a main function) and one for tests (files with a main function). The library files get compiled into object files and are bundled into a static library, while your test files are compiled and linked against this library.

Once the test executables are built, each one is run with a 90-second timeout to catch any potential issues early on. If a test fails or takes too long, the workflow stops and lets you know right away, making it easy to pinpoint and fix problems. This human-friendly process ensures that every update you make is both compiled correctly and behaves as expected, keeping your development smooth and reliable.

---

## Contributing

Feel free to open a pull request or an issue if you spot something that can be improved. Please remember:

- These notes are **personal remarks** and **not** a definitive guide.
- I strongly recommend practicing and testing your own approaches.

## License

[MIT](https://choosealicense.com/licenses/mit/)

---

> **Disclaimer**: These notes are solely **my personal study aids** and should not be treated as an official or comprehensive guide to *Coding Interviews*. Purchase the book for the full experience and complete problem statements. Happy coding and learning!
