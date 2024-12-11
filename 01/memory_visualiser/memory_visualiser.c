#include <stdio.h>
#include <stdlib.h>

// DATA Segment (initialized global/static)
int global_init = 42;
static int static_init = 100;

// BSS Segment (uninitialized global/static)
int global_uninit;
static int static_uninit;

// Stack growth demonstration
void stack_demo(int depth) {
  int stack_var = depth;
  printf("Stack variable at depth %d: %p\n", depth, (void *)&stack_var);

  if (depth > 0) {
    stack_demo(depth - 1);
  }
}

int main() {
  printf("=== Memory Layout ===\n\n");

  // DATA segment variables
  printf("DATA Segment:\n");
  printf("  global_init:  %p\n", (void *)&global_init);
  printf("  static_init:  %p\n", (void *)&static_init);

  // BSS segment variables
  printf("\nBSS Segment:\n");
  printf("  global_uninit: %p\n", (void *)&global_uninit);
  printf("  static_uninit: %p\n", (void *)&static_uninit);

  // Stack segment
  printf("\nStack Segment:\n");
  int stack_var = 42;
  printf("  stack_var:     %p\n", (void *)&stack_var);

  // Recursive stack demonstration
  printf("\nStack Growth:\n");
  stack_demo(3);

  // Heap segment
  printf("\nHeap Segment:\n");
  int *heap_var1 = malloc(sizeof(int));
  int *heap_var2 = malloc(sizeof(int));

  printf("  heap_var1:     %p\n", (void *)heap_var1);
  printf("  heap_var2:     %p\n", (void *)heap_var2);

  // Cleanup
  free(heap_var1);
  free(heap_var2);

  return 0;
}
