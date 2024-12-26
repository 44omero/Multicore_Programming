# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2 -lm
OMP_FLAGS = -fopenmp

# Executables
EXECUTABLES = Q2 Q3 Q4 Q5

# Targets
all  : $(EXECUTABLES)

Q2: Q2.c
	$(CC) $(CFLAGS) $(OMP_FLAGS) -o $@ $<

Q3: Q3.c
	$(CC) $(CFLAGS) $(OMP_FLAGS) -o $@ $<
	
Q4: Q4.c
	$(CC) $(CFLAGS) $(OMP_FLAGS) -o $@ $<

Q5: Q5.c
	$(CC) $(CFLAGS) $(OMP_FLAGS) -o $@ $<

	
# Clean target
clean:
	rm -f $(EXECUTABLES)
clear:
	rm -f $(EXECUTABLES)
clr:
	rm -f $(EXECUTABLES)

