#include <stdio.h>
#include <stdlib.h>

// main
int main(int argv, char * args[]){
	// this is jsut to get rid of the vars unused not used
	if(argv< 0){
		printf("Failed to initiated session %d\n", argv);
	}
	FILE * log;
	log = fopen("lab6.log","a+");

	fprintf(log,"Pop %s\n",args[0]);
}//end of main