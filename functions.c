#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

char getCharacter() //Ask and retrieve character user input
{
	printf("Enter a letter: ");
		
	char character = 0;
	character = getchar(); //gets the first character entered
	character = toupper(character); //uppercase character
	while (getchar() != '\n'); //prevents multiple characters from being stored in character at once

	return character;
}

void readWord(char secretWord[], char userWord[])
{
	char character = 0;
	int counter = 0;
	
	while (strcmp(secretWord, userWord) != 0 && counter < 11)
	{		
		character = getCharacter();
		char *ptr = strchr(secretWord, character);
		counter++;
		
		if (ptr != NULL)
		{		
			int index = ptr - secretWord;
			userWord[index] = character;
			printf("%s\n", userWord);
		}
		else
		{
			printf("%s\n", userWord);
		}
	}
	
	if (counter < 11)
	{
		printf("\nYou solved the mystery word in %d tries.\n", counter);
	}
	else 
	{
		printf("\nGame over!!!\n");
	}
}
