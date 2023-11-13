#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int n, m, k;
int numofthreads;
int **matrix1, **matrix2, **ans;

void *runner(void *arg)
{
    int tid = *(int *)arg;
    int start = tid * m / numofthreads;
    int end = (tid + 1) * m / numofthreads;

    for (int o = start; o < end; o++)
    {
        for (int z = 0; z < k; z++)
        {
            for (int i = 0; i < n; i++)
            {
                ans[o][z] += matrix1[o][i] * matrix2[i][z];
            }
        }
    }

    free(arg); // Free the memory allocated for thread ID
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        printf("Usage: %s <m> <n> <k> <numofthreads>\n", argv[0]);
        return 1;
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);
    k = atoi(argv[3]);
    numofthreads = atoi(argv[4]);

    // Allocate memory for matrix1
    matrix1 = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i)
    {
        matrix1[i] = (int *)malloc(n * sizeof(int));
    }

    // Allocate memory for matrix2
    matrix2 = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i)
    {
        matrix2[i] = (int *)malloc(k * sizeof(int));
    }

    // Allocate memory for ans
    ans = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i)
    {
        ans[i] = (int *)malloc(k * sizeof(int));
    }

    // Initialize matrices and perform matrix multiplication
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

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            ans[i][j] = 0;
        }
    }

    pthread_t threads[numofthreads];
    clock_t start_time = clock();
    int region = m / numofthreads;

    for (int i = 0; i < numofthreads; i++)
    {
        int *tid = (int *)malloc(sizeof(int));
        *tid = i;

        pthread_create(&threads[i], NULL, runner, (void *)tid);
    }

    for (int i = 0; i < numofthreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);

    // Free allocated memory
    for (int i = 0; i < m; ++i)
    {
        free(matrix1[i]);
    }
    free(matrix1);

    for (int i = 0; i < n; ++i)
    {
        free(matrix2[i]);
    }
    free(matrix2);

    for (int i = 0; i < m; ++i)
    {
        free(ans[i]);
    }
    free(ans);

    return 0;
}
