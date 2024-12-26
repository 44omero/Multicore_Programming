# Multicore Programming - Homework 2

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Implementation Details](#implementation-details)
  - [Custom Read-Write Lock (`my_rwlock_t`)](#custom-read-write-lock-my_rwlock_t)
  - [Linked List Operations](#linked-list-operations)
- [Installation](#installation)
- [Usage](#usage)
  - [Building the Project](#building-the-project)

## Overview

This repository contains the solutions to Homework 2 of the Multicore Programming course. The assignment focuses on implementing efficient synchronization mechanisms for multithreaded linked lists to allow concurrent access by multiple threads. Specifically, it involves:

1. **Implementing Custom Read-Write Locks**: Creating a `my_rwlock_t` type with associated lock and unlock functions using synchronization primitives.
2. **Applying Read-Write Locks to Linked List Operations**: Enhancing `Member()`, `Insert()`, and `Delete()` functions to utilize the custom read-write locks.
3. **Performance Evaluation**: Comparing the performance of the custom read-write locks with the standard `pthread` read-write locks under various workloads.

## Features

- **Custom Read-Write Lock Implementation**: Provides `my_rdlock`, `my_wrlock`, and `my_unlock` functions.
- **Thread-Safe Linked List Operations**: Implements `Member()`, `Insert()`, and `Delete()` functions protected by read-write locks.
- **Performance Benchmarking**: Scripts and tools to run experiments comparing custom and `pthread` read-write locks.
- **Comprehensive Results**: Detailed performance metrics under different operation distributions.

## Implementation Details

### Custom Read-Write Lock (`my_rwlock_t`)

The custom read-write lock is implemented using POSIX synchronization primitives, including mutexes and condition variables. The `my_rwlock_t` structure maintains the state of the lock, tracking active readers, waiting writers, and active writers.

**Key Functions:**
- `int my_rdlock(my_rwlock_t* rwlock_p);`
- `int my_wrlock(my_rwlock_t* rwlock_p);`
- `int my_unlock(my_rwlock_t* rwlock_p);`

### Linked List Operations

The linked list supports three primary operations:
- **Member(int value)**: Checks if a value exists in the list. Utilizes `my_rdlock` for shared access.
- **Insert(int value)**: Inserts a new value into the list. Utilizes `my_wrlock` for exclusive access.
- **Delete(int value)**: Removes a value from the list. Utilizes `my_wrlock` for exclusive access.

Each operation is properly synchronized using the custom read-write locks to ensure thread safety and maximize concurrency.

## Installation

### Prerequisites

Ensure your system has the following installed:

- **Compiler**: GCC (version 9.0 or higher) or Clang
- **Libraries**: POSIX Threads (`pthread`)
- **Build Tools**: Make

### Steps

1. **Clone the Repository**

   ```bash
   git clone https://github.com/44omero/Multicore_Programming.git
   cd Multicore_Programming/Hw2
   ```

2. **Build the Project**

   Use the provided Makefile to compile the source code.

   ```bash
   make
   ```

   This will generate the executable binaries necessary for running the experiments.

## Usage

### Building the Project

After cloning the repository, navigate to the `Hw2` directory and build the project using `make`:

```bash
cd Multicore_Programming/Hw2
make
```

This command compiles all source files and produces executables for the custom and pthread read-write lock implementations.

### Running the Experiments

The project includes executables to run the linked list operations using both custom and `pthread` read-write locks. To perform the experiments as outlined in the assignment, use the following commands:

1. **Custom Read-Write Lock Implementation**

   ```bash
   ./hw2_custom_rwlock <num_threads> <num_elements> <num_operations> <member_ratio> <insert_ratio> <delete_ratio>
   ```

2. **Pthreads Read-Write Lock Implementation**

   ```bash
   ./hw2_pthread_rwlock <num_threads> <num_elements> <num_operations> <member_ratio> <insert_ratio> <delete_ratio>
   ```

**Parameters:**
- `<num_threads>`: Number of concurrent threads (e.g., 8)
- `<num_elements>`: Initial number of elements in the linked list (e.g., 100000)
- `<num_operations>`: Total number of operations to perform (e.g., 1000000)
- `<member_ratio>`: Percentage of `Member` operations (e.g., 99 for 99%)
- `<insert_ratio>`: Percentage of `Insert` operations (e.g., 0.5 for 0.5%)
- `<delete_ratio>`: Percentage of `Delete` operations (e.g., 0.5 for 0.5%)

**Example:**

To run the first experiment with custom read-write locks:

```bash
./hw2_custom_rwlock 8 100000 1000000 99 0.5 0.5
```

And with pthread read-write locks:

```bash
./hw2_pthread_rwlock 8 100000 1000000 99 0.5 0.5
```

## Results

### Experiment Parameters

The experiments were conducted under the following configurations:

1. **Experiment 1**
   - **Threads**: 8
   - **Initial Elements**: 100,000
   - **Total Operations**: 1,000,000
   - **Operation Distribution**:
     - Member: 99%
     - Insert: 0.5%
     - Delete: 0.5%

2. **Experiment 2**
   - **Threads**: 8
   - **Initial Elements**: 100,000
   - **Total Operations**: 1,000,000
   - **Operation Distribution**:
     - Member: 90%
     - Insert: 5%
     - Delete: 5%

3. **Experiment 3**
   - **Threads**: 8
   - **Initial Elements**: 100,000
   - **Total Operations**: 1,000,000
   - **Operation Distribution**:
     - Member: 50%
     - Insert: 25%
     - Delete: 25%
