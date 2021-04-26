#include <cassert>
#include <stack>
#include <vector>

bool isPopOrder(std::vector<int> &push, std::vector<int> &pop) {
  bool possible = false;

  if (!push.empty() && !pop.empty()) {
    unsigned int iPush = 0;
    unsigned int iPop = 0;
    std::stack<int> stackData;

    while (iPop < pop.size()) {
      while (stackData.empty() || stackData.top() != pop[iPop]) {

        if (iPush == push.size())
          break;

        stackData.push(push[iPush]);
        iPush++;
      }

      if (stackData.top() != pop[iPop])
        break;

      stackData.pop();
      iPop++;
    }

    if (stackData.empty() && iPop == pop.size())
      possible = true;
  }

  return possible;
}

void test1() {
  std::vector<int> push{1, 2, 3, 4, 5};
  std::vector<int> pop{4, 5, 3, 2, 1};
  assert(isPopOrder(push, pop));
}

void test2() {
  std::vector<int> push{1, 2, 3, 4, 5};
  std::vector<int> pop{3, 5, 4, 2, 1};
  assert(isPopOrder(push, pop));
}

void test3() {
  std::vector<int> push{1, 2, 3, 4, 5};
  std::vector<int> pop{4, 3, 5, 1, 2};
  assert(!isPopOrder(push, pop));
}

void test4() {
  std::vector<int> push{1, 2, 3, 4, 5};
  std::vector<int> pop{3, 5, 4, 1, 2};
  assert(!isPopOrder(push, pop));
}

int main() {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
