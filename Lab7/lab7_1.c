#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//main
int main(int argc, char * argv[]){

	int n = 0;
	FILE * fw = fopen("matrix.txt","w");

	// n  = atoi(argv[1]);
	// testing
	printf("Enter Size of Array\n");
	scanf("%d",&n);

	// alocating a2d array of size n
	// i = rpws
	// j == columns
	int matrix[n][n];

	srand(time(0));

	// for printing on to file. 
	// count and count2 are for better formatting. 
	int count=0,count2=0;

	//let's populate this bitch 
	for(int i = 0; i < n; i++){
		for(int j=0; j < n; j++){

			matrix[i][j] = rand()%100;


			if(count == n){
				fprintf(fw,"\n");
				count=0;
			}

			fprintf(fw," %d ",matrix[i][j]);
		

			if(count2 == n*n -1){
				
				fprintf(fw,"\n");
			}
			count++;

			count2++;

		}//end of j loop
	}// enf of i loop

	// for printing on to file. 
	// count and count2 are for better formatting. 
//	int count=0,count2=0;
// // print th e elementd onto  a file. 
// 	for(int i = 0; i < n; i++){
// 		for(int j=0; j < n; j++){

// 			if(count == n){
// 				fprintf(fw,"\n");
// 				count=0;
// 			}

// 			fprintf(fw," %d ",matrix[i][j]);
		

// 			if(count2 == n*n -1){
				
// 				fprintf(fw,"\n");
// 			}
// 			count++;

// 			count2++;

// 		}//end of j loop
// 	}// enf of i loop	



}//end of main