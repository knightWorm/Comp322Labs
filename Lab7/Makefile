CFLAGS=-Wall -Wextra

all: matrix_gen matrix_add 

matrix_gen: lab7_1.c
	gcc lab7_1.c -lpthread -o matrix_gen

matrix_add: lab7_2.c
	gcc lab7_2.c -lpthread -o matrix_add

clean:
	rm -rf *.o 