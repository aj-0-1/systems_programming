#include "array_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[50];
  int age;
} Person;

int main() {
  ArrayList *list = array_list_new();
  if (list == NULL) {
    printf("Failed to create list\n");
    return 1;
  }

  printf("Adding integers...\n");
  for (int i = 0; i < 3; i++) {
    int *num = malloc(sizeof(int));
    *num = i * 10;
    if (!array_list_append(list, num)) {
      printf("Failed to append integer %d\n", i);
      array_list_free_all(list);
      return 1;
    }
  }

  printf("\nAdding strings...\n");
  char *str1 = strdup("Hello");
  if (str1 == NULL) {
    printf("Failed to allocate memory for str1\n");
    array_list_free_all(list);
    return 1;
  }

  char *str2 = strdup("World");
  if (str2 == NULL) {
    printf("Failed to allocate memory for str2\n");
    free(str1);
    array_list_free_all(list);
    return 1;
  }
  if (!array_list_append(list, str1)) {
    printf("Failed to append string 'Hello'\n");
    free(str1);
    free(str2);
    array_list_free_all(list);
    return 1;
  }

  if (!array_list_append(list, str2)) {
    printf("Failed to append string 'World'\n");
    free(str1);
    free(str2);
    array_list_free_all(list);
    return 1;
  }

  printf("\nAdding person struct...\n");
  Person *person = malloc(sizeof(Person));
  if (person == NULL) {
    printf("Failed to allocate memory for person\n");
    array_list_free_all(list);
    return 1;
  }

  strncpy(person->name, "John Doe", sizeof(person->name) - 1);
  person->name[sizeof(person->name) - 1] = '\0';
  person->age = 30;

  if (!array_list_append(list, person)) {
    printf("Failed to append person\n");
    free(person);
    array_list_free_all(list);
    return 1;
  }

  printf("\nList contents:\n");
  for (size_t i = 0; i < array_list_size(list); i++) {
    void *element = array_list_get(list, i);
    if (i < 3) {
      printf("Integer at index %zu: %d\n", i, *(int *)element);
    } else if (i < 5) {
      printf("String at index %zu: %s\n", i, (char *)element);
    } else {
      Person *p = (Person *)element;
      printf("Person at index %zu: %s, age %d\n", i, p->name, p->age);
    }
  }

  array_list_free_all(list);
  printf("\nList freed successfully\n");

  return 0;
}
