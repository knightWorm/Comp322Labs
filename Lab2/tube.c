#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argv,char * args[]){
	if(argv <=1){
		printf("Invalid input!\n"); // this is done becasue the suser might not provide the command to be operated and also gets rid of the warning on my compiler for unuse vars
		exit(1);
	}
	printf("\nHello World from tube function : %s\n",args[1]);
	

	return 0;
}