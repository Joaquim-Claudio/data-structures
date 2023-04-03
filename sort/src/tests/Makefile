module: ../modules/module.c
	gcc -Wall -Wextra -c ../modules/module.c -o module.o

unity: unity.c
	gcc -Wall -Wextra -c unity.c -o unity.o

test: test.c ../modules/module.o unity.o
	gcc -Wall -Wextra test.c ../modules/module.o unity.o -o test
	./test
