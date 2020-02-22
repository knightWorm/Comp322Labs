#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
//#include <sys/wait.h> 
#include <unistd.h>

void printShit(int i);

int main(int argv,char * args[]){
	time_t start, stop; 

	start = time(NULL); //start the clock
	printf("START: %ld\n",start);

	if(fork() == 0){
		printf("\nI am Child!\n");
	}else{
		printf("\nI am  parent!\n");
	}

	stop = time(NULL);
	printf("STOP:  %ld\n",stop);

	return 0;
}//main