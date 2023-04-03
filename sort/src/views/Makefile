CFLAGS= -Wall -Wextra

main: main.c module.o
	gcc $(CFLAGS) main.c module.o -o main
	./main

module: module.c
	gcc $(CFLAGS) -c module.c -o module.o