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
	time_t start, stop; 
	int status; 

	//struct tms buf, data typr: struct tms. 
	// this has the following functions:
	// tms_utime
	//tms_stime
	//tms_cutime
	// tms_cstime
	struct tms buf;

	clock_t sinceStart;

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

		childParentProcessing(0,0);

	}else{
		//printf("I am parent!\n");

		waitpid(currentProcessID,&status, 0);

		childParentProcessing(status,currentProcessID);

		sinceStart = times(&buf);
		printf("USER: %ld, SYS: %ld\nCUSER: %ld, CSYS: %ld\n",buf.tms_utime,buf.tms_stime,buf.tms_cutime, buf.tms_cstime);

		//the times needs to be delayed because this sould be the last program to run.
		sleep(2);// to delay the time difference 10 seconds

		printf("STOP:  %ld\n",time(NULL));
	}

	return 0;
}//main

// Function manages the different process and displays their results.
void childParentProcessing(int processStatus, pid_t pId)
{
	pid_t pid = getpid();
	pid_t ppid = getppid();

	if(processStatus == 0 && pId == 0)
	{
		printf("PPID: %d, PID: %d\n",ppid, pid);

	}else
	{
		printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d\n",ppid, pid, pId,processStatus);
	}
}//childParentProcessing
