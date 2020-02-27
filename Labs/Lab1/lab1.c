#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void childParentProcessing(pid_t processStatus, pid_t pId);

int main(int argv,char * args[]){
	time_t start, stop; 
	int status; 

	start = time(NULL); //start the clock
	printf("START: %ld\n",start);

	//if the child id remains with value of -1 after code line 19 
	// then there is a problem statrting the child process... terminate the program.
	pid_t currentProcessID = fork();
	if(currentProcessID == -1){
		printf("Error: child process did not initiate!\n");
		exit(1);
	}

	// getppid() returns parent PID,
	// getpid() retrurns child PID
	//if child pid  == 0 then 0 will be pass to the childrenparentprocessing because the child proces is running. 
	// else we are in parent process, child is done and now pass current process Id and the status obtained by waitpid();
	if(currentProcessID == 0){
		//printf("I am Child!\n");

		childParentProcessing(0,0);

	}else{
		//printf("I am parent!\n");

		waitpid(currentProcessID,&status, 0);

		childParentProcessing(status,currentProcessID);

		sleep(10);// to delay the time difference 10 seconds

		//the time needs to be stopped here because this should be the last process to run
                printf("STOP:  %ld\n",time(NULL));
	}

	return 0;
}//main

// Function manages the different process and displays their results.
void childParentProcessing(int processStatus, pid_t pId)
{
        pid_t pid= getpid();
	pid_t ppid = getppid();

	if(processStatus == 0 && pId == 0)
	{
		printf("PPID: %d, PID: %d\n",ppid, pid);

	}else
	{
		printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d\n",ppid, pid, pId,processStatus);
	}
}//childParentProcessing

/* Question to ask: 
* is there a way to twll which memory blocked are used for child/parent procesis. 
* how to stop a self influxed fork attack
* is there a waty to get the time formatted to US dependencuy stds or ajsut work it put?
*
*/
