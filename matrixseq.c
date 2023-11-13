#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int rows, cols1, cols2;

int main(int argc, char* argv[]) {
    clock_t start_time = clock();

    rows = atoi(argv[1]);
    cols1 = atoi(argv[2]);
    cols2 = atoi(argv[3]);

    int matrix1[rows][cols1];
    int matrix2[cols1][cols2];
    int result[rows][cols2];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols1; j++) {
            matrix1[i][j] = rand() % 100 + 1;
        }
    }

    for (int i = 0; i < cols1; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i][j] = rand() % 100 + 1;
        }
    }

    for (int x = 0; x < rows; x++) {
        for (int z = 0; z < cols2; z++) {
            for (int i = 0; i < cols1; i++) {  // Fixed this line
                result[x][z] += matrix1[x][i] * matrix2[i][z];
            }
        }
    }

    /*
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", result[i][j]);
        }
        printf(" ");
    }
    */

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
