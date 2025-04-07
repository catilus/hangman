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
	
	// Initialization of variables; memory allocation
	char buffer[30] = {0};
	int streak = 0;
		
	// Main screen instructions 
	printf("***********************\n");
	printf("  Welcome to Hangman!\n");	
	printf("***********************\n\n");
	
	// Handles username input
	printf("Choose a username: ");

	fgets(buffer, sizeof(buffer), stdin); // Read user input into buffer
	buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character (if present) with null terminator
	
	char *userName = malloc(strlen(buffer) + 1);	// Allocate memory to user name the size of the input
	if (userName == NULL)	// Check that memory allocation was successful
	{
		exit(1);
	}
	strcpy(userName, buffer);	// Copy string from buffer into userName
	printf("\nWelcome %s!!!\n", userName);

	// Sets difficulty level based on user input
	Difficulty numberOfAttempts = setDifficulty();
	printf("\n________________\n\n");
	printf("Guess the following word in %d attempts: %s\n\n", numberOfAttempts , userWord);

	// Word handling
	if (readWord(secretWord, userWord, numberOfAttempts) == 1) // If user wins, increment streak by 1
	{
		streak++;
	}
	else // If user looses, reset streak to 0
	{
		streak = 0;
	}
	
	// File contains high scores
	streak = highScores(streak, userName);
	
	printf("%s, your streak is now: %d\n", userName, streak);
	
	// Freeing dynamically allocated memory
	free(userWord);
	free(secretWord);
	free(userName);
	
	return 0;
}
