#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

char getCharacter() //Ask and retrieve character user input
{
	printf("Enter a letter: ");
		
	char character = 0;
	character = getchar();	//gets the first character entered
	character = toupper(character);	//uppercase character
	
	while (getchar() != '\n') {};	//consumes leftover characters in the input buffer

	return character;
}

void readWord(char secretWord[], char userWord[])
{
	char character = 0;
	int counter = 1;
	
	// Compares mystery word to input word and keeps looping around until either secret word is found or counter reaches 10 tries
	while (strcmp(secretWord, userWord) != 0 && counter < 11)
	{		
		character = getCharacter(); // Gets a letter from user
		char *ptr = secretWord;	// Finds first occurence of letter in secret word
		
		while ((ptr = strchr(ptr, character)) != NULL)	// If inputted letter is in secret word
		{		
			int index = ptr - secretWord; // Calculate array index of letter in secret word
			userWord[index] = character;	// Reveal letter in user word at calculated index
			ptr++; // Move to next character to avoid infinite loop
		}
		
		printf("%s\n", userWord);	// Show updated word
		
		counter++;	// Increments counter of tries
	}
	
	// Once either secret word is found or number of tries = 10, print associated message
	if (counter < 10)
	{
		printf("\nYou found the mystery word in %d tries.\n", counter);
	}
	else 
	{
		printf("\nGame over!!!\n");
	}
}
