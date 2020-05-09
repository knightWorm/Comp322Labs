  
CFLAGS=-Wall -Wextra

all: spiritd moles clean
.PHONY : all

spiritd: spiritd.o
	gcc -o spiritd spiritd.o

moles: mole.o
	gcc -o moles mole.o
clean: 
	rm *.o