# Multicore Programming - Homework 3

This repository contains the solutions and code files for Homework 3 of the Multicore Programming course (CS 435/535, Fall 2024). The homework focuses on concepts like loop-carried data dependencies, critical sections, OpenMP parallelization directives, and scheduling policies in multicore programming.

## Repository Structure

- **`hw3.pdf`**: Homework description detailing the problems and requirements.
- **`hw3_omerozturk.pdf`**: Solutions document containing detailed explanations and analyses for each question.
- **`Q1.c`**: Solution code for Question 1 - Eliminating loop-carried data dependencies and parallelizing the loop.
- **`Q2.c`**: Solution code for Question 2 - Testing OpenMP atomic operations versus critical sections.
- **`Q3.c`**: Solution code for Question 3 - Parallel implementation of the count sort algorithm.
- **`Q4.c`**: Solution code for Question 4 - Exploring OpenMP parallelization directives and thread behavior.
- **`Q5.c`**: Solution code for Question 5 - Matrix multiplication using OpenMP with various scheduling policies.
- **`Makefile`**: Makefile to compile the provided solution codes.

## Questions Overview

### Question 1: Loop-Carried Data Dependencies
- **Objective**: Eliminate loop-carried dependencies to enable parallelization.
- **Code**: `Q1.c`
- **Solution**: Identifies a pattern for computation to make iterations independent, thus allowing for parallel execution.

### Question 2: Critical Sections vs Atomic Operations
- **Objective**: Evaluate whether atomic directives in OpenMP are treated as a single critical section.
- **Code**: `Q2.c`
- **Solution**: Tests and concludes that atomic directives allow independent operations on different memory locations.

### Question 3: Parallelizing Count Sort
- **Objective**: Implement a parallel version of the count sort algorithm.
- **Code**: `Q3.c`
- **Solution**: Analyzes variable scoping, eliminates loop dependencies, and provides a parallel implementation.

### Question 4: OpenMP Parallelization Directives
- **Objective**: Understand the behavior of threads under different OpenMP directives.
- **Code**: `Q4.c`
- **Solution**: Demonstrates thread output with `firstprivate` and the `#pragma omp for` directive.

### Question 5: OpenMP Programming and Schedules
- **Objective**: Analyze the performance of different scheduling policies in OpenMP.
- **Code**: `Q5.c`
- **Solution**: Implements parallel matrix multiplication and compares scheduling policies (static, dynamic, guided) under varying conditions.

## Compilation and Execution

1. **Compiling the Code**:
   Use the provided `Makefile` to compile the solutions. Run the following command:
   ```
   make
   ```
   This will generate executable files for each solution (e.g., `Q1`, `Q2`, etc.).

2. **Running the Programs**:
   Execute the compiled binaries by running:
   ```
   ./Q1
   ./Q2
   ./Q3
   ./Q4
   ./Q5
   ```

## Results and Analysis
The detailed results and explanations for each question are included in `hw3_omerozturk.pdf`. This document provides the rationale behind each solution and the observed outcomes from the experiments.

## Requirements

- **Compiler**: A C compiler supporting OpenMP (e.g., GCC).
- **Libraries**: Ensure OpenMP is enabled (use the `-fopenmp` flag during compilation).

## Author
- **Ömer Öztürk**

## License
This repository is intended for educational purposes and may not be used for commercial applications.
- **Student ID**: S046798

## License
This repository is intended for educational purposes and is not licensed for commercial use.

