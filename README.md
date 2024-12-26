# Multicore Programming Homework Repository

This repository contains solutions, code, and documentation for the **CS 435/535 - Multicore Programming** course. The homework assignments focus on exploring and analyzing various concepts in multicore programming, including parallelization, synchronization, and performance optimization.

## Repository Structure

The repository is organized into subdirectories for each homework assignment:

### Homework 1: Serial and Parallel Sobel Filter
- **Focus**: Implementation and performance analysis of serial and parallel Sobel filter algorithms using pthreads.
- **Key Files**:
  - `sobel_seq.c`: Serial implementation.
  - `sobel_par.c`: Parallel implementation.
  - Example input/output images.
  - `hw1.pdf`: Assignment description and guidelines.
- **Highlights**:
  - Profiling using tools like Intel Vtune and `likwid`.
  - Analysis of CPU performance for varying thread counts.

### Homework 2: Read-Write Locks and Linked List
- **Focus**: Implementation of custom read-write locks and their application in a concurrent linked list.
- **Key Files**:
  - `rwlocks_imp.c`: Custom read-write lock implementation.
  - `pth_ll_rwl.c`: Linked list protected with custom read-write locks.
  - `hw2.pdf`: Assignment description.
- **Highlights**:
  - Performance comparison between custom and pthreads read-write locks.
  - Execution time analysis for different operation distributions.

### Homework 3: OpenMP Programming and Parallel Algorithms
- **Focus**: Parallel programming concepts using OpenMP, including loop dependencies, critical sections, and scheduling policies.
- **Key Files**:
  - `Q1.c` to `Q5.c`: Solution codes for various tasks, including matrix multiplication and sorting algorithms.
  - `hw3.pdf`: Assignment description.
- **Highlights**:
  - Exploring OpenMP directives for parallelization.
  - Comparing scheduling policies (static, dynamic, guided).

## Requirements
- **Languages**: C with OpenMP and pthreads.
- **Tools**: GCC or compatible C compiler, OpenMP-enabled environment, profiling tools (`likwid`, `gprof`, Intel Vtune).
- **Dependencies**: Ensure all system libraries (e.g., pthreads, OpenMP) are installed.

## Compilation and Execution
Each homework folder includes a `Makefile` for convenient compilation. To build and run the solutions:
1. Navigate to the desired homework folder.
2. Compile using:
   ```bash
   make
   ```
3. Run the executables as specified in the respective README files.

## Author
- **Ömer Öztürk**

## License
This repository is intended for educational purposes and may not be used for commercial applications.
