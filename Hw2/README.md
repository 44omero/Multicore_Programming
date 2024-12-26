# Multicore Programming - Homework 2

## Overview
This repository contains the code and resources for Homework 2 of the CS 435/535 course on Multicore Programming. The assignment focuses on the implementation and analysis of concurrent access to a linked list using custom read-write locks.

## Files

- **`hw2.pdf`**: The homework description, including the problem statement and requirements.
- **`rwlocks_imp.c`**: Implementation of custom read-write locks.
- **`pth_ll_rwl.c`**: Code for the linked list protected with custom read-write locks.
- **`my_rand.h` & `my_rand.c`**: Utility functions for random number generation.
- **`timer.h`**: Utility for measuring execution time.
- **`Makefile`**: File for compiling the project.

## Homework Tasks

### Question: Implementation of Read-Write Locks
#### Part A: Implementation
Develop a custom read-write lock implementation using synchronization primitives (e.g., mutex, semaphores, conditional variables). The implementation includes the following functions:

- `int my_rdlock(my_rwlock_t* rwlock_p);`
- `int my_wrlock(my_rwlock_t* rwlock_p);`
- `int my_unlock(my_rwlock_t* rwlock_p);`

#### Part B: Performance Analysis
Compare the performance of the linked list protected with your custom read-write locks against the implementation using pthreads’ read-write locks. Use the following parameters for the comparison:

1. 8 threads, 100,000 elements, 1,000,000 operations; 99% `member`, 0.5% `insert`, 0.5% `delete`.
2. 8 threads, 100,000 elements, 1,000,000 operations; 90% `member`, 5% `insert`, 5% `delete`.
3. 8 threads, 100,000 elements, 1,000,000 operations; 50% `member`, 25% `insert`, 25% `delete`.

## Compilation and Execution

1. **Compile the Code**
   Use the `Makefile` to compile the project. Run:
   ```bash
   make
   ```

2. **Run the Program**
   Execute the program with the following command:
   ```bash
   ./<executable_name> [arguments]
   ```
   Replace `<executable_name>` with the appropriate executable generated during compilation.

## Results
The performance analysis results are reported based on execution time comparisons between custom and pthreads’ read-write locks.

## Requirements
- GCC compiler
- POSIX Threads Library (pthreads)

## Author
Ömero

## Notes
Ensure all dependencies are correctly installed and the system supports POSIX threads for proper functionality.

