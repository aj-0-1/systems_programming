#include <stdlib.h>
#include "array_list.h"

#define INITIAL_CAPACITY 8
#define GROWTH_FACTOR 2

ArrayList* array_list_new(void) {
  ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
  if (list == NULL) {
    return NULL;
  }

  list->data = (void**)malloc(INITIAL_CAPACITY*sizeof(void**));
  if (list->data == NULL) {
    free(list);
    return NULL;
  }

  list->size = 0;
  list->capacity = INITIAL_CAPACITY;
  return list;
}

static int array_list_resize(ArrayList* list) {
  size_t new_capacity = list->capacity * GROWTH_FACTOR;
  void** new_data = (void**)realloc(list->data, new_capacity * sizeof(void**));
  
  if (new_data == NULL) {
    return 0;
  }

  list->data = new_data;
  list->capacity = new_capacity;

  return 1;
}

int array_list_append(ArrayList* list, void* element) {
  if (list == NULL) {
    return 0;
  }

  if (list->size >= list->capacity) {
    if (!array_list_resize(list)) {
      return 0;
    }
  }

  list->data[list->size++] = element;
  return 1;
}

void* array_list_get(ArrayList* list, size_t index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    }
    
    return list->data[index];
}

int array_list_set(ArrayList* list, size_t index, void* element) {
    if (list == NULL || index >= list->size) {
        return 0;
    }
    
    list->data[index] = element;
    return 1;
}

size_t array_list_size(ArrayList* list) {
    return list == NULL ? 0 : list->size;
}

void array_list_free(ArrayList* list) {
    if (list == NULL) {
        return;
    }
    
    free(list->data);
    free(list);
}

void array_list_free_all(ArrayList* list) {
    if (list == NULL) {
        return;
    }
    
    // Free all elements
    for (size_t i = 0; i < list->size; i++) {
        free(list->data[i]);
    }
    
    // Free the array and list
    free(list->data);
    free(list);
}

