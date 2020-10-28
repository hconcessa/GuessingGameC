//============================================================================
// Name        : GuessingGame.cpp
// Author      : Higor Maia Concessa
// Version     : 1.0.0
// License     : GNU General Public License v3.0
// Description : A simple guessing game in C, Ansi-style
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/** Constants **/
const short MAX_SCORE = 1000;
const short ATTEMPT_EASY = 15;
const short ATTEMPT_MEDIUM = 10;
const short ATTEMPT_HARD = 5;
const short ATTEMPT_VERY_HARD = 3;
/**				**/

/** Non Constants **/
int exitGame;
int winner = 0;
short level;
short attempts;
float score = 100;
short winnerNumber;
/** 			**/

/** Procedures **/
void printWelcome();
void printWinner();
void printLoser();
void printTip(short number);
void printScore(float score);
void selectLevel();
void playAgain();
/**				**/

/** Functions **/
int isValidLevel(short level);
short randomNumber();
short receiveNumber();
short receiveNewNumber();
float calcScore(float oldScore, short number);
/**				**/

int main() {
	printWelcome();
	while(!exitGame){
		winner = 0;
		winnerNumber = randomNumber();
		selectLevel();
		if(!exitGame){
			printf("Attempt %d of %d\n", 1, attempts);
			int playerNumber = receiveNumber();

			if(playerNumber != winnerNumber){
				printTip(playerNumber);
				for(int i = 1; i < attempts; i++){
					printf("Attempt %d of %d\n", i+1, attempts);
					playerNumber = receiveNewNumber();
					score = calcScore(score, playerNumber);
					if(playerNumber == winnerNumber){
						winner = 1;
						printWinner();
						printScore(score);
						playAgain();
						break;
					}else{
						printTip(playerNumber);
					}
				}
				if(!winner){
					printf("The secret number is %d\n", winnerNumber);
					printLoser();
					printScore(score);
					playAgain();
				}
			}else{
				winner = 1;
				printWinner();
				playAgain();
			}
		}
	}
	printf("Thank you, good bye!\n");
	system("PAUSE");
	return 0;
}

void printWelcome(){
	printf("\n");
	printf("*******************************************************\n");
	printf("********** Welcome to number guessing game! ***********\n");
	printf("*******************************************************\n\n");
}

void printWinner(){
	printf("\n");
	printf("**       *************************************       **\n");
	printf("************** CONGRATULATIONS! YOU WIN! **************\n");
	printf("**       *************************************       **\n\n");
}

void printLoser(){
	printf("\n");
	printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	printf("X X X X X X X X X  MY BAD! YOU LOSE!  X X X X X X X X X\n");
	printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n");
}

void printScore(float score){
	printf("Score: %.2f\n\n", score);
}

void selectLevel(){
	printf("Choose the game level:\n");
	printf("1 - Easy\n");
	printf("2 - Medium\n");
	printf("3 - Hard\n");
	printf("4 - Very Hard\n");
	printf("0 - Exit\n");
	scanf("%d", &level);
	
	if(isValidLevel(level)){
		printf("Level %d  selected! God game!\n\n", level);
	}else if(exitGame){
		return;
	}else{
		printf("Invalid level! Please, select a valid level or digit 0 to exit.\n", level);
		selectLevel();
	}
}

int isValidLevel(short level){
	switch(level){
		case 1:
			attempts = ATTEMPT_EASY;
			return 1;
		case 2:
			attempts = ATTEMPT_MEDIUM;
			return 1;
		case 3:
			attempts = ATTEMPT_HARD;
			return 1;
		case 4:
			attempts = ATTEMPT_VERY_HARD;
			return 1;
		case 0:
			exitGame = 1;
			return 0;
		default:
			return 0;
	}
}

short randomNumber(){
	srand(time(NULL));	// Use base time to calc a random number
	/**
	* % 100 return a number between 0~99
	* % 1000 return a number between 0~999
	* etc
	*/
	printf("A new number between 0 and 99 has generate!\n\n");
	return rand() % 100;
}

short receiveNumber(){
	printf("Enter the first number to try to guess:\n");
	int i;
	scanf("%d", &i);
	return i;
}

short receiveNewNumber(){
	printf("Enter with other number to try to guess:\n");
	int i;
	scanf("%d", &i);
	return i;
}

float calcScore(float oldScore, short number){
	float newScore = oldScore - abs(number - winnerNumber)/2;
	return newScore;
}

void playAgain(){
	printf("Play again?\n");
	printf("Yes (Y)\n");
	printf("No (N)\n\n");
	char in;
	scanf("%c", &in);

	if(in == 'y' || in == 'Y'){
		exitGame = 0;
	} else if(in == 'n' || in == 'N' || in == '0'){
		exitGame = 1;
	}else{
		printf("Invalid answer! Please, try again or digit 0 to exit.\n");
		playAgain();
	}
}

void printTip(short number){
	printf("\n");
	if(number < winnerNumber){
		printf("The number %d is lower than the secret number!\n\n", number);
	}else{
		printf("The number %d is bigger than the secret number!\n\n", number);
	}
}