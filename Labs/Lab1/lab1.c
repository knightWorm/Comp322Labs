#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void childParentProcessing(int* processStatus, pid_t * pId);

int main(int argv,char * args[]){
	time_t start, stop; 
	int status; 

	start = time(NULL); //start the clock
	printf("START: %ld\n",start);

	//if the child id remains awith value of -1 after code line 19 
	// then there is a problem statrting the child process... terminate the program.
	pid_t currentProcessID = fork();
	if(currentProcessID == -1){
		printf("Error: child process did not initiate!\n");
		exit(1);
	}

	// getppid() returns parent PID,
	// getpid() retrurns child PID
	//if child pid  == 0 then exe code for child
	// else child pid will be positice and exe code for parent. 
	if(currentProcessID == 0){
		//printf("I am Child!\n");

		childParentProcessing(NULL,NULL);

	}else{
		//printf("I am parent!\n");

		waitpid(currentProcessID,&status, 0);

		childParentProcessing(&status,&currentProcessID);

		//the times needs to be stopped here because this sould be the last program to run.

		sleep(10);// to delay the time difference 10 seconds

		printf("STOP:  %ld\n",time(NULL));
	}

	return 0;
}//main

// Function manages the different process and displays their results.
void childParentProcessing(int* processStatus, pid_t* pId)
{
	pid_t getPId = getpid();
	pid_t getPPId = getppid();

	if(processStatus == NULL && pId == NULL)
	{
		printf("PPID: %d, PID: %d\n",getPPId, getPId);

	}else
	{
		printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %u\n",getPPId, getPId, *pId,*processStatus);
	}
}//childParentProcessing

/* Question to ask: 
* is there a way to twll which memory blocked are used for child/parent procesis. 
* how to stop a self influxed fork attack
* is there a waty to get the time formatted to US dependencuy stds or ajsut work it put?
*
*/