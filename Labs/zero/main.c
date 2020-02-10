#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

/* Global vars*/
FILE * in_file;
char data[8];
char NSInput[256];
char file_name[256];// assuming the file name will not be longer than 25 characters.

int binaryToInt(char * incoming);
void display(char * incoming);
void FileWork(char * fname);
int isFile(char * fname);
int main(){
	/* Local vars*/
	int input_result;// will act as checkpoints for my program; key: 1 is file, 0 is data. 2 continue checking


	printf("Enter Data or File name: ");
	scanf("%[^\n]s",file_name); // this allows to read spaces
	printf("Original\tASCII\t\tDecimal\t\tParity \n");
	printf("--------\t--------\t--------\t--------\n");
    input_result = isFile(file_name);
    if(input_result == 1){
   
    		//testing
		printf("This is a file\n");
		FileWork(file_name);
    }else{
    	// it must be data from terminal treat it as such.
    	//testing
		printf("not a file"); 

    }

	return 0;
}

// this class will check is the input is a file name.
int isFile(char * fname){
	in_file = fopen(fname,"r");
	if(in_file == NULL){
		return 0;
	}else{
		fclose(in_file); // becasue i wont be working with the file here.
		return 1;
		
	}
	
} // end of class

void FileWork(char * fname){
	size_t nbytes;
	ssize_t bytes_read;
	char actual_data[8];
	int index = 0;
	int fd = open(fname, O_RDONLY, 0666);
	if(fd == -1){
	perror("File Error\n");
	exit(1);
		}
		bytes_read = read(fd,actual_data,8);
	while(bytes_read != 0){
		char local_data[bytes_read];
		for(int i = 0; i < sizeof(local_data);i++){
			if(isspace(actual_data[i]) == 0){
				if(index == 7){
					display(actual_data);
					index = 0;
					
				}else{
				local_data[i] = actual_data[i];
				index++;
					  }
			}else{
				printf("\nThis is a space\n");
			  // bytes_read = read(fd,data,1);
				}

				}
		bytes_read = read(fd,actual_data,8);	
}
	//testing
	for(int j = 0; j < sizeof(actual_data); j++){
		printf("%c",actual_data[j]);
		
	}
} // enf of class
void display(char *incoming){
	char og_data[8];
	int decimal;
	int odd_even=0;// 0 == false, 1 == even
	char ascii;
	int binary;

	for(int i =0;i<8;i++){
		og_data[i] =incoming[i];
		//printf("%c",og_data[i]);
	}
	binary = binaryToInt(og_data);
	printf("\nBinary value: %d\n",binary);
}//end of class

int binaryToInt(char * incoming){
	double sqr;
	int sum = 0, in = 0;
	for(int i =7; i > 0; i--){
		// printf("%c\n",incoming[i]);
		 if((int)incoming[i]== 49){
		 	in= 7 - i;
		 	sum = sum + pow(2,in);
		 }
	 }
	return sum;
}//end of class