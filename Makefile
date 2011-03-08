# ache; Cheng, Alaln

CC = g++

all: avl

avl: avl.o
	$(CC) -o avl avl.o

avl.o: avl.cpp classes.h
	$(CC) -o avl.o -c -O3 -g avl.cpp

clean:
	rm avl.o avl
