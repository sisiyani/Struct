EXEC = main

all: $(EXEC)

biblioLC.o: biblioLC.c biblioLC.h
	gcc -Wall -c biblioLC.c  -o biblioLC.o

entreeSortieLC.o: entreeSortieLC.c entreeSortieLC.h biblioLC.h
	gcc -Wall -c entreeSortieLC.c -o entreeSortieLC.o
biblioH.o:biblioH.c biblioH.h
	gcc -Wall -c biblioH.c  -o biblioH.o

entreeSortieH.o: entreeSortieH.c entreeSortieH.h biblioH.h
	gcc -Wall -c entreeSortieH.c -o entreeSortieH.o

main.o:main.c entreeSortieLC.h biblioLC.h entreeSortieH.h biblioH.h
	gcc -Wall -c main.c -o main.o

main: main.o biblioLC.o entreeSortieLC.o entreeSortieH.o biblioH.o
	gcc -Wall main.o biblioLC.o entreeSortieLC.o entreeSortieH.o biblioH.o -o main

clean :
	rm -f *.o
	rm -f prog
