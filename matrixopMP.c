#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "omp.h"

int m, n, k;
int **matrix1, **matrix2, **ans;
int numofthreads;

int main(int argc, char **argv)
{
    printf("ana wen\n");
    clock_t start_time = clock();
    if (argc != 3)
    {
        printf("error");
        return 1;
    }

    m = atoi(argv[1]);
    n = atoi(argv[1]);
    k = atoi(argv[1]);
    numofthreads = atoi(argv[2]);

    int *values = (int *)malloc(m * n * sizeof(int));

    matrix1 = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i)
    {
        matrix1[i] = &values[i * n];
    }

    int *values1 = (int *)malloc(n * k * sizeof(int));

    matrix2 = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i)
    {
        matrix2[i] = &values1[i * k];
    }

    int *values2 = (int *)malloc(m * k * sizeof(int));

    ans = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i)
    {
        ans[i] = &values2[i * k];
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            ans[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix1[i][j] = rand() % 100 + 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            matrix2[i][j] = rand() % 100 + 1;
        }
    }

    int region = m / numofthreads;

    omp_set_num_threads(numofthreads);
#pragma omp parallel for schedule(static, region)
    for (int x = 0; x < m; x++)
    {
        for (int z = 0; z < k; z++)
        {
            for (int i = 0; i < n; i++)
            {
                ans[x][z] += matrix1[x][i] * matrix2[i][z];
            }
        }
    }

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);
    return 0;
}
