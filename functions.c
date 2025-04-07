#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#define ALPHABET_LEN 26

void screenClear()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

// Function sets game difficulty base on user input
Difficulty setDifficulty()
{
	int difficultyChoice = 0;
	
	printf("\n"); // Inserts newline before menu selection is displayed
		
	while(1) {
		printf("Select a difficulty level:\n");
		printf("	[1] Easy -- 20 attempts\n");
		printf("	[2] Medium -- 15 attempts\n");
		printf("	[3] Hard -- 10 attempts\n");
		printf("Difficulty level [enter 1, 2 or 3]: ");
		
		if (scanf("%d", &difficultyChoice) == 1) //Checks if the user inputted a number and acts accordingly
		{
			switch (difficultyChoice)
			{
				case 1: return EASY;
				case 2: return MEDIUM;
				case 3: return HARD;
				default:
					printf("\nInvalid choice\n");
			}
		}
		else
		{
			while (getchar() != '\n');  // Clear input buffer
			printf("\nPlease enter a number...\n");
		}
	}
}

// Function picks a random word from a file that contains names
char *chooseFromFile()
{
	int fileChoice = 0;
	char fileChosen[100] = {0};
	
	// Menu to choose from multiple file lists
	while (1)
	{
		printf("Please choose amongst the following lists of names:\n");
		printf("	[1] Animals\n");
		printf("	[2] Plants\n");
		printf("File number [enter 1 or 2]: ");
		if (scanf("%d", &fileChoice) == 1) 
		{
			switch (fileChoice)
			{
				case 1: 
					strcpy(fileChosen, "Lists//animals.txt");
					break;
				case 2: 
					strcpy(fileChosen, "Lists//plants.txt");
					break;
				default: 
					printf("\nInvalid choice\n");
					continue;
			}
			break;
		}
		else
		{
			while (getchar() != '\n');  // Clear input buffer
			printf("Please enter a number\n");
		}
	}
	
	// Open text file and count lines
	FILE *fptr = fopen(fileChosen, "r");
	
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
	while (getchar() != '\n'); // Clear any leftovers in previous input buffers
	
	while (1) {	
		printf("Choose a letter [a-z;A-Z]: ");
		character = getchar();
		printf("\n");
	
		if (isalpha(character))
		{
			return toupper(character);
		}
		else
		{
			printf("\nPlease enter an actual letter...\n");
			while (getchar() != '\n') ;
		}
		
	}
}

// Function checks if input letter is in secretWord
int readWord(char secretWord[], char userWord[], Difficulty numberOfAttempts)
{		
	// Calculate length of secret word
	size_t length = strlen(secretWord);
	
	// Initialize counter of user attempts
	int counter = 0;
	
	// Initialize array of letters already tried
	char lettersTried[ALPHABET_LEN] = {0};
	int letterCounter = 0;
		
	// Keep prompting for characters until secretWord is found
	while (strcmp(secretWord, userWord) != 0 && counter < numberOfAttempts)
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
				printf("--> Guess the word: %s\n\n", userWord);
			}
			else
			{
				counter++;
				printf("\n%c is not in the secret word. \nYou have %d tries left.\n", character, (numberOfAttempts - counter));
				printf("________________\n\n");
				printf("--> Guess the word: %s\n\n", userWord);
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
		return 1;
	}
	else
	{
		printf("The secret word was: %s\n\n\n", secretWord);
		return 0;
	}
}

// Function handles record keeping of user streaks in external file
int highScores(int streak, char userName[])
{
	// Open two files - create files if they does not exist
	FILE *scores = fopen("scores.txt", "r");
	if (scores == NULL)
	{
		printf("File did not open\n");
		exit(1);
	}
	
	FILE *tempScores = fopen("temp_scores.txt", "a");
	if (scores == NULL)
	{
		printf("File did not open\n");
		exit(1);
	}
	
	// Read through the file, line by line, looking for username
	char buffer[100]; // Initialize buffer
	
	if (fgets(buffer, sizeof(buffer), scores) == NULL) // Check if file is empty
	{
		printf("File is empty, adding new player score");
		fprintf(tempScores, "%s: %d\n", userName, streak); // If empty, write username and score in temporary file
	}
	else
	{	
		rewind(scores); // Go back to beginning of original file
		
		while (fgets(buffer, sizeof(buffer), scores) != NULL) // Loop over file, one line at a time
		{	
			if (strstr(buffer, userName) != NULL) // If username is found in file
			{
				// Find score in the string
				int score = 0;
				sscanf(buffer, "%*[^:]: %d", &score);
				
				if (streak == 0)
				{
					streak = 0;
				}
				else
				{
					streak += score;
				}
				
				// Rewrite line in temp file
				fprintf(tempScores, "%s: %d\n", userName, streak);
			}
			else  // If username is not found in file 
			{
				fprintf(tempScores, buffer);
			}
		}
	}
	
	while (getchar() != '\n');  // Clear buffer
	
	fclose(scores);
	fclose(tempScores);
	
	// Delete scores and rename tempScores to scores
	remove("scores.txt");
	
	if (rename("temp_scores.txt", "scores.txt") != 0)
	{
		perror("Rename failed");
		exit(1);
	}
	
	return streak;
}
