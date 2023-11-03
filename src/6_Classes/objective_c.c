#include <stdio.h>

/**
 * @struct Object
 * @brief Simulates class-like behavior in C by encapsulating data and function
 * pointers.
 */
struct Object {
  int data;                             // Encapsulated data
  void (*execute)(struct Object *self); // Function pointer to emulate a method
};

/**
 * @brief Function emulating a class method, prints the name of the function and
 * the encapsulated data.
 *
 * @param self A pointer to the instance of Object invoking this method.
 */
void method1(struct Object *self) {
  printf("%s, %d\n", __FUNCTION__, self->data);
}

/**
 * @brief Another function emulating a class method, prints the name of the
 * function and the encapsulated data.
 *
 * @param self A pointer to the instance of Object invoking this method.
 */
void method2(struct Object *self) {
  printf("%s, %d\n", __FUNCTION__, self->data);
}

int main() {
  struct Object obj1, obj2;

  // Initializing and invoking method1
  obj1.data = 10;
  obj1.execute = method1;
  obj1.execute(&obj1);

  // Initializing and invoking method2
  obj2.data = 20;
  obj2.execute = method2;
  obj2.execute(&obj2);

  return 0;
}
