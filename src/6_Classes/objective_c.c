#include <stdio.h>

struct X {
  int x;
  void (*fp)(struct X *);
};

void func1(struct X *xobj) { printf("%s, %d\n", __FUNCTION__, xobj->x); }
void func2(struct X *xobj) { printf("%s, %d\n", __FUNCTION__, xobj->x); }

int main() {
  struct X obj;
  obj.x = 10;
  obj.fp = func1;
  obj.fp(&obj);
  obj.x = 20;
  obj.fp = func2;
  obj.fp(&obj);

  return 0;
}
