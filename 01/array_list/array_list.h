#ifndef ARRAY_LIST_H

#define ARRAY_LIST_H

#include <stddef.h>

typedef struct {
  void** data;
  size_t size;
  size_t capacity;
} ArrayList;

ArrayList* array_list_new(void);

int array_list_append(ArrayList* list, void* element);
void* array_list_get(ArrayList* List, size_t index);
int array_list_set(ArrayList* list, size_t index, void* element);
size_t array_list_size(ArrayList* list);
void array_list_free(ArrayList* list);
void array_list_free_all(ArrayList* list);

#endif
