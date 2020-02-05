#include <stdio.h>
#include <stdlib.h>

int main(){
	char file_name[20]; //allows up to 20 characters.
	char buffer[8]; // this is to stor the chars 
	int permutations=0;
printf("File: ");
scanf("%s", file_name);
FILE *file_in = fopen(file_name,"r");
if (file_in == NULL) {
	printf("Error: empty file!\n");
	exit(-1);
}else {
	printf("status: File opened successsfully!\n");
	while(fgets(buffer,9,file_in)!=NULL){
		printf("Data: %s \n",buffer);
	}
	fclose(file_in);
 }

return 0;
}
	//int count = getc(file_in);
 	//    char c;
	// printf("count:  %d\n",count);
	// while ((count = getc(file_in))!=EOF) {
	// 	//c = fgetc(file_in);
	// 	// permutations++;
	// 	// printf("%c",count);
	// 	//fgets(buffer,8,file_in);
	// 	scanf("%s",buffer);
	// 	printf("Data available: %c\n", buffer);

	// }
	//printf("\nCount: %d", c);