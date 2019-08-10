#if !defined(ARRAY_H)
#define ARRAY_H

#include <stdbool.h>

void array_random(int *array, int size, int min, int max);
void array_random_arraylimited(int *array, int size, int *min, int *max);

int array_compare(int *a, int *b, int size);
int array_compare2(int *a, int *b, int size);
//compute
int array_add(int *a, int *b, int size);
int array_subtract(int *a, int *b, int size);

void array_copy(int *a, int *copy, int size);

void array_print(int *a, int size);

typedef bool (*test_project)(char *);
void test(test_project);

int random(int min, int max);

#endif // ARRAY_H
