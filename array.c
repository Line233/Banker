#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "array.h"
#include <math.h>
#include <stdlib.h>

void array_random(int *array, int size, int min, int max)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = random(min, max);
    }
}
int array_compare2(int *a, int *b, int size) //not suggest
{
    int absx = 0;
    int contract = 0;
    for (int i = 0; i < size; i++)
    {
        contract += (a[i] - b[i]);
        absx += abs(a[i] - b[i]);
    }
    if (absx == 0)
        return 0;
    else if (absx == contract)
        return 1;
    else if (absx == abs(contract))
        return -1;
    else
        return 2;
}
int array_add(int *a, int *b, int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] += b[i];
    }
}
int array_subtract(int *a, int *b, int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] -= b[i];
    }
}
int random(int min, int max) //include min, but include max
{
    static bool first = true;
    if (first)
    {
        srand(time(0));
        first = false;
    }
    int distance = max - min;
    if (distance == 0)
    {
        return min;
    }
    else
    {
        int r = rand() %( distance+1);
        return r + min;
    }
}
void test(test_project tp)
{
    char name[20];
    int r = tp(name);
    printf("%s\t%s\n", name, r ? "succussful" : "failed");
}
int array_compare(int *a, int *b, int size)
{
    bool less = false, bigger = false;
    for (int i = 0; i < size; i++)
    {
        if (a[i] < b[i])
            less = true;
        else if (a[i] > b[i])
            bigger = true;
    }
    if (less && bigger)
        return 2;
    else if (less)
        return -1;
    else if (bigger)
        return 1;
    else
        return 0;
}
void array_copy(int *a, int *copy, int size)
{
    for (int i = 0; i < size; i++)
    {
        copy[i] = a[i];
    }
}
void array_print(int *a, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("%d", a[size - 1]);
}
void array_random_arraylimited(int *array, int size, int *min, int *max)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = random(min[i], max[i]);
    }
}