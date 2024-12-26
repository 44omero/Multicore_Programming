# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -g -Wall

# Libraries to link
LIBS = -lpthread

# Target executables
#TARGET1 = pth_ll_custom_rwlock
#TARGET2 = test_program
TARGET3 = rwlocks_imp

# Source files for each target
#SRCS1 = pth_ll_custom_rwlock.c my_rand.c
#SRCS2 = test_program.c my_rand.c
SRCS3 = rwlocks_imp.c my_rand.c

# Object files for each target
#OBJS1 = $(SRCS1:.c=.o)
#OBJS2 = $(SRCS2:.c=.o)
OBJS3 = $(SRCS3:.c=.o)

# Default target builds all executables
#all: $(TARGET1) $(TARGET2) $(TARGET3)
all: $(TARGET3)

# Rules to link executables
#$(TARGET1): $(OBJS1)
#	$(CC) $(CFLAGS) -o $(TARGET1) $(OBJS1) $(LIBS)

#$(TARGET2): $(OBJS2)
#	$(CC) $(CFLAGS) -o $(TARGET2) $(OBJS2) $(LIBS)

$(TARGET3): $(OBJS3)
	$(CC) $(CFLAGS) -o $(TARGET3) $(OBJS3) $(LIBS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	#rm -f $(TARGET1) $(TARGET2) $(TARGET3) *.o
	rm -f $(TARGET3) *.o

# Phony targets
.PHONY: all clean
