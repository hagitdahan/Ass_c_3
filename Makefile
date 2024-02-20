CC=gcc
FLAGS =-Wall -g

all: StrList

StrList: Main.o StrList.o
	$(CC) $(FLAGS) -o StrList Main.o StrList.o

Main.o: Main.c StrList.h
	$(CC) $(FLAGS) -c Main.c

StrList.o: StrList.c StrList.h
	$(CC) $(FLAGS) -c StrList.c

clean: 
	rm *.o StrList
 