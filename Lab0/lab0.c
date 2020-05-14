#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

void fileWork(char * fname);
void displayChart();
int binaryToInt(char * incoming);
int OE(int size, char * incoming);
char DecToAscii(int num);
int isFile(char* fname);
int validInput(int num,char* e[]);
void display(int size, char *incoming);


int main(int num, char* args[])
{
	int decimal;
	int odd_even;// 0 == even, 1 == odd
	char ascii;
	int binary;
	
	// validInput checks type of input and returns what starting index of binary values 
	int start = validInput(num,args);
	
	if (start == 0 || num == 1) {
		printf("\nInvalid Input. Must pass in binary split by spaces or a file containing binary.\n");
		exit(1);
	}

	// print columns
	displayChart();

	// if isValid is 1 or 2 then that means input not a file
	if(start == 1 || start == 2){

		for(int i = start; i < num; i++){
			// convert binary to int, Ascii and checks if odd or even
			// TODO: check if you need to pad 0's to binary
			decimal = binaryToInt(args[i]);
			ascii = DecToAscii(decimal);
			odd_even = OE(8, args[i]);	 
			
			printf("%s",args[i]);
			printf("\t%c\t%d\t",ascii,decimal);
			switch(odd_even){
				case 1: 
					printf("ODD\n");
					break;
				case 0: 
					printf("Even\n"); 
					break;
				default:
					break;
			}
		}
	}

	if(start == 3){
		// process file and check 
		fileWork(args[2]);
	}

	if(start == 4){
		fileWork(args[1]);
	}

	return 0;
}//main

void fileWork(char * fname){
	int fd = open(fname, O_RDONLY, 0666);
	if(fd == -1){
		perror("File Error\n");
		exit(1);
	}
	
	// read 8 bytes from fd into data
	char data[8];
	char cArr[8];
	ssize_t bytes_read;

	bytes_read = read(fd,data,8);	
	while(bytes_read != 0){
		int count = 0;
		if(bytes_read != 8){
			for(int i=0; i < 8; i++){
				// fill the cArr with 0's to the right
				if(i <(8-bytes_read)){
					cArr[i] ='0';
					count++;
				}else{
					cArr[i] = data[i - count];	
				}
			}
			display(bytes_read, cArr);
		}else{
			display(bytes_read, data);
		}

		// skip the space
		bytes_read=read(fd,data,1);
		//read the next 8
		bytes_read=read(fd,data,8);
	}
}//end of Fucntion

int validInput(int num, char* e[]){
	if(num == 2 && isFile(e[1])==1){
		return 4;
	}else if(num == 3 && (strcmp(e[1],"-")==0) && isFile(e[2])==1){
		return 3;
	}else if(num > 3 && strcmp(e[1],"-")==0){
		return 2;
	}else if(num > 3){
		return 1;
	}else{
		return 0;
	}
}//end of Fucntion

void display(int size, char* incoming){
	int decimal;
	int odd_even;// 0 == even, 1 == odd
	char ascii;
	int binary;

	for(int i =0;i< size;i++){
		printf("%c",incoming[i]);
	}
	//printf(" ");
	decimal = binaryToInt(incoming);
	ascii = DecToAscii(decimal);
	odd_even = OE(8, incoming);
	printf("\t%c\t%d\t",ascii,decimal);
	switch(odd_even){
		case 1: printf("ODD\n");break;
		case 0: printf("Even\n"); break;
		default:break;
	}
}//end of class

int isFile(char* fname){
	FILE * in_file = fopen(fname,"r");
	if(in_file == NULL){
		return 0;
	}else{
		fclose(in_file); // becasue i wont be working with the file here.
		return 1;	
	}
} //end of Fucntion

int binaryToInt(char * incoming){
	double sqr;
	int sum = 0, in = 0;
	for(int i =7; i > 0; i--){
		 if((int)incoming[i]== 49){
		 	in= 7 - i;
		 	sum = sum + pow(2.0,in);
		 }
		 
	}
	return sum;
}//end of Fucntion

char DecToAscii(int num){
	return (char)num;
}//end of Fucntion

int OE(int size, char * incoming){
	int count =0,product;
	for(int i = 0; i < size;i++){
		if((int)incoming[i]==49){
			count++;
		}
	}

	product = count%2;
	if(product == 0){
		return 0; //even
	}else{
		return 1;//odd
	}
}//end of Fucntion

void displayChart(){
	printf("Original\tASCII\tDecimal\tParity\n");
	printf("--------\t------\t------\t------\n");
}//end of Fucntion