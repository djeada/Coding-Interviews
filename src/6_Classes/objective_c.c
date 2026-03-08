/*
 * Task: Simulate class-like behavior in C using structs and function pointers.
 *
 * OBJECT-LIKE DESIGN IN C
 *
 * Problem:
 * Build a C struct that stores state and a function pointer to emulate method
 * dispatch. Show that different instances can point to different behaviors
 * while sharing the same data layout.
 *
 * Constraints:
 * - Use C structs and function pointers only (no C++ features).
 * - Method functions receive `self` pointer to access instance data.
 * - Keep memory ownership explicit and simple.
 *
 * Example:
 * Input: obj1.data = 10 with method1, obj2.data = 20 with method2
 * Output: method1, 10 and method2, 20
 */

#include <stdio.h>

struct TestRunner {
  int total;
  int failed;
};

static void init_runner(struct TestRunner *runner) {
  runner->total = 0;
  runner->failed = 0;
}

static void expect_int_eq(struct TestRunner *runner, int got, int expected,
                          const char *label) {
  runner->total++;
  if (got == expected) {
    printf("[PASS] %s\n", label);
    return;
  }
  runner->failed++;
  printf("[FAIL] %s expected=%d got=%d\n", label, expected, got);
}

static void expect_ptr_eq(struct TestRunner *runner, const void *got,
                          const void *expected, const char *label) {
  runner->total++;
  if (got == expected) {
    printf("[PASS] %s\n", label);
    return;
  }
  runner->failed++;
  printf("[FAIL] %s expected=%p got=%p\n", label, expected, got);
}

static void summary(const struct TestRunner *runner) {
  printf("Tests: %d passed, %d failed, %d total\n",
         runner->total - runner->failed, runner->failed, runner->total);
}

struct Object {
  int data;                             // Encapsulated data
  void (*execute)(struct Object *self); // Function pointer to emulate a method
};

void method1(struct Object *self) {
  printf("%s, %d\n", __FUNCTION__, self->data);
}

void method2(struct Object *self) {
  printf("%s, %d\n", __FUNCTION__, self->data);
}

int main() {
  struct TestRunner runner;
  init_runner(&runner);

  // Create two object instances
  struct Object obj1, obj2;

  // Initialize obj1 and assign method1 to its function pointer
  obj1.data = 10;
  obj1.execute = method1;
  obj1.execute(&obj1);
  expect_int_eq(&runner, obj1.data, 10, "obj1 data");
  expect_ptr_eq(&runner, (const void *)obj1.execute, (const void *)method1,
                "obj1 method");

  // Initialize obj2 and assign method2 to its function pointer
  obj2.data = 20;
  obj2.execute = method2;
  obj2.execute(&obj2);
  expect_int_eq(&runner, obj2.data, 20, "obj2 data");
  expect_ptr_eq(&runner, (const void *)obj2.execute, (const void *)method2,
                "obj2 method");

  summary(&runner);
  return 0;
}
