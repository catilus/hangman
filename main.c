#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
//#define MAX_LENGTH 1000

int main(int argc, char *argv[])
{
	srand(time(NULL)); // Set seed for random number generator
	
	//char secretWord[] = "HELENE";
	char *secretWord = randomWord();
	if (secretWord == NULL)
	{
		exit(1);
	}
	
	// Allocate space for userWord and fill with asterisks
	size_t size = strlen(secretWord);
	char *userWord = (char *)malloc(size + 1);
	
	if (userWord == NULL)
	{
		free(secretWord);
		exit(1);
	}
	
	for (size_t i=0; i < size; i++)
	{
		userWord[i] = '*';	
	}
	userWord[size] = '\0'; //Null-terminate
	
	// Main screen instructions 
	printf("\nWelcome to Hangman!\n\n");
	readWord(secretWord, userWord);
	
	// Freeing dynamically allocated memory
	free(userWord);
	free(secretWord);
	userWord = NULL;
	secretWord = NULL;
	
	return 0;
}
