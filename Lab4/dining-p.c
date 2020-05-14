#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <time.h>

// prgram's definitions
#define EAING 0 
#define THINKING 2
#define HUNGRY 1
#define FREECHOPSTICK 3


//global vars
typedef void (*sighamdler_t)(int);
sem_t * rightChop;
sem_t * leftChop;
volatile sig_atomic_t done = 0;

int raise(int sig);
int phInt;
int counter=0;

struct chopstick {
	sem_t * left;
	sem_t * right;
	char * leftName;
	char * rightName;
};
struct chopstick tmp;
struct chopstick * uten = &tmp;


void term(int sigNum);
void eat(int pat);
void think(int pat);
void waits();
void signal_handler(int sig);
// main
int main (int num, char * args[]){
	
	char * phil = args[2];
	char * seat = args[1];
	
	char * pos1;
	char * pos2;

	signal(SIGTERM, term);
	signal(FREECHOPSTICK, signal_handler);

	phInt = atoi(phil);

	int flag = O_CREAT;
	mode_t mode = 0644;

	char leftChopName[20] = "/chop";
	strcat(leftChopName,phil);

	char rightChopName[20] = "/chop";

	if(phil == "1"){
		char temp = '1';
		strcat(rightChopName, temp);

	}else{
		strcat(rightChopName, seat);
	}


	printf("Left ChopStick name: %s\n", leftChopName);
	
	printf("Right ChopStick name: %s\n", rightChopName);

	uten = (struct ChopStick*)malloc(sizeof(struct chopstick));

//left chopstick
	leftChop = sem_open(leftChopName, flag, mode, num);
	if(leftChop == SEM_FAILED){
		fprintf(stderr, "sem_open() failed .errno: %d\n",errno );
		leftChop = sem_open(phil, 0, mode, num);
	}

	uten->right = rightChop;
	uten->leftName = leftChopName;

	// right chopstick

	rightChop = sem_open(rightChopName, flag, mode, num);
	if(rightChop == SEM_FAILED){
		fprintf(stderr, "sem_open() failed .errno: %d\n",errno );
		rightChop = sem_open(phil, 0, mode, num);
	}

	sem_unlink(rightChopName);

	uten->right = rightChop;
	uten->rightName = rightChopName;

	while(!done){
		waits();
		eat(phInt);
		raise(FREECHOPSTICK);
		think(phInt);
		counter++;

	}//end of whileloop

	printf("Done\n");

	return 0;

}//end of main function

// term functon
void term(int sig){
	done = 1;

	sem_close(uten->left);
	sem_destroy(uten->left);
	sem_close(uten->right);
	sem_destroy(uten->right);

	fprintf(stderr, "Phil %d completed %d cycles\n",phInt, counter );

	free(uten);
}//end of term

// eating function
void eat(int pat){

	printf("Phil %d is eating\n", pat);
	usleep(((rand() % 11)+ 80) * 1000);

}//end of eat function

// think function
void think(int pat){
	printf("Phil %d is thinking\n", pat);
	usleep(((rand() % 11)+ 80) * 1000);
}// end of think

// signal handler
void signal_handler(int sig)
{
	sem_post(uten->left);
	sem_post(uten->right);
}//end of handler function

void waits(){
	printf("Phil %d is waiting for left chopstick: %s\n", phInt, uten->leftName);

	if(sem_trywait(uten->left) != 0){
		printf("Left chopStick not received. thinking now\n");
		raise(FREECHOPSTICK);
		think(phInt);
	}else{
		printf("Phil %d is waiting for right ChopStick %s\n", phInt, uten->rightName);
		if(sem_trywait(uten->right) !=0){
			printf("Could not wait for right chopstick. thinking now.\n");
			raise(FREECHOPSTICK);
			think(phInt);
		}
	}
}// end of wait function