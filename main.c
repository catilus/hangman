#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
//#define MAX_LENGTH 1000

int main(int argc, char *argv[])
{
	char secretWord[] = "OLIVE";
	char userWord[] = "*****";
	
	printf("\nWelcome to Hangman!\n\n");
	
	readWord(secretWord, userWord);
	
	return 0;
}
