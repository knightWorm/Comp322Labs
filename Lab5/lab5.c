#include <stdlib.h>
#include <stdio.h>

// main
int main(int argc, char * args[]){
	// if the argc < 1 no need for further exploration so it will be caught here and exit program.
	if(argc <= 1){
		printf("invalid input!\n");
		exit(0);
	}

	// variables to hold page information
	int size = 4096; // to hold 4k

	// converting the input into int for the mem address
	int address = atoi(args[1]);

	// display info

	printf("The address: %d contains\nPage number: %d\nOffset: %d\n",address,address/size,address%size);

	return 0;
}// end og main function
	// int offset;
	// int pageNum;

	// pageNum = address / size;

	// offset = address % size;