main: main.o studenti.o
	gcc -o main main.o studenti.o

main.o: main.c studenti.h
	gcc -c main.c

studenti.o: studenti.c studenti.h
	gcc -c studenti.c