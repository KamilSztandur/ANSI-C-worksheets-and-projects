CC = gcc
PNG = -lpng
MATH = -lm
NAME = sim.out


all: ./guts/stats.o ./guts/input.o ./guts/create_txt.o ./guts/sprinklers.o ./guts/create_png.o ./guts/drawInArray.o ./guts/algorithm.o ./guts/common.o ./guts/main.o
	$(CC) $^ -Wall $(MATH) $(PNG) -o $(NAME)

./guts/main.o: ./src/main.c ./src/tab.h ./src/input.h ./src/algorithm.h
	$(CC) -c ./src/main.c
	mv main.o guts

./guts/drawInArray.o: ./src/drawInArray.c ./src/tab.h
	$(CC) -c ./src/drawInArray.c
	mv drawInArray.o guts

./guts/create_png.o: ./src/create_png.c ./src/tab.h
	$(CC) -c ./src/create_png.c
	mv create_png.o guts

./guts/sprinklers.o: ./src/sprinklers.c ./src/tab.h
	$(CC) -c ./src/sprinklers.c
	mv sprinklers.o guts

./guts/create_txt.o: ./src/create_txt.c ./src/tab.h
	$(CC) -c ./src/create_txt.c
	mv create_txt.o guts

./guts/input.o: ./src/input.c ./src/input.h
	$(CC) -c ./src/input.c
	mv input.o guts

./guts/stats.o: ./src/stats.c ./src/stats.h
	$(CC) -c ./src/stats.c
	mv stats.o guts

./guts/algorithm.o: ./src/algorithm.c ./src/algorithm.h ./src/tab.h ./src/common.h
	$(CC) -c ./src/algorithm.c
	mv algorithm.o guts

./guts/common.o: ./src/common.c ./src/common.h
	$(CC) -c ./src/common.c
	mv common.o guts