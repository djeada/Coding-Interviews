# CodingInterviews
My alternate solutions to challenges from Harry He's book "Coding Interviews."

<h1>Motivation</h1>

"Coding Interviews" is an excellent book for anyone preparing for a coding job.
However while reading it, I couldn't help but notice how much has changed in the way you write C++ code.
Many solutions were actually written in C and disguised as C++.
I thought that it would be a fantastic idea to modernize the solutions.
Plus you can never really learn something until you implement it yourself.

The things I tried to change:

- Exceptions instead of error codes.
- "iostream" instead of "stdlib.h".
- Assertions instead of console tests.
- Vectors instead of bare arrays.
- Iterators instead of int counter.
- Collections implemented with classes.
- Refrences instead of pointers.
- Lambdas for private functions.
- Stl pair instead of custom structs.
- <i>auto</i> keyword for type deduction.

My improvements are only minor and can be further developed, especially with C++20.

Note: 
- not all problems from the book have solutions in this repository.
- not all solutions in this repository are for the problems found in the book.

<h1>Arrays</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Array rotation</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/array_rotation.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Duplicates</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/duplicates.cpp">C++</a></td>
</tr>
<tr>
<td>3</td>
<td>Majority element</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/majority_element.cpp">C++</a></td>
</tr>
<tr>
<td>4</td>
<td>Merge arrays</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/merge_arrays.cpp">C++</a></td>
</tr>
<tr>
<td>5</td>
<td>Min number</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/min_number.cpp">C++</a></td>
</tr>
<tr>
<td>6</td>
<td>Permutations</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/permutations.cpp">C++</a></td>
</tr>
  <tr>
<td>7</td>
<td>Reorder numbers</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/1_Arrays/reorder_numbers.cpp">C++</a></td>
</tr>
</tbody>
</table>

<h1>Strings</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Add numeric string</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/add_numeric_string.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Allocate string</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/allocate_str.c">C</a></td>
</tr>
<tr>
<td>3</td>
<td>Anagram</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/anagram.cpp">C++</a></td>
</tr>
<tr>
<td>4</td>
<td>Combinations</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/combinations.cpp">C++</a></td>
</tr>
<tr>
<td>5</td>
<td>Delete char</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/delete_char.cpp">C++</a></td>
</tr>
<tr>
<td>6</td>
<td>Delete duplicate chars</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/delete_duplicate_chars.cpp">C++</a></td>
</tr>
  <tr>
<td>7</td>
<td>Edit distance</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/edit_distance.cpp">C++</a></td>
</tr>
  <tr>
<td>8</td>
<td>First char appearing once</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/first_char_appearing_once.cpp">C++</a></td>
</tr>
<tr>
<td>9</td>
<td>Numeric string</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/numeric_string.cpp">C++</a></td>
</tr>
<tr>
<td>10</td>
<td>Palindrome number</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/palindrome_number.cpp">C++</a></td>
</tr>
<tr>
<td>11</td>
<td>Permutations</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/permutations.cpp">C++</a></td>
</tr>
<tr>
<td>12</td>
<td>Regex</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/regex.cpp">C++</a></td>
</tr>
<tr>
<td>13</td>
<td>Replace blanks</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/replace_blanks.cpp">C++</a></td>
</tr>
<tr>
<td>14</td>
<td>Reverse words in a sentence</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/reverse_words_in_sentence.cpp">C++</a></td>
</tr>
<tr>
<td>15</td>
<td>String path</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/2_Strings/string_path.cpp">C++</a></td>
</tr>
</tbody>
</table>

<h1>Stack and Queue</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Min in stack</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/min_in_stack.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Push pop order</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/stack_push_pop_order.cpp">C++</a></td>
</tr>
<tr>
<td>3</td>
<td>Stream median</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/3_Stack_Queue/stream_median.cpp">C++</a></td>
</tr>
</tbody>
</table>

<h1>Lists</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Clone complex list</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/clone_complex_list.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Delete duplicates</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/delete_duplicates.cpp">C++</a></td>
</tr>
<tr>
<td>3</td>
<td>Delete node</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/delete_node.cpp">C++</a></td>
</tr>
<tr>
<td>4</td>
<td>Kth node</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/kth_node.cpp">C++</a></td>
</tr>
<tr>
<td>5</td>
<td>Loops</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/loops.cpp">C++</a></td>
</tr>
<tr>
<td>6</td>
<td>Merge lists</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/merge.cpp">C++</a></td>
</tr>
  <tr>
<td>7</td>
<td>Print reversely</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/print_reversely.cpp">C++</a></td>
</tr>
  <tr>
<td>8</td>
<td>Reverse list</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/reverse_list.cpp">C++</a></td>
</tr>
<tr>
<td>9</td>
<td>Sort list</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/4_Lists/sort.cpp">C++</a></td>
</tr>
</tbody>
</table>

<h1>Matrices</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Fibonacci</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/fibonacci.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Partially sorted matrix</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/partially_sorted_matrix.cpp">C++</a></td>
</tr>
<tr>
<td>3</td>
<td>Sorted matrix</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/5_Matrices/sorted_matrix.cpp">C++</a></td>
</tr>
</tbody>
</table>

<h1>Classes</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Arrow and dot</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/arrow_and_dot.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Assigment operator</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/assigment_operator.cpp">C++</a></td>
</tr>
<tr>
<td>3</td>
<td>Objective C</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/6_Classes/objective_c.c">C</a></td>
</tr>
</tbody>
</table>

<h1>Bit operations</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Count ones</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/count_ones.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Modify numbers</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/modify_number.cpp">C++</a></td>
</tr>
<tr>
<td>3</td>
<td>Two missing numbers</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/two_missing_numbers.cpp">C++</a></td>
</tr>
<tr>
<td>4</td>
<td>Uniquely occuring numbers</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/7_Bit_Operations/uniquely_occuring_numbers.cpp">C++</a></td>
</tr>
</tbody>
</table>

<h1>Trees</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Balance</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/balance.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Construct binary tree</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/construct_binary_tree.cpp">C++</a></td>
</tr>
<tr>
<td>3</td>
<td>Convert to list</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/convert_to_list.cpp">C++</a></td>
</tr>
<tr>
<td>4</td>
<td>Depth</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/depth.cpp">C++</a></td>
</tr>
<tr>
<td>5</td>
<td>Largest subtrees</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/largest_subtrees.cpp">C++</a></td>
</tr>
<tr>
<td>6</td>
<td>Lowest ancestor</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/lowest_ancestor.cpp">C++</a></td>
</tr>
  <tr>
<td>7</td>
<td>Nodes at k distance</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/nodes_at_k_distance.cpp">C++</a></td>
</tr>
  <tr>
<td>8</td>
<td>Path</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/path.cpp">C++</a></td>
</tr>
<tr>
<td>9</td>
<td>Print levels</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/print_levels.cpp">C++</a></td>
</tr>
<tr>
<td>10</td>
<td>Print zigzag</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/8_Trees/print_zigzag.cpp">C++</a></td>
</tr>
</tbody>
</table>

<h1>Dynamic programming</h1>

<table>
<thead>
<tr>
<th>#</th>
<th>Title</th>
<th>Solution</th>
</tr>
</thead>
<tbody>
<tr>
<td>1</td>
<td>Coin change</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/coin_change.cpp">C++</a></td>
</tr>
<tr>
<td>2</td>
<td>Eight queens</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/eight_queens.cpp">C++</a></td>
</tr>
<tr>
<td>3</td>
<td>Greatest sum subarrays</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/greatest_sum_subarrays.cpp">C++</a></td>
</tr>
<tr>
<td>4</td>
<td>K least numbers</td>
<td><a href="https://github.com/djeada/CodingInterviews/blob/master/src/9_Dynamic_Programming/k_least_numbers.cpp">C++</a></td>
</tr>
</tbody>
</table>
