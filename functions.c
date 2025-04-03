#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

char *randomWord()
{
	char *arrayOfWords[] = {"OLIVE", "PINEAPPLE", "CHOCOLATE", "BIRDS", "WOODWORKING", 
		"CLOVER", "CRICKET", "CLOCLO", "OLLIE", "PACHO", "KOKO"}; // Array of secret words
	size_t sizeOfArray = sizeof(arrayOfWords) / sizeof(arrayOfWords[0]);	// Size of array of words
	
	int randomNumber = rand() % sizeOfArray; // Generate random index
	size_t randomWordSize = strlen(arrayOfWords[randomNumber]); 
	
	// Allocate memory for the chosen word
	char *randomWord = (char *)malloc((randomWordSize + 1) * sizeof(char)); 
	if (!randomWord)
	{
		exit(1);
	}
	
	strcpy(randomWord, arrayOfWords[randomNumber]);
	return randomWord;
}

char getCharacter() //Ask and retrieve character user input
{
	printf("Enter a letter: ");
		
	char character = getchar();	//gets the first character entered
	character = toupper(character);	//uppercase character
	
	while (getchar() != '\n');	//consumes leftover characters in the input buffer

	return character;
}

void readWord(char secretWord[], char userWord[])
{
	char character = 0;
	int counter = 1;
	
	printf("Find the following word: %s\n\n", userWord);
	
	// Compares mystery word to input word and keeps looping around until either secret word is found or counter reaches 10 tries
	while (strcmp(secretWord, userWord) != 0 && counter < 11)
	{		
		character = getCharacter(); // Gets a letter from user
		printf("You entered: %c\n", character);
		
        int letterFound = 0;
        for (size_t i = 0; i < strlen(secretWord); i++) {
            if (secretWord[i] == character) {
                userWord[i] = character;   // Reveal letter
                letterFound = 1;
            }
        }
		//char *ptr = secretWord;	// Pointer to secret word
		
		//while ((ptr = strchr(ptr, character)) != NULL)	// Finds first occurence of letter in secret word
		//{		
			//int index = ptr - secretWord; // Calculate array index of letter in secret word
			//userWord[index] = character;	// Reveal letter in user word at calculated index
			//ptr++; // Move to next character to avoid infinite loop
		//}
		
		printf("%s\n", userWord);	// Show updated word
		if (letterFound == 0)
		{
			printf("\nAttempts remaining: %d\n", 10 - counter);
		}
		
		counter++;	// Increments counter of tries
	}
	
	// Once either secret word is found or number of tries = 10, print associated message
	if (strcmp(secretWord, userWord) == 0)
	{
		printf("\nYou found the mystery word in %d tries.\n", counter);
	}
	else 
	{
		printf("\nGame over!!! The word was: %s.\n", secretWord);
	}
}
