#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void childParentProcessing(int processStatus, pid_t pId);

int main(int argv,char * args[]){ 
	int status =0;
	if(argv <= 1){
		printf("Invalid input!\n"); // this is done becasue the suser might not provide the command to be operated and also gets rid of the warning on my compiler for unuse vars
		exit(1);
	}

	//if the child id remains awith value of -1 after code line 19 
	// then there is a problem statrting the child process... terminate the program.
	pid_t currentProcessID = fork();
	if(currentProcessID == -1){
		printf("Error: child process did not initiate!\n");
		exit(1);//no need to exit. 
	}

	// getppid() returns parent PID,
	// getpid() retrurns child PID
	//if child pid  == 0 then exe code for child
	// else child pid will be positice and exe code for parent. 
	if(currentProcessID == 0){
		execve(args[1],args +1,NULL); // i wont set this to an int becasue it won't be checking for failure
	
		perror("Could not excute");
		exit(1);

	}else{
	   fprintf(stderr,"%s: $$ = %d\n",args[1],currentProcessID);

	   waitpid(currentProcessID,&status, 0);//change status parameter to signal the next program exec.

	   if(WIFEXITED(status) != 0){
	   		fprintf(stderr,"%s: $? = %d\n",args[1],WEXITSTATUS(status));
	   		
	   }

	}

	return 0;
}//main

