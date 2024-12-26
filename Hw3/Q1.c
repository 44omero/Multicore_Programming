a [0] = 0; 
#pragma omp parallel for num_threads(thread_count) 
for (i = 1; i < n; i++) 
    a[i] = i * (i + 1) / 2; 