CC=gcc
NAME=-o MT_solver
CFLAGS=-Wall

all: main

main: main.o help.o inputGen.o solver.o interpreter.o
	$(CC) $(CFLAGS) $(NAME) $(^)

main.o: main.c MT.h
	$(CC) $(CFLAGS) -c main.c

help.o: help.c 
	$(CC) $(CFLAGS) -c help.c

inputGen.o: inputGen.c
	$(CC) $(CFLAGS) -c inputGen.c

solver.o: solver.c
	$(CC) $(CFLAGS) -c solver.c

interpreter.o: interpreter.c
	$(CC) $(CFLAGS) -c interpreter.c

clean:
	rm inputGen.o
	rm main.o
	rm help.o
	rm interpreter.o
	rm solver.o
