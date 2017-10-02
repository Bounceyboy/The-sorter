#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"sorter.h"
#include <time.h>
#include"mergesort.c"

int main(int argc, char *argv[]){

	//TODO: error handling for wrong file input

	FILE *input;
	input = stdin;				//the File "input" is now the csv
//	input = fopen("movie_metadata.csv", "r"); 		//for debugging

	Line **Lines = malloc(sizeof(Line));
	char buf[1024];
	
	int ArraySize = 1;

	//one extra fgets call to skip header line of csv
	fgets(buf,1024,input);

	//one manual fgets call to store in first line so that there isn't an extra
	//empty Line in the array "Lines"
	fgets(buf,1024,input);
	Lines[0] = importLine(buf);
	

	//in this loop:
	//increment ArraySize (might remove, just figured it'd be good to have just in case)
	//Reallocate memory to allow for an additional Line in "Lines"
	//Call importLine to create that line and add it to "Lines"
	
	while(fgets(buf,1024,input)!=NULL){	//for each line (gets stored in string "buf")
		ArraySize++;
		Lines = realloc(Lines, sizeof(Lines) + sizeof(Line));
		Lines[ArraySize-1] = importLine(buf);
	}

	printf("%d\n", ArraySize);



/*TODO mergesort function with following properties
 *Takes a "Lines" input (pointer to array of "Line" structs), and a string (character array) containing
 *the title of the column to sort by
 *
 *a prototype of the function would look like this:
 *	Line* Mergesort(Line* inputArray, char* column);
 *
 *This will be in a separate file called Mergesort.c
 *Let me know if you need help!
 */

	return 0;
}
