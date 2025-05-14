#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <Windows.h>

#define SIZE 32768
#define MOD 256
#define HMOD 128
#define ITERS 1000000

typedef struct 
{
    int arr[SIZE];
    long long sum;
    clock_t start, end;
    double elapsed;
}   stuff;

int compare(const void* arg1, const void* arg2)
{
    return (*(int*)arg1 - *(int*)arg2);
}

unsigned __stdcall sorted_branching(void* args)
{
    stuff* sb = (stuff*)args;    
    srand(_getpid() + rand());
    for (int i = 0; i < SIZE; i++)
    {
        sb->arr[i] = rand() % MOD;
    }
    qsort(sb->arr, SIZE, sizeof(int), compare);
    sb->start = clock();
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (sb->arr[j] >= HMOD)
            {
                sb->sum += sb->arr[j];
            }
        }
    }
    sb->end = clock();
    sb->elapsed = (double)(sb->end - sb->start) / CLOCKS_PER_SEC;
    return 0;
}

unsigned __stdcall sorted_branchless(void* args)
{
    int t = 0;
    stuff* sbl = (stuff*)args;    
    srand(_getpid() + rand());
    for (int i = 0; i < SIZE; i++)
    {
        sbl->arr[i] = rand() % MOD;
    }
    qsort(sbl->arr, SIZE, sizeof(int), compare);
    sbl->start = clock();
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            t = (sbl->arr[j] - HMOD) >> 31;
            sbl->sum += ~t & sbl->arr[j];
        }
    }
    sbl->end = clock();
    sbl->elapsed = (double)(sbl->end - sbl->start) / CLOCKS_PER_SEC;
    return 0;
}

unsigned __stdcall unsorted_branching(void* args)
{
    stuff* usb = (stuff*)args;    
    srand(_getpid() + rand());
    for (int i = 0; i < SIZE; i++)
    {
        usb->arr[i] = rand() % MOD;
    }
    usb->start = clock();
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (usb->arr[j] >= HMOD)
            {
                usb->sum += usb->arr[j];
            }
        }
    }
    usb->end = clock();
    usb->elapsed = (double)(usb->end - usb->start) / CLOCKS_PER_SEC;
    return 0;
}

unsigned __stdcall unsorted_branchless(void* args)
{
    int t = 0;
    stuff* usbl = (stuff*)args;    
    srand(_getpid() + rand());
    for (int i = 0; i < SIZE; i++)
    {
        usbl->arr[i] = rand() % MOD;
    }
    usbl->start = clock();
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            t = (usbl->arr[j] - HMOD) >> 31;
            usbl->sum += ~t & usbl->arr[j];
        }
    }
    usbl->end = clock();
    usbl->elapsed = (double)(usbl->end - usbl->start) / CLOCKS_PER_SEC;
    return 0;
}

int main(void)
{
    stuff sb, sbl, usb, usbl;
    uintptr_t threads[4];
    threads[0] = _beginthreadex(NULL, 0, sorted_branching, &sb, 0, NULL);
    threads[1] = _beginthreadex(NULL, 0, sorted_branchless, &sbl, 0, NULL);
    threads[2] = _beginthreadex(NULL, 0, unsorted_branching, &usb, 0, NULL);
    threads[3] = _beginthreadex(NULL, 0, unsorted_branchless, &usbl, 0, NULL);
    for (int i = 0; i < 4; i++)
    {
        WaitForSingleObject((HANDLE)threads[i], INFINITE);
        CloseHandle((HANDLE)threads[i]);
    }
    printf("\n");
    printf("sorted branching:\ntime: %lf, sum = %lld\n\n", sb.elapsed, sb.sum);
    printf("sorted branchless:\ntime: %lf, sum = %lld\n\n", sbl.elapsed, sbl.sum);
    printf("unsorted branching:\ntime: %lf, sum = %lld\n\n", usb.elapsed, usb.sum);
    printf("unsorted branchless:\ntime: %lf, sum = %lld\n\n", usbl.elapsed, usbl.sum);
    return 0;
}
