#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int intSignal;
void sigHandler(int sig);
// main
int main(int num, char * argc[]){
  	struct rlimit rlim;
  	int fd, result;
  	pid_t m2;
  	pid_t m1;

  	//lets kill the program if nothoing is given to the cmd
  	// also for getting rid of the warnings for unused vars
  	result = strcmp(argc[0],"JUSTFORTESTINGB");
  	if(num < 1 || result ==0){
  		printf("Failure to initiate session\n");
  	}

  	//unmasking for new file permission
  	umask(0);

  	// findding the path to that mole
  	char buf[256];
  	char path[256];
  	getcwd(buf, 256);

  	sprintf(path, "%s/mole", buf);
  
  	printf("%s\n", path);
  
  	// forking 
  	pid_t pid = fork();
 	if(pid  < 0){
 		fprintf(stderr, "Fork Failed to create\n");
		
		exit(0);
 	}

  	// eveyr evil person is borned from tragety, so let's kill this child's parents.
  	if(pid > 0){

    	printf("The process ID: %d\n", pid);

    	exit(0);
  	}

  	// this is the child
  	if(pid == 0){

    	pid_t sid = setsid();
    	if(sid < 0){
    		printf("SID failed \n");
    	}

    	// changing the path to "/"
    	chdir("/");

    	getrlimit(RLIMIT_NOFILE, &rlim);
    	
    	int i = 0;

    	// closing all unneeded file descriptors
    	while(i < (int)rlim.rlim_cur){
      		close(i);
      		i++;
    	}

   	  	fd = open("/dev/null", O_RDWR);

    	dup(fd);
    	dup(fd);

    	signal(SIGUSR1, sigHandler);
    	signal(SIGUSR2, sigHandler);

    	srand(time(NULL));

    	while(1){
      		int chosenMole;

      		if(intSignal == 1){
        		if(m1 > 0){
          			kill(m1, SIGTERM);
        		}

        	chosenMole = rand() % 2 + 1;
        	if(chosenMole == 1 && m1 == 0){
          		m1 = fork();
          		if(m1 == 0){
            		char *args[2] = {"M1", NULL};
            		execve(path, args, NULL);
          		}
        	}else if (chosenMole == 2 && m2 == 0){
          		m2 = fork();
          		if(m2 == 0){
            		char *args[2] = {"M2", NULL};
            		execve(path, args, NULL);
          		}
        	}

        	intSignal = 0;
      		}else if(intSignal == 2){
        		if(m2 > 0){
          			kill(m2, SIGTERM);
        		}

        		chosenMole = rand() % 2 + 1;
        		if(chosenMole == 1 && m1 == 0){
          			m1 = fork();
          			if(m1 == 0){
            			char *args[2] = {"m1", NULL};
            			execve(path, args, NULL);
          			}
        		}else if (chosenMole == 2 && m2 == 0){
          			m2 = fork();
          			if(m2 == 0){
            			char *args[2] = {"m2", NULL};
            			execve(path, args, NULL);
          			}
        		}

        	intSignal = 0;
      		}
    	}// endof second whileloop

    	kill(m1, SIGTERM);
    	kill(m2, SIGTERM);
    	exit(0);// to kill the deamon

  	}
	} // end of main

// handler function
// adds value to my global var for signals recieved.
void sigHandler(int sig){
	if(sig == SIGUSR1){
    	intSignal = 1;
	}else if(sig == SIGUSR2){
    	intSignal = 2;
	}
  	signal(sig, sigHandler);
}// end of sigHandler