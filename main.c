#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
//#define MAX_LENGTH 1000

int main(int argc, char *argv[])
{
	char secretWord[] = "OLIVE";
	size_t size = sizeof(secretWord) / sizeof(secretWord[0]);
	char *userWord = malloc(size);
	
	
	for (int i=0; i < (size-1); i++)
	{
		userWord[i] = '*';	
	}
	
	printf("\nWelcome to Hangman!\n\n");
	
	readWord(secretWord, userWord);
	
	free(userWord);
	
	return 0;
}
