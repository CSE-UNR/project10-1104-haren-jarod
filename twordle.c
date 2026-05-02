//author: Jarod Haren
//date 5/1/2026

#include <stdio.h>
#define GUESS_AMOUNT 11
#define WORD_LENGTH 6
#define READ_FILENAME "mystery.txt"

_Bool readWordle(char correctWord[]);
void makeLowerCase(int cols, char guessArray[][cols], int guessNumber);
void getGuess(int cols, char guessArray[][cols], int guessNumber);
void evaluateGuess(int cols, char guessArray[][cols],char correctWord[], int guessNumber);
void printGuesses(int cols, char guessArray[][cols], int guessNumber);
void winCondition(int guessNumber, char correctWord[]);
void loseCondition();


int main() {
	char guessArray[GUESS_AMOUNT][WORD_LENGTH], correctWord[WORD_LENGTH];
	int guessNumber = 0;
	int cols = WORD_LENGTH;
	_Bool win;
	if (readWordle(correctWord) == 0) {
		return 0;
	}	 
	do {
		printf("GUESS %d! Enter your guess: ",guessNumber + 1);
		getGuess(cols, guessArray, guessNumber);
		
		makeLowerCase(cols,guessArray, guessNumber);
		
		evaluateGuess(cols, guessArray, correctWord, guessNumber);
		
		guessNumber++;
		
		printGuesses(cols, guessArray, guessNumber);
		
		
		win = 1;
		for (int i = 0; i < WORD_LENGTH - 1; i++) {	
			if (guessArray[(guessNumber-1) * 2][i] != correctWord[i] - 32) {
				win = 0;
			}
		}
		if (win) {
				winCondition(guessNumber, correctWord);
			} else if (guessNumber == GUESS_AMOUNT /2) {
				loseCondition();	
		}
	} while (guessNumber < GUESS_AMOUNT / 2 && !win);		  
												
return 0;
}

_Bool readWordle (char correctWord[]) {
	FILE* readFilePointer;
	readFilePointer = fopen(READ_FILENAME, "r");
	if(readFilePointer == NULL){
		printf("Cannot open file for reading.\n");
		return 0;
	} else {
		fgets(correctWord, WORD_LENGTH, readFilePointer);		
	}
	fclose(readFilePointer);
	return 1;
}	

void makeLowerCase(int cols, char guessArray[][cols], int guessNumber) {
	for (int i = 0; guessArray[guessNumber * 2][i] != '\0'; i++) {
		if ( guessArray[guessNumber*2][i] >= 'A' && guessArray[guessNumber*2][i] <= 'Z') {
			guessArray[guessNumber * 2][i] = guessArray[guessNumber * 2][i] + 32;
		} else {
			guessArray[guessNumber*2][i] = guessArray[guessNumber*2][i];
		}	
	}	
}

void getGuess(int cols, char guessArray[][cols], int guessNumber) {
	char currentGuess[WORD_LENGTH];
	int specialCharacters, letterCount, specialCount;
	_Bool letterCorrect;
	do {
		letterCount = 0;
		specialCount = 0;
		specialCharacters = 0;
		scanf("%s", currentGuess);
		for (letterCount = 0; currentGuess[letterCount] != '\0'; letterCount++) {
		}
		if (letterCount == WORD_LENGTH-1) {
			letterCorrect = 1;			
		} else { 
			letterCorrect = 0;	
		}
		for (int i = 0; currentGuess[i] != '\0'; i++) {
			if ((currentGuess[i] >= 'a' && currentGuess[i] <= 'z') || (currentGuess[i] >= 'A' && currentGuess[i] <= 'Z')) {
				specialCount = 1;	
			} else {
				specialCount = 0;
			}
			specialCharacters = specialCharacters + specialCount;
		}	
		if  (!letterCorrect) {
			printf("Your guess must be %d letters long.", WORD_LENGTH - 1);
		}	
		if  (specialCharacters != letterCount) {
			printf("Your guess must contain only letters");
		}	
		if (specialCharacters != letterCount || letterCorrect == 0) {
			printf("\nPlease try again: ");	
		}
			
	} while (specialCharacters != letterCount || letterCorrect == 0);		
	for (int i = 0; i <= WORD_LENGTH; i++) {
		guessArray[guessNumber * 2][i] = currentGuess[i];
	}
	guessArray[guessNumber * 2][WORD_LENGTH] = '\0';
}
void winCondition(int guessNumber, char correctWord[]) {
	printf("\n================================");
	printf("\n		");
	for (int i = 0; i < WORD_LENGTH - 1; i++) {
		printf("%c", correctWord[i] - 32);
	}
	printf("\n	You won in %d guesses!\n ", guessNumber);
	if (guessNumber == 1){
		printf("		GOATED!\n");
	} else if( guessNumber < 4 && guessNumber > 1) {
		printf("		Amazing!\n");
	} else {
		printf("		Nice!\n");
	}			
}

void loseCondition () {
	printf("You lost, better luck next time!\n");
}

void printGuesses(int cols,char guessArray[][cols], int guessNumber) {
	printf("================================\n");
	for (int i = 0; i < guessNumber * 2; i += 2) {
		printf("%s\n", guessArray[i]);
		printf("%s\n", guessArray[i + 1]);
	}
	printf("\n");	
}

void evaluateGuess(int cols, char guessArray[][cols], char correctWord[], int currentGuess) {
	_Bool closeMatch;
	for (int i = 0; i < cols - 1; i++) {
		closeMatch = 0;
        	if (guessArray[currentGuess * 2][i] == correctWord[i]) {
        	    guessArray[currentGuess * 2][i] = guessArray[currentGuess * 2][i] - 32;
        	    guessArray[currentGuess * 2 + 1][i] = ' ';
       		} else {
			for (int j = 0; j < cols && !closeMatch; j++) {
			if (guessArray[currentGuess * 2][i] == correctWord[j]) {
				closeMatch = 1;
                	}
            		}
            		if (closeMatch) {
                		guessArray[currentGuess * 2 + 1][i] = '^';
            		} else {
                		guessArray[currentGuess * 2 + 1][i] = ' ';
            		}
        	}
    	}
	guessArray[currentGuess * 2 + 1][WORD_LENGTH] = '\0';
}		
