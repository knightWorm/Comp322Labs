#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

FILE * in_file;
char file_data[25];

int isFile(char* fname);
int validInput(int num,char* e[]);
int main(int num, char* args[]){
int isValid; //valid input: 1, invalid: 0
isValid = validInput(num,args);
if(isValid == 1){
}else{
printf("\nInvalid Input\n");
}
}//end of class

int validInput(int num, char* e[]){
	if(num == 2 && isFile(e[1])==1){
		return 1;
	}else if(num == 3 && (strcmp(e[1],"-")==0) && isFile(e[2])==1){
		return 1;
	}else if(num > 3 && strcmp(e[1],"-")==0){
		return 1;
	}else{
		return 0;
	}
}//end of class
int isFile(char* fname){
	 in_file = fopen(fname,"r");
	if(in_file == NULL){
		return 0;
	}else{
		fclose(in_file); // becasue i wont be working with the file here.
		return 1;	
	}
} // end of class