CC = gcc
CFLAGS = -O2 -Wall -g
LFLAGS = -ljpeg -lm -lpthread

all:   sobel_seq sobel_par

sobel_seq:	sobel_seq.o
		$(CC) -o sobel_seq sobel_seq.o $(LFLAGS)

sobel_seq.o:	sobel_seq.c
		$(CC) $(CFLAGS) -c sobel_seq.c


sobel_par:	sobel_par.o
		$(CC) -o sobel_par sobel_par.o $(LFLAGS)

sobel_par.o:	sobel_par.c
		$(CC) $(CFLAGS) -c sobel_par.c



clean:
	       rm -f *~ *.o out.jpg sobel_seq sobel_par

submit:
	tar -czvf hw1_submit.tar.gz Makefile *.c

