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
	pid_t child_pid = -1;

	start = time(NULL); //start the clock
	printf("START: %ld\n",start);

	child_pid = fork();

	// getppid() returns parent PID,
	// getpid() retrurns child PID
	if(child_pid == 0){
		printf("\nI am Child!\n");
		printf("\nChild ID: %d\n", getpid());
	}else{
		int status; 
		waitpid(child_pid,&status, 0);
		printf("\nI am parent!\n");
		printf("\nParent ID: %d\n", getpid());
		printf("RETVAL: %d\n", status);
	}

	stop = time(NULL);
	printf("STOP:  %ld\n",stop);

	return 0;
}//main

