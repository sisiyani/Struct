EXEC = main

all: main timeH

main: main.o biblioLC.o entreeSortieLC.o entreeSortieH.o biblioH.o
	gcc -o main biblioLC.o entreeSortieLC.o entreeSortieH.o biblioH.o main.o

main.o:main.c entreeSortieLC.h biblioLC.h entreeSortieH.h biblioH.h
	gcc -Wall -c main.c

timeH: time.o biblioLC.o biblioH.o entreeSortieH.o entreeSortieLC.o
	gcc -o timeH time.o biblioLC.o biblioH.o entreeSortieH.o entreeSortieLC.o 

time.o:time.c entreeSortieLC.h biblioLC.h entreeSortieH.h biblioH.h
	gcc -Wall -c time.c -o time.o

entreeSortieLC.o: entreeSortieLC.c entreeSortieLC.h biblioLC.h
	gcc -Wall -c entreeSortieLC.c

biblioLC.o: biblioLC.c biblioLC.h
	gcc -Wall -c biblioLC.c

entreeSortieH.o: entreeSortieH.c entreeSortieH.h biblioH.h
	gcc -Wall -c entreeSortieH.c

biblioH.o:biblioH.c biblioH.h
	gcc -Wall -c biblioH.c



clean :
	rm -f *.o
	rm -f prog
