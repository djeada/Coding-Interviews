/*
 * STACK WITH MINIMUM TRACKING
 *
 * This program implements a template class `StackWithMin` which represents a stack
 * data structure capable of tracking the minimum element in constant time (O(1))
 * for all operations including push, pop, top, and retrieving the minimum value.
 *
 * The implementation uses a modified stack mechanism where the pushed value is
 * encoded if it is less than the current minimum. This ensures that when an element
 * is popped, the previous minimum can be restored in constant time.
 *
 * ASCII Illustration:
 *
 *      Stack: [ ... | encoded_value ]
 *                   ^
 *              min_value (current minimum)
 *
 * Example Input/Output:
 *
 *   Sequence of operations:
 *     push(10) -> min: 10, stack: [10]
 *     push(5)  -> min: 5,  stack: [10, (2*5 - 10)=0]
 *     push(2)  -> min: 2,  stack: [10, 0, (2*2 - 5)=-1]
 *     top()    -> returns: 2 (decoded from -1)
 *     pop()    -> removes 2, restores min to 5
 *
 *   Explanation:
 *     The algorithm encodes new minimum values to allow constant time retrieval of
 *     both the top element and the minimum element after a pop operation.
 */

#include <cassert>
#include <iostream>
#include <optional>
#include <stack>

// Template class for a stack that tracks the minimum element in O(1) time.
template <typename T>
class StackWithMin {
public:
    StackWithMin() = default;
    ~StackWithMin() = default;

    void push(const T &value) {
        if (data_.empty()) {
            data_.push(value);
            min_value_ = value;
        } else if (value >= *min_value_) {
            data_.push(value);
        } else {
            // Encode the new minimum value.
            data_.push(2 * value - *min_value_);
            min_value_ = value;
        }
    }

    void pop() {
        assert(!data_.empty());
        T top_val = data_.top();
        if (top_val < *min_value_) {
            // Restore the previous minimum.
            min_value_ = 2 * *min_value_ - top_val;
        }
        data_.pop();
    }

    std::optional<T> top() const {
        if (data_.empty()) {
            return std::nullopt;
        }
        T top_val = data_.top();
        return (top_val < *min_value_) ? *min_value_ : top_val;
    }

    std::optional<T> min() const {
        return min_value_;
    }

    bool empty() const {
        return data_.empty();
    }

    size_t size() const {
        return data_.size();
    }

private:
    std::stack<T> data_;
    std::optional<T> min_value_;
};

// Test cases to ensure correctness of StackWithMin operations.
void test() {
    {
        StackWithMin<int> stack;
        stack.push(10);
        stack.push(5);
        stack.push(2);
        assert(stack.min() == 2);
        assert(stack.top() == 2);
        stack.pop();
        assert(stack.min() == 5);
        assert(stack.top() == 5);
    }
    {
        StackWithMin<int> stack;
        stack.push(-1);
        stack.push(7);
        stack.push(-2);
        assert(stack.min() == -2);
        stack.pop();
        assert(stack.min() == -1);
        assert(stack.top() == 7);
    }
    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
