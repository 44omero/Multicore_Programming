#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>

#define SIZE 1024 //matrix size

void initialize_matrix(double *matrix) {
    for(int i = 0; i < SIZE * SIZE; ++i) {
        matrix[i] = (double)rand() / RAND_MAX; //Dividing to randmax to get a random number between 0 and 1
    }
}

double multiply_matrices(const double *A, const double *B, double *C,
                        int num_threads, const char *schedule_type, int chunk_size) {
    
    double start_time, end_time;

    // Determine/set the number of threads, schedule type and chunksizes
    omp_set_num_threads(num_threads);

    omp_sched_t sched_kind;
    if(strcmp(schedule_type, "static") == 0) {
        sched_kind = omp_sched_static;
    }
    else if(strcmp(schedule_type, "dynamic") == 0) {
        sched_kind = omp_sched_dynamic;
    }
    else if(strcmp(schedule_type, "guided") == 0) {
        sched_kind = omp_sched_guided;
    }
    else {
        printf("Unknown schedule type '%s'. Using 'static' as default.\n", schedule_type);
        sched_kind = omp_sched_static;
    }

    if(chunk_size > 0) {
        omp_set_schedule(sched_kind, chunk_size);
    }
    else {
        omp_set_schedule(sched_kind, 0);//default
    }

    start_time = omp_get_wtime();

    //Matrix multiplication part
    #pragma omp parallel for schedule(runtime) collapse(2)
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            double sum = 0.0;
            for(int k = 0; k < SIZE; ++k) {
                sum += A[i * SIZE + k] * B[k * SIZE + j];
            }
            C[i * SIZE + j] = sum;
        }
    }
    end_time = omp_get_wtime();

    return end_time - start_time; //returns execution time
}

int main() {
    // RNG seed
    srand((unsigned int)time(NULL));

    double *A = (double *)malloc(sizeof(double) * SIZE * SIZE);
    double *B = (double *)malloc(sizeof(double) * SIZE * SIZE);
    double *C = (double *)malloc(sizeof(double) * SIZE * SIZE);

    if(A == NULL || B == NULL || C == NULL) { //break if matrices empty
        printf("Memory allocation failed.\n");
        return -1;
    }

    printf("Initializing matrices A and B with random numbers...\n");
    initialize_matrix(A);
    initialize_matrix(B);
    printf("Initialization complete.\n");

    const char *schedules[] = {"static", "dynamic", "guided"};//schedule types
    int num_schedules = sizeof(schedules) / sizeof(schedules[0]);

    int thread_counts_a[] = {2, 4, 8, 16}; // given thread counts
    int num_thread_a = sizeof(thread_counts_a) / sizeof(thread_counts_a[0]);

    printf("\n--- Varying Number of Threads with Default Chunk Size ---\n");
    printf("Schedule Type | Threads | Execution Time (s)\n");
    printf("--------------------------------------------\n");

    for(int s = 0; s < num_schedules; ++s) {
        for(int t = 0; t < num_thread_a; ++t) {
            memset(C, 0, sizeof(double) * SIZE * SIZE);// Reset matrix C

            double exec_time = multiply_matrices(A, B, C, thread_counts_a[t], schedules[s], 0);
            printf("%-13s | %-7d | %.6f\n", schedules[s], thread_counts_a[t], exec_time);
        }
    }

    int thread_fixed = 16;
    int chunk_sizes_b[] = {4, 16, 32, 64}; //given chunk sizes
    int num_chunk_b = sizeof(chunk_sizes_b) / sizeof(chunk_sizes_b[0]);

    printf("\n--- Varying Chunk Sizes with 16 Threads ---\n");
    printf("Schedule Type | Chunk Size | Execution Time (s)\n");
    printf("----------------------------------------------\n");

    for(int s = 0; s < num_schedules; ++s) {
        for(int c = 0; c < num_chunk_b; ++c) {
            memset(C, 0, sizeof(double) * SIZE * SIZE);// Reset matrix C 

            double exec_time = multiply_matrices(A, B, C, thread_fixed, schedules[s], chunk_sizes_b[c]);
            printf("%-13s | %-10d | %.6f\n", schedules[s], chunk_sizes_b[c], exec_time);
        }
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
