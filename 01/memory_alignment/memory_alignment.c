#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma pack(push, 1)
struct tag_misaligned {
  char a;
  double b;
  int c;
} typedef struct_misaligned;
#pragma pack(pop)

struct tag_aligned {
  double b;
  int c;
  char a;
} typedef struct_aligned;

// Initialize struct with data
void init_struct_misaligned(struct_misaligned *s) {
  s->a = rand() % 128;
  s->b = (double)rand() / RAND_MAX;
  s->c = rand();
}

void init_struct_aligned(struct_aligned *s) {
  s->a = rand() % 128;
  s->b = (double)rand() / RAND_MAX;
  s->c = rand();
}

// Different operations to simulate real workloads
double compute_sequential(void *array, size_t count, int type_size) {
  clock_t start = clock();
  double sum = 0;

  // Cast to appropriate type and perform operations
  if (type_size == sizeof(struct_misaligned)) {
    struct_misaligned *arr = (struct_misaligned *)array;
    for (size_t i = 0; i < count; i++) {
      sum += arr[i].b * arr[i].c + arr[i].a;
    }
  } else {
    struct_aligned *arr = (struct_aligned *)array;
    for (size_t i = 0; i < count; i++) {
      sum += arr[i].b * arr[i].c + arr[i].a;
    }
  }

  clock_t end = clock();
  printf("Computed sum: %f\n", sum); // Prevent optimization
  return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double compute_random_access(void *array, size_t count, int type_size,
                             int *indices) {
  clock_t start = clock();
  double sum = 0;

  if (type_size == sizeof(struct_misaligned)) {
    struct_misaligned *arr = (struct_misaligned *)array;
    for (size_t i = 0; i < count; i++) {
      sum += arr[indices[i]].b * arr[indices[i]].c + arr[indices[i]].a;
    }
  } else {
    struct_aligned *arr = (struct_aligned *)array;
    for (size_t i = 0; i < count; i++) {
      sum += arr[indices[i]].b * arr[indices[i]].c + arr[indices[i]].a;
    }
  }

  clock_t end = clock();
  printf("Computed sum: %f\n", sum); // Prevent optimization
  return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
  srand(time(NULL));
  const int ARRAY_SIZE = 1000000; // Increased size

  // Allocate arrays
  struct_misaligned *misaligned_array =
      malloc(sizeof(struct_misaligned) * ARRAY_SIZE);
  struct_aligned *aligned_array = malloc(sizeof(struct_aligned) * ARRAY_SIZE);

  // Create random access pattern
  int *indices = malloc(sizeof(int) * ARRAY_SIZE);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    indices[i] = rand() % ARRAY_SIZE;
  }

  // Initialize arrays with data
  for (int i = 0; i < ARRAY_SIZE; i++) {
    init_struct_misaligned(&misaligned_array[i]);
    init_struct_aligned(&aligned_array[i]);
  }

  printf("Struct sizes:\n");
  printf("struct_misaligned: %zu bytes\n", sizeof(struct_misaligned));
  printf("struct_aligned: %zu bytes\n\n", sizeof(struct_aligned));

  printf("Sequential Access Test:\n");
  double misaligned_seq = compute_sequential(misaligned_array, ARRAY_SIZE,
                                             sizeof(struct_misaligned));
  double aligned_seq =
      compute_sequential(aligned_array, ARRAY_SIZE, sizeof(struct_aligned));
  printf("Misaligned sequential: %f seconds\n", misaligned_seq);
  printf("Aligned sequential: %f seconds\n", aligned_seq);
  printf("Sequential difference: %.2f%%\n\n",
         ((misaligned_seq - aligned_seq) / aligned_seq) * 100);

  printf("Random Access Test:\n");
  double misaligned_rand = compute_random_access(
      misaligned_array, ARRAY_SIZE, sizeof(struct_misaligned), indices);
  double aligned_rand = compute_random_access(aligned_array, ARRAY_SIZE,
                                              sizeof(struct_aligned), indices);
  printf("Misaligned random: %f seconds\n", misaligned_rand);
  printf("Aligned random: %f seconds\n", aligned_rand);
  printf("Random access difference: %.2f%%\n",
         ((misaligned_rand - aligned_rand) / aligned_rand) * 100);

  // Cleanup
  free(misaligned_array);
  free(aligned_array);
  free(indices);

  return 0;
}
