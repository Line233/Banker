#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "array.h"

#define resource_num 5
#define process_num 5
#define availiable_max 5
#define max_max 5

void processx(void *pindex);

HANDLE SystemMutex;
int AVAILIBLE[resource_num] = {0};
int NEED[process_num][resource_num] = {0};
int MAX[process_num][resource_num] = {0};
int ALLOCATION[process_num][resource_num] = {0};

bool SystemAllocation(int index, int *k);
bool SystemSet(int index, int *k);
bool _issecurity(int *availible, int *need, int *allocation, int proccessnum, int resourcenum);

//test
bool test_all(char *name);

void Ready(void);

int main(void)
{
    int tp_num = 1;
    test_project tps[] = {
        test_all};

    for (int j = 0; j < tp_num; j++)
        test(tps[j]);
}
bool test_all(char *name)
{
    strcpy(name, "all");
    bool result = true;

    Ready();
    printf("\nAVALIBLE:\t\n");
    array_print(AVAILIBLE, resource_num);
    HANDLE processes[process_num];
    for (int i = 0; i < process_num; i++)
    {
        int *k = malloc(sizeof(int));
        *k = i;
        processes[i] = (HANDLE)_beginthread(processx, 0, k);
    }
    WaitForMultipleObjects(5, processes, true, INFINITE);
    getchar();
    return true;
}
void processx(void *pindex)
{
    int index;
    bool first = true;
    int Max[resource_num];
    //set
    index = *(int *)(pindex);
    srand(time(NULL) + 10 - index);
    int mins[resource_num] = {0};
    array_random_arraylimited(Max, resource_num, mins, AVAILIBLE);
    SystemSet(index, Max);

    first = false;
    //allocate
    while (1)
    {
        int request[resource_num];
        int min[resource_num] = {0};
        array_random_arraylimited(request, resource_num, min, NEED[index]);
        //
        if (array_compare(mins, request, resource_num) != 0)
            SystemAllocation(index, request);
        //release
        Sleep(rand() % 100);
    }
}
bool SystemSet(int index, int *k)
{
    WaitForSingleObject(SystemMutex, INFINITE);
    for (int i = 0; i < resource_num; i++)
    {
        MAX[index][i] = k[i];
        NEED[index][i] = k[i];
    }
    ReleaseSemaphore(SystemMutex, 1, NULL);
}

bool test__issecurity(char *name)
{
    strcpy(name, "_issecurity");
    Ready();

    bool result = false;
}
bool _isenough(int *availible, int *need, int *request, int resourcenum)
{
    int compare_ava = array_compare(availible, request, resource_num);
    int compare_need = array_compare(need, request, resource_num);
    return (compare_ava == 1 || compare_ava == 0) && (compare_need == 0 || compare_need == 1);
}
void _allocate(int *availible, int *need, int *allocation, int *request, int resourcenum)
{
    array_subtract(need, request, resourcenum);
    array_add(allocation, request, resourcenum);
    array_subtract(availible, request, resourcenum);
}
void _release(int *availible, int *need, int *allocation, int *request, int resourcenum)
{
    array_add(need, request, resourcenum);
    array_subtract(allocation, request, resourcenum);
    array_add(availible, request, resourcenum);
}
void _printmatrix()
{
    printf("\nAvalilbe\t\t\t\n");
    array_print(AVAILIBLE, resource_num);
    printf("\nNEED\t\t\t\n");
    array_print(NEED[0], resource_num * process_num);
    printf("\nALLOCATION\t\t\t\n");
    array_print(ALLOCATION[0], resource_num * process_num);
    printf("\nMAX\t\t\t\n");
    array_print(MAX[0], resource_num * process_num);
}
bool SystemAllocation(int index, int *k) //request
{

    WaitForSingleObject(SystemMutex, INFINITE);
    printf("\n%d:\t\n", index);
    array_print(k, resource_num);
    printf("\t");
    if (_isenough(AVAILIBLE, NEED[index], k, resource_num))
    {
        //try to allocate
        //can allocate
        _allocate(AVAILIBLE, NEED[index], ALLOCATION[index], k, resource_num);

        bool issecurity =
            _issecurity(AVAILIBLE, NEED[0], ALLOCATION[0], process_num, resource_num);
        if (issecurity == true)
        {
            //test
            printf("allowed\t");
            //
        }
        else
        {
            //isnotsecurity recoverry
            _release(AVAILIBLE, NEED[index], ALLOCATION[index], k, resource_num);

            printf("insecurity\t");
        }
    }
    else
    {
        //cant allocate
        printf("lack:\t\n");
    }
    _printmatrix();
    printf("\n\n");

    ReleaseSemaphore(SystemMutex, 1, NULL);
}
int _getindex(int processindex, int resoureindx, int processnum, int resourcenum)
{
    return processindex * processnum + resoureindx;
}
bool _issecurity(int *availible, int *need, int *allocation, int proccessnum, int resourcenum)
{
    int finished = 0;
    bool nochange = false;
    int availible2[resourcenum];
    array_copy(availible, availible2, resourcenum);
    while (finished != proccessnum && nochange == false)
    {
        nochange = true;
        for (int i = 0; i < proccessnum; i++)
        {
            int headadd = _getindex(i, 0, proccessnum, resourcenum);
            if (need[headadd] >= 0)
            {
                int compare = array_compare(need + headadd, availible2, resourcenum);
                if (compare == -1 || compare == 0)
                {
                    array_add(availible2, allocation + headadd, resourcenum);
                    need[headadd] = (-1) * need[headadd] - 1;
                    nochange = false;
                    finished++;
                }
            }
        }
    }
    for (int i = 0; i < proccessnum; i++)
    {
        int headadd = _getindex(i, 0, process_num, resourcenum);
        if (need[headadd] < 0)
            need[headadd] = (-1) * need[headadd] - 1;
    }
    return finished == process_num;
}
void Ready(void)
{
    SystemMutex = CreateSemaphore(NULL, 1, 1, NULL);
    WaitForSingleObject(SystemMutex, INFINITE);
    array_random(AVAILIBLE, resource_num, 0, availiable_max);
    ReleaseSemaphore(SystemMutex, 1, NULL);
}
