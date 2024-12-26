#include <stdio.h>
#include <omp.h>
#include <math.h>

int main() {
    int n = 10000000;
    double start_time, end_time;

    int thread_counts[] = {1, 2, 4, 8, 16};
    int num_tests = sizeof(thread_counts) / sizeof(thread_counts[0]);

    printf("Thread Count | Atomic Time (s) | Critical Time (s)\n");
    printf("--------------------------------------------------\n");

    // Iterate through each thread count
    for (int t = 0; t < num_tests; t++) {
        int thread_count = thread_counts[t];

        // Test with atomic
        start_time = omp_get_wtime();
        #pragma omp parallel num_threads(thread_count)
        {
            double sum = 0.0;
            int i;
            //#pragma omp for
            for (i = 0; i < n; i++) {
                #pragma omp atomic
                sum += sin(i);
                #pragma omp atomic
                sum += cos(i);

            }
        }
        end_time = omp_get_wtime();
        double atomic_time = end_time - start_time;

        // Test with critical
        start_time = omp_get_wtime();
        #pragma omp parallel num_threads(thread_count)
        {
            double sum = 0.0;
            int i;
            //#pragma omp for
            for (i = 0; i < n; i++) {
                #pragma omp critical
                sum += sin(i);
                sum += cos(i);
            }
        }
        end_time = omp_get_wtime();
        double critical_time = end_time - start_time;

        printf("%12d | %15.6f | %15.6f\n",
               thread_count, atomic_time, critical_time);
    }

    return 0;
}


