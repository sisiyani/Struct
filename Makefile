EXEC = main

all: $(EXEC)

main: main.c biblioLC.o entreeSortieLC.o
	gcc -Wall main.c biblioLC.o entreeSortieLC.o -o main

main.o:main.c entreeSortieLC.h biblioLC.h
	gcc -Wall -c main.c -o main.o
	
entreeSortieLC.o: entreeSortieLC.c entreeSortieLC.h biblioLC.h
	gcc -Wall -c entreeSortieLC.c -o biblioLC.o

biblioLC.o: biblioLC.c biblioLC.h
	gcc -Wall -c biblioLC.c  -o biblioLC.o
