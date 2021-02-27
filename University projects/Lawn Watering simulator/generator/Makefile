CC=gcc
NAME=generuj.out

all: gen.o
	$(CC) $^ -o $(NAME)
	mv $(NAME) ..

gen.o: gen.c
	$(CC) -c gen.c
