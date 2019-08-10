#include "array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define array_size 5
#define elem_max 10

bool test_random(char *name)
{
    strcpy(name, "random");
    int max = 100;
    int min = 10;
    bool r = true;
    for (int i = 0; i < 100; i++)
    {
        int k = random(min, max);
        if (k < min || k >= max)
            r = false;
    }
    return r;
}
bool _test_single_array_compare(int *a, int *b, int size)
{
    int r = array_compare(a, b, 10);
    int r2 = array_compare2(a, b, 10);
    return (r == r2);
}
bool test_array_compare(char *name)
{
    strcpy(name, "array_compare");
    int a[10], b[10];
    bool result = true;
    for (int i = 1; i < 1000; i++)
    {
        array_random(a, 10, -1000, 1000);
        array_random(b, 10, -1000, 1000);
        if (!(result = _test_single_array_compare(a, b, 10)))
            break;
        //equal
        array_copy(a, b, 10);
        if (!(result = _test_single_array_compare(a, b, 10)))
            break;
        //less
        b[i % 10] -= i % 1000;
        if (!(result = _test_single_array_compare(a, b, 10)))
            break;
        //more
        b[i % 10] += i % 1000;
        if (!(result = _test_single_array_compare(a, b, 10)))
            break;
    }
    return result;
}
int main()
{

    int tp_num = 2;
    test_project tps[] = {
        test_random,
        test_array_compare};
    for (int i = 0; i < tp_num; i++)
    {
        test(tps[i]);
    }
    getchar();
}