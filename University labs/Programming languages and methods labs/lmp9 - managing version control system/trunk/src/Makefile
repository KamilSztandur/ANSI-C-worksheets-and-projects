CC=gcc
CFLAGS=-Wall
NAME=-o

all: mat_io.o backsubst.o gauss.o main.o
	$(CC) $^ $(NAME) gauss

mat_io.o: mat_io.h mat_io.c 
	$(CC) $(CFLAGS) -c $^

backsubst.o: backsubst.h backsubst.c
	$(CC) $(CFLAGS) -c $^

gauss.o: gauss.h gauss.c
	$(CC) $(CFLAGS) -c $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^
