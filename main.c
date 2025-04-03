#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
//#define MAX_LENGTH 1000

int main(int argc, char *argv[])
{
	char secretWord[] = "HELENE";
	
	// Initialize displayed word based on size of secret word
	size_t size = sizeof(secretWord) / sizeof(secretWord[0]);
	char *userWord = (char *)malloc(size);
	if (userWord == NULL)
	{
		exit(0);
	}
	
	for (int i=0; i < (size-1); i++)
	{
		userWord[i] = '*';	
	}
	
	// Main screen instructions 
	printf("\nWelcome to Hangman!\n\n");
	
	readWord(secretWord, userWord);
	
	// Freeing dynamically allocated memory
	free(userWord);
	userWord = NULL;
	
	return 0;
}
