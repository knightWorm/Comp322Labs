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

int OE(char * incoming);
char DecToAscii(int num);
int binaryToInt(char * incoming);
void display(char * incoming);
void FileWork(char * fname);
int isFile(char * fname);
int main(){
	/* Local vars*/
	int input_result;// will act as checkpoints for my program; key: 1 is file, 0 is data. 2 continue checking
	printf("Enter Data or File name: ");
	scanf("%[^\n]s",file_name); // this allows to read spaces
	printf("Original\tASCII\tDecimal\tParity\n");
	printf("--------\t------\t------\t------\n");
    input_result = isFile(file_name);
    if(input_result == 1){
		FileWork(file_name);
    }else{
    	// it must be data from terminal treat it as such.
    	//testing
		printf("not a file"); 
    }
	return 0;
} // end of main class
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
	char cArr[8];
	int index = 0;
	int fd = open(fname, O_RDONLY, 0666);
	if(fd == -1){
	perror("File Error\n");
	exit(1);
		}
		bytes_read = read(fd,data,8);
	while(bytes_read != 0){
		if(bytes_read != 8){
			int i=0,j=0;
			// fill the cAee with 0's to the right
			for(i;i < (8-bytes_read);i++){
				cArr[i]='0';
				j++;
			}
			for(j;j<bytes_read;j++){
				cArr[j] = data[j-i];
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
void display(char *incoming){
	int decimal;
	int odd_even;// 0 == even, 1 == odd
	char ascii;
	int binary;

	for(int i =0;i<sizeof(data);i++){
		printf("%c",incoming[i]);
	}
	printf(" ");
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
//fuck