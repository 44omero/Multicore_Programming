#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int x = 0;
    int y = 0;

    #pragma omp parallel num_threads(2) firstprivate(x,y)
    {
        int my_rank = omp_get_thread_num();
        printf("Thread: %d\n", my_rank);

        // First loop
        for (int i = 0; i < 4; i++) {
            x += i;
        }
        printf("Thread %d running first loop, result: %d\n", my_rank, x);

        // Second loop
        #pragma omp for
        for (int i = 0; i < 4; i++) {
            #pragma omp atomic
            y += i;
        }
        printf("Thread %d running second loop, result: %d\n", my_rank, y);
    }

    return 0;
}
