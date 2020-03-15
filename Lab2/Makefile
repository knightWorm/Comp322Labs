  
CFLAGS=-Wall -Wextra

all: launch tube clean
.PHONY : all

launch: lab2.o
	gcc -o launch lab2.o

tube: tube.o
	gcc -o tube tube.o
clean: 
	rm *.o