#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#define ALPHABET_LEN 26
#define MAX_TRIES 10

// Function picks a random word from a file that contains names
char *chooseFromFile()
{
	// Open text file and count lines
	FILE *fptr = fopen("animals.txt", "r");
	
	if(fptr == NULL)
	{
		printf("File did not open\n");
		exit(1);
	}
	
	char buffer[100];
	int wordCounter = 0;
	
	while(fgets(buffer, sizeof(buffer), fptr))
	{
		wordCounter++;
	}
	
	if(wordCounter == 0)
	{
		fclose(fptr);
		return NULL;
	}
	
	// Generate a random line number
	int randomLine = rand() % wordCounter + 1;
	
	// Scroll through file until we reach the line we picked	
	rewind(fptr);
	int currentLine = 1;
	
	//char chosenWord = malloc(
	
	while(fgets(buffer, sizeof(buffer), fptr))
	{
		if (currentLine == randomLine)
		{
			break;
		}
		else
		{
			currentLine++;
		}
	}
	char *chosenWord = malloc(strlen(buffer) + 1);
	if (chosenWord == NULL)
	{
		exit(1);
	}
	
	int i = 0;
	while (buffer[i] != '\n')
	{
		chosenWord[i] = buffer[i];
		i++;
	}
	chosenWord[i] = '\0';
	
	fclose(fptr);
	
	return chosenWord;
}

// Function initializes userWord based on secretWord (ran only once)
char *initializeUserWord(char secretWord[])
{
	// Calculate length of secret word
	size_t length = strlen(secretWord);
		
	// Allocates memory for a string of the same length as secretWord
	char *userWord = malloc(length + 1);
	if (userWord == NULL)
	{
		exit(1);
	}
		
	// Fills string with *
	for (int i=0; i < length; i++)
	{
		userWord[i] = '*';
	}
	userWord[length] = '\0'; //Last character is the null-terminator
		
	return userWord;
}

// Function retrieves letter input from user
char getCharacter()
{
	char character = 0;
	
	while (1) {	
		printf("Choose a letter [a-z;A-Z]: ");
		character = getchar();
	
		while (getchar() != '\n') ;
	
		if (isalpha(character))
		{
			
			return toupper(character);
		}
		
		printf("Please enter an actual letter...\n");
	}
}

// Function checks if input letter is in secretWord
void readWord(char secretWord[], char userWord[])
{	
	// Calculate length of secret word
	size_t length = strlen(secretWord);
	
	// Initialize counter of user tries
	int counter = 0;
	
	// Initialize array of letters already tried
	char lettersTried[ALPHABET_LEN] = {0};
	int letterCounter = 0;
		
	// Keep prompting for characters until secretWord is found
	while (strcmp(secretWord, userWord) != 0 && counter < MAX_TRIES)
	{
		// Get a letter from user
		char character = getCharacter();
		
		// See if letter has already been tried
		if(strchr(lettersTried, character) == NULL) // if letter hasn't been tried, strchr will not return a pointer --> append letter to letterTried[] and keep going
		{
			lettersTried[letterCounter] = character;
			letterCounter++;
			
			int letterFound = 0;
		 
			// Iterates over characters in word
			for (int i=0; i < length; i++)
			{
				// Check if character is identical to current letter in secretWord
				if (character == secretWord[i])
				{
					userWord[i] = character;
					letterFound = 1;
				}
				else
				{
					continue;
				}
			}
		
			if (letterFound != 0)
			{
				printf("Guess the word: %s\n\n", userWord);
			}
			else
			{
				counter++;
				printf("\n%c is not in the secret word. \nYou have %d tries left.\n", character, (10 - counter));
				printf("________________\n\n");
				printf("%s\n\n", userWord);
			}	
		}
		else   // if letter has been tried, print a message and continue
		{
			printf("Letter %c has already been tried.\n\n", character);		
		}										
	}

	if (strcmp(secretWord, userWord) == 0)
	{
		printf("\nYOU WON!!!\n\n");
	}
	else
	{
		printf("The secret word was: %s\n\n\n", secretWord);
	}
}
