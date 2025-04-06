#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "functions.h"

int main(int argc, char *argv[])
{	
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
	
	srand(time(NULL)); // Set seed for random number generator
	
	//char *secretWord = chooseRandomWord();
	char *secretWord = chooseFromFile();
	char *userWord = initializeUserWord(secretWord);
	
	// Main screen instructions 
	printf("\nWelcome to Hangman!\n\n");
	printf("Guess the following word: %s\n\n", userWord);
	
	readWord(secretWord, userWord);
	
	// Freeing dynamically allocated memory
	free(userWord);
	free(secretWord);
	
	return 0;
}
