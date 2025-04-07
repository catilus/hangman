/*
	Functions.h by HPIET
 	Prototypes for functions
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void screenClear();
// Structure containing difficulty levels
typedef enum
{
	HARD = 10,
	MEDIUM = 15,
	EASY = 20
} Difficulty;

Difficulty setDifficulty();
char *chooseFromFile();
char *initializeUserWord(char secretWord[]);
char getCharacter();
int readWord(char secretWord[], char userWord[], Difficulty numberOfAttempts);
int highScores(int streak, char username[]);

#endif
