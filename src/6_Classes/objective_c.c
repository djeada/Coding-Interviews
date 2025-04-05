/*
 * Simulating Classes and Objects in Pure C
 *
 * This program demonstrates how to simulate class-like behavior using pure C.
 * We define a struct "Object" that encapsulates data and a function pointer,
 * which acts as a method. Two "methods" (functions) are implemented: method1 and
 * method2. Each function takes a pointer to the struct instance ("self") to access
 * the encapsulated data.
 *
 * ASCII Illustration:
 *
 *      +-----------------------+
 *      |       Object          |
 *      +-----------------------+
 *      | int data              |  ---> Data member
 *      | void (*execute)(*)    |  ---> Function pointer ("method")
 *      +-----------------------+
 *
 * Example Usage:
 *   1. Create an instance of Object (e.g., obj1).
 *   2. Set its data value.
 *   3. Assign a function pointer to emulate a method (e.g., method1).
 *   4. Call the method via the function pointer.
 *
 * Expected Output:
 *   method1, 10
 *   method2, 20
 */

#include <stdio.h>

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
  // Create two object instances
  struct Object obj1, obj2;

  // Initialize obj1 and assign method1 to its function pointer
  obj1.data = 10;
  obj1.execute = method1;
  obj1.execute(&obj1);

  // Initialize obj2 and assign method2 to its function pointer
  obj2.data = 20;
  obj2.execute = method2;
  obj2.execute(&obj2);

  return 0;
}
