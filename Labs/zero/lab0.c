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
char data[8];

void FileWork(char * fname);
void display_chart();
int binaryToInt(char * incoming);
int OE(char * incoming);
char DecToAscii(int num);
void display(char *incoming);
int isFile(char* fname);
int validInput(int num,char* e[]);
int main(int num, char* args[]){
int isValid; //valid input: 1,2,3,4 invalid: 0, file: 3(thi is also valid)
isValid = validInput(num,args);
int i =0; // for he for loop
if(isValid == 1){
	i=1;
	display_chart();
	for(i; i < num; i++){
		display(args[i]);
	}
	}else if(isValid ==2){
	i=2;
	display_chart();
	for(i; i < num; i++){
		display(args[i]);
	}	
	}else if(isValid == 3){
		display_chart();
		FileWork(args[2]);
	}else if(isValid == 4){
		printf("************* 4 ********\n");
		display_chart();
		FileWork(args[1]);
	}else{
		printf("\nInvalid Input\n");
	}
}//end of class
void FileWork(char * fname){
	size_t nbytes;
	ssize_t bytes_read;
	char cArr[8];
	int index = 0;
	int fd = open(fname, O_RDONLY, 0666);
	if(fd == -1){
	perror("File Error\n");
	exit(1);
		}
		bytes_read = read(fd,data,8);
	while(bytes_read != 0){
		int count = 0;
		if(bytes_read != 8){
			int i=0,j=0;
			// fill the cArr with 0's to the right
			for(i;i < 8;i++){
				if(i <(8-bytes_read)){
					cArr[i] ='0';
					count++;
				}else{
				cArr[i] = data[i - count];	
				}
			}
			display(cArr);
		}else{
			display(data);
		}
		// skip the space
		bytes_read=read(fd,data,1);
		//read the next 8
		bytes_read=read(fd,data,8);
}
} // enf of class
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
void display(char* incoming){
	int decimal;
	int odd_even;// 0 == even, 1 == odd
	char ascii;
	int binary;

	for(int i =0;i<sizeof(data);i++){
		printf("%c",incoming[i]);
	}
	//printf(" ");
	decimal = binaryToInt(incoming);
	ascii = DecToAscii(decimal);
	odd_even = OE(incoming);
	printf("\t%c\t%d\t",ascii,decimal);
	switch(odd_even){
		case 1: printf("ODD\n");break;
		case 0: printf("Even\n"); break;
		default:break;
	}
}//end of class
int binaryToInt(char * incoming){
	double sqr;
	int sum = 0, in = 0;
	for(int i =7; i > 0; i--){
		 if((int)incoming[i]== 49){
		 	in= 7 - i;
		 	sum = sum + pow(2,in);
		 }
	 }
	return sum;
}//end of class
char DecToAscii(int num){
	return (char)num;
}//end of class
int OE(char * incoming){
int count =0,product;
for(int i = 0; i < sizeof(data);i++){
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
}// end of class
void display_chart(){
	printf("Original\tASCII\tDecimal\tParity\n");
	printf("--------\t------\t------\t------\n");
}//end of class