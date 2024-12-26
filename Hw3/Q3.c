#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

int thread_count;

void count_sort(int a [], int n) {
    int i , j , count;
    int *temp = malloc (n * sizeof(int));

    #pragma omp parallel for private(i, j, count) shared(a, temp)
    for (i = 0; i < n ; i++) {
        thread_count = omp_get_num_threads();
        count = 0;
        for (j = 0; j < n; j++){
            if (a[j] < a[i])
                count++;
            else if ( a[j] == a[i] && j < i)
                count++;
        }
        temp[count] = a[i];
    }
    memcpy (a , temp, n * sizeof(int));
    free(temp );
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <array_length>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Array length must be a positive integer.\n");
        return 1;
    }

    int *a = malloc(n * sizeof(int));
    if (!a) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000; // RNG 0-99
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%2d|", a[i]);
    }
    printf("\n");

    double start_time, finish_time;
    
    start_time = omp_get_wtime();
    count_sort(a, n);
    finish_time = omp_get_wtime();
    printf("Thread number : %2d\n", thread_count);
    printf("Sorted array  : ");
    for (int i = 0; i < n; i++) {
        printf("%2d|", a[i]);
    }
    printf("\n");
    printf("Elapsed time : %.6f\n", finish_time-start_time);
    free(a);
    return 0;
}