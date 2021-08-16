#include <stdio.h>
#include <stdlib.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[1]) //main function grabs command line arguments to be used for printing the number of words in a given text file
{
	//initializing variables
	char *filename;
	char buffer[MAX_WORD_LENGTH];
	int wordCount = 0;

	filename = argv[1]; //declare filename as the second command line argument

	FILE *fp; //create file pointer

	fp = fopen(filename, "r"); //open the file for reading
	while(fscanf(fp, "%s", buffer)==1) //continue scanning the file for words at the given maximum length of 30
	{
		wordCount++; //increase the word count by one
	}	
	
	printf("%d total words\n", wordCount); //print the word count

	fclose(fp); //close file pointer
}
