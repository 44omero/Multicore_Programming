Here’s the corrected and well-formatted README file:

```markdown
# Homework 2: Parallel Mandelbrot Set Computation

This project is part of the **Multicore Programming** course and focuses on parallelizing the computation of the Mandelbrot set using Pthreads, OpenMP, and MPI.

## Project Structure

- `mandelbrot_pthread.c`: Implementation using Pthreads.
- `mandelbrot_openmp.c`: Implementation using OpenMP.
- `mandelbrot_mpi.c`: Implementation using MPI.
- `Makefile`: For building the executables.
- `README.md`: This file.

## Features

- **Pthreads Implementation**: Utilizes POSIX threads to parallelize the Mandelbrot set computation across multiple CPU cores.
- **OpenMP Implementation**: Employs OpenMP directives for parallel processing.
- **MPI Implementation**: Uses the Message Passing Interface to distribute the computation across multiple processes, potentially on different nodes in a cluster.

## Installation

Ensure you have the necessary compilers and libraries installed:

- GCC compiler with Pthreads support.
- OpenMP library.
- MPI library (e.g., MPICH or OpenMPI).

Clone the repository:

```bash
git clone https://github.com/44omero/Multicore_Programming.git
cd Multicore_Programming/Hw2
```

Build the executables:

```bash
make all
```

This will generate the following executables:

- `mandelbrot_pthread`
- `mandelbrot_openmp`
- `mandelbrot_mpi`

## Usage

Each program generates a PNG image of the Mandelbrot set.

### Pthreads Version

```bash
./mandelbrot_pthread output.png 1000 -2.0 1.0 -1.5 1.5 1920 1080
```

### OpenMP Version

```bash
./mandelbrot_openmp output.png 1000 -2.0 1.0 -1.5 1.5 1920 1080
```

### MPI Version

```bash
mpirun -np 4 ./mandelbrot_mpi output.png 1000 -2.0 1.0 -1.5 1.5 1920 1080
```

**Parameters**:

- `output.png`: Name of the output image file.
- `1000`: Maximum number of iterations.
- `-2.0 1.0`: Real axis range.
- `-1.5 1.5`: Imaginary axis range.
- `1920 1080`: Image width and height in pixels.

```

