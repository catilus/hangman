#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

// Function picks a random word in an array of words and returns it (or a pointer to the word itself)
char *chooseRandomWord()
{
	char *listOfWords[] = {"ARACHNEA", "BEAR", "COYOTE", "DOLPHIN", "ELEPHANT", "FOX",
						"GIRAFFE", "HIPPOPOTAMUS", "IBIS", "JAGUARANDI", "KOALA", "LION", "MOOSE",
						"NAUTILUS", "OSTRICH", "PENGUIN", "QUAIL", "ROOSTER", "SNAKE", "TAMARIND",
						"URCHIN" "VOLLE", "WAPITI", "XENOPS", "YAK", "ZEBRA"};
	
	size_t length = sizeof(listOfWords) / sizeof(listOfWords[0]) + 1;				
	int randomNumber = rand() % length + 1;
	
	return listOfWords[randomNumber];
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
	printf("Choose a letter [a-z;A-Z]: ");
	character = getchar();
	
	while (getchar() != '\n') ;
	
	if (!isalpha(character))
	{
		printf("Please enter an actual letter...\n");
		return getCharacter();
	}
	
	return toupper(character);
}


// Function checks if input letter is in secretWord
void readWord(char secretWord[], char userWord[])
{	
	// Calculate length of secret word
	size_t length = strlen(secretWord);
	
	// Initialize counter of user tries
	int counter = 0;
		
	// Keep prompting for characters until secretWord is found
	while (strcmp(secretWord, userWord) != 0 && counter < 10)
	{
		char character = getCharacter();
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
			printf("%s\n\n", userWord);
		}
		else
		{
			counter++;
			printf("\n%c is not in the secret word. \nYou have %d tries left.\n", character, (10 - counter));
			printf("________________\n\n");
			printf("%s\n\n", userWord);
		}	
	}

	if (strcmp(secretWord, userWord) == 0)
	{
		printf("\nYOU WON!!!\n\n");
	}
	else
	{
		printf("The secret word was: %s\n", secretWord);
	}
}
