#include "binary_tree.h"
#include <vector>

//              1
//            /   \
//           2     3
//       /       \
//      4         5
//     / \      / |  \
//    6   7    8  9  10
void test1() {
  test("Test1", pNode1, pNode6, pNode8, pNode2);

}

//              1
//            /   \
//           2     3
//       /       \
//      4         5
//     / \      / |  \
//    6   7    8  9  10
void test2() {
  test("Test2", pNode1, pNode7, pNode3, pNode1);

}

//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void test3() {
  test("Test3", pNode1, pNode5, pNode4, pNode3);
}

//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void test4() {
  test("Test4", pNode1, pNode5, pNode6, NULL);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  return 0;
}
