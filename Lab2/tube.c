#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argv,char * args[]){
	/*Local vars*/
	int fd[2],i=0,nextInstr =0;
	int status=0,status1=0;

	/*status and status1 attributes
	* these will serve as the status for the waitpid for thw two child process.*/


	/*FD attributes
	* 0: read
	* 1: write
	* hence the buffer only needs to be of size 2.
	*/

	// this is done becasue the suser might not provide the command to be operated and also gets rid of the warning on my compiler for unuse vars
	if(argv < 2){
		printf("Invalid input!\n"); 

		exit(1);
	}

		// this is done to take care of the different command which will be separated by a comma.
	while(i < argv){
		if(strcmp(args[i],",")==0){
			args[i] = NULL;
			nextInstr = i+1;
			break;
		}
		i++;
	}

	//pipe has 1 entrance 1 exit: read, and write.
	if(pipe(fd)==-1){
		fprintf(stderr,"Pipe failed\n");
		return 1;
	}

	// let's fork! just me or if you say that fast and laud this sounds sexual... it is jsut me. 
	pid_t oneChildProcess = fork();

	// if the function fails, let's stop it now rather than waste more cpu time 
	if(oneChildProcess < 0){
		fprintf(stderr,"Fork failed: %d", oneChildProcess);
		exit(1);
	}

	// if the process is succcessful then: child process == 0.
	// parent process > 0
	// also the child is repossible for executing the next set of instructuions so, dup2() will be use for the file descriptor. refer back to fd attributes.
	// the parent will create the secodn process. 
	if(oneChildProcess == 0){
		//fprintf(stderr,"This is the first chiild\n");

		// write to the pipe
		close(fd[0]);
		dup2(fd[1],1);

		//execve(args[1],args + 1, NULL);
	}else{
		pid_t twoChildProcess  = fork();

		// check if the second process fails terminate the whole thing?
		if(twoChildProcess < 0){
			fprintf(stderr,"Second fork failed: %d",twoChildProcess);
		
		}

		if(twoChildProcess == 0){
		 	//fprintf(stderr,"This is the second child\n");

			// read from pipe
			close(fd[1]);
		 	dup2(fd[0],0);

		 	execve(args[nextInstr],args + nextInstr,NULL);

		 	exit(1);
		}else{
			fprintf(stderr,"%s: $$ = %d\n",args[1],oneChildProcess);
		 	fprintf(stderr,"%s: $$ = %d\n",args[4],twoChildProcess);
		    // parent must wait for the children to finish their processes. 
	   		// waitpid(oneChildProcess,&status,0);
	   	    waitpid(twoChildProcess,&status1,0);
	   	     // cloing the pipes access to children
	    	close(fd[1]);
	    	//close(fd[0]);
   			// print to stdderr fd[2]
	    	fprintf(stderr, "%s: $? = %d\n",args[1],status);
	 	   	fprintf(stderr, "%s: $? = %d\n",args[1],status1);

	    }
	     
	}

	return 0;
}// end fo tube function

/*





*/