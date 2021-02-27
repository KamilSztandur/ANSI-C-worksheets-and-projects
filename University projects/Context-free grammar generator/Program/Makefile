CC=gcc
NAME=-o GBKgen
CFLAGS=-Wall

all: main

main: GBK.o GBK_help.o GBK_displayChains.o GBK_displayTree.o
	$(CC) $(CFLAGS) $(NAME) $(^)

GBK.o: GBK.c GBK.h
	$(CC) $(CFLAGS) -c GBK.c

GBK_help.o: GBK_help.c 
	$(CC) $(CFLAGS) -c GBK_help.c

GBK_displayChains.o: GBK_displayChains.c
	$(CC) $(CFLAGS) -c GBK_displayChains.c

GBK_displayTree.o: GBK_displayTree.c 
	$(CC) $(CFLAGS) -c GBK_displayTree.c

